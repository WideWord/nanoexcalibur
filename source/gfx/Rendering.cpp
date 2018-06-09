#include "Rendering.hpp"
#include "../common/Transform2D.hpp"
#include "Camera2D.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "SpriteRenderer.hpp"
#include "HUDTextRenderer.hpp"
#include <locale>
#include <codecvt>
#include <string>
#include "../3rdparty/glad/glad.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <algorithm>
#include "Sprite.hpp"
#include <vector>

namespace nexc {

	Rendering::Rendering(sf::Window& window) : window(window) {
		window.setActive(true);

		auto vs = R"""(
			#version 330

			layout(location = 0) in vec2 iWorldPosition;
			layout(location = 1) in vec2 iTexCoord;

			out vec2 vTexCoord;

			void main() {
				gl_Position = vec4(iWorldPosition, 0.5, 1);
				vTexCoord = iTexCoord;
			}
		)""";
		auto fs = R"""(
			#version 330

			in vec2 vTexCoord;

			out vec4 oColor;

			uniform sampler2D uTexture;

			void main() {
				oColor = texture(uTexture, vec2(vTexCoord.x, 1.0 - vTexCoord.y));
			}
		)""";
		shader.build(vs, fs);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vertexVBO);
		glGenBuffers(1, &indexVBO);

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

		glBindVertexArray(0);
	}

	void Rendering::run() {
		using namespace glm;

		window.setActive(true);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		auto cameraEntity = getWorld()->getEntitiesWith<Transform2D, Camera2D>().first();

		auto cameraTransform = cameraEntity.get<Transform2D>();
		auto camera = cameraEntity.get<Camera2D>();

		Mat3 viewMatrix = translate(rotate(Mat3(), -cameraTransform.rotation), -cameraTransform.position);

		Mat3 viewProjectionMatrix;

		float aspect = (float)window.getSize().x / (float)window.getSize().y;
		if (camera.keepHorizontalSize) {
			float horScale = 2.0f / camera.size;
			float verScale = horScale * aspect;
			viewProjectionMatrix = scale(viewMatrix, Vec2(horScale, verScale));
		} else {
			float verScale = 2.0f / camera.size;
			float horScale = verScale / aspect;
			viewProjectionMatrix = scale(viewMatrix, Vec2(horScale, verScale));
		}



		for (auto e : getWorld()->getEntitiesWith<Transform2D, SpriteRenderer>()) {
			auto transform = e.get<Transform2D>();
			auto spriteRenderer = e.get<SpriteRenderer>();

			drawTasks.emplace_back();
			DrawTask& task = drawTasks.back();

			task.transform = transform;
			task.sprite = spriteRenderer.sprite;
			task.layer = spriteRenderer.layer;
		}

		std::sort(drawTasks.begin(), drawTasks.end(), [](const DrawTask& a, const DrawTask& b) {
			if (a.layer == b.layer) {
				return a.sprite->texture->getId() < b.sprite->texture->getId();
		    } else {
				return a.layer < b.layer;
			}
		});

		std::vector<Vertex> verticies;
		std::vector<uint16_t> indicies;

		uint32_t elementsCtr = 0;

		for (auto& task : drawTasks) {
			Vec2 fSize(task.sprite->rect.size.x, task.sprite->rect.size.y);
			Vec2 a = -task.sprite->pivot / task.sprite->pixelsInUnit;
			Vec2 c = a + fSize / task.sprite->pixelsInUnit;
			Vec2 b(a.x, c.y);
			Vec2 d(c.x, a.y);

			Mat3 transform = viewProjectionMatrix * translate(rotate(Mat3(), task.transform.rotation), task.transform.position);

			a = Vec2(transform * Vec3(a, 1));
			b = Vec2(transform * Vec3(b, 1));
			c = Vec2(transform * Vec3(c, 1));
			d = Vec2(transform * Vec3(d, 1));

			auto rect = task.sprite->rect;
			auto textureSize = task.sprite->texture->getSize();
			Vec2 ta((float)rect.origin.x / (float)textureSize.x, (float)rect.origin.y / (float)textureSize.y);
			Vec2 tc((float)(rect.origin.x + rect.size.x) / (float)textureSize.x, (float)(rect.origin.y + rect.size.y) / (float)textureSize.y);
			Vec2 tb(ta.x, tc.y);
			Vec2 td(tc.x, ta.y);

			auto id = (uint16_t)verticies.size();

			verticies.push_back(Vertex(a, ta));
			verticies.push_back(Vertex(b, tb));
			verticies.push_back(Vertex(c, tc));
			verticies.push_back(Vertex(d, td));

			indicies.push_back(id);
			indicies.push_back(id + (uint16_t)2);
			indicies.push_back(id + (uint16_t)1);
			indicies.push_back(id);
			indicies.push_back(id + (uint16_t)3);
			indicies.push_back(id + (uint16_t)2);

			task.elementsNum = 6;
		}

		glBindVertexArray(vao);

		glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), verticies.data(), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint16_t), indicies.data(), GL_DYNAMIC_DRAW);

		glUseProgram(shader.getId());
		int uTexture = glGetUniformLocation(shader.getId(), "uTexture");
		glUniform1i(uTexture, 0);

		glActiveTexture(GL_TEXTURE0);

		uint32_t dcStart = 0;
		uint32_t dcSize = 0;
		Ref<Texture> lastTexture;
		for (auto& drawTask : drawTasks)  {
			if (lastTexture == nullptr || lastTexture == drawTask.sprite->texture) {
				lastTexture = drawTask.sprite->texture;
				dcSize += drawTask.elementsNum;
			} else {
				glBindTexture(GL_TEXTURE_2D, lastTexture->getId());
				glDrawElements(GL_TRIANGLES, dcSize, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(dcStart * sizeof(uint16_t)));
				dcStart += dcSize;
				dcSize = drawTask.elementsNum;
				lastTexture = drawTask.sprite->texture;
			}
		}
		if (lastTexture != nullptr) {
			glBindTexture(GL_TEXTURE_2D, lastTexture->getId());
			glDrawElements(GL_TRIANGLES, dcSize, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(dcStart * sizeof(uint16_t)));
		}


		glBindVertexArray(0);

		drawTasks.clear();

		window.display();
	}

}
