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

	Rendering::Rendering(sf::RenderWindow& window) : window(window) {
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

			if (spriteRenderer.sprite == nullptr) continue;
			if (spriteRenderer.sprite->texture == nullptr) continue;

			drawTasks.emplace_back();
			DrawTask& task = drawTasks.back();

			task.type = DrawTask::Type::Sprite;
			task.transform = transform;
			task.sprite = spriteRenderer;
			task.layer = spriteRenderer.layer;
			task.texture = spriteRenderer.sprite->texture;
		}

		for (auto e : getWorld()->getEntitiesWith<HUDImageRenderer>()) {
			auto hudImage = e.get<HUDImageRenderer>();

			drawTasks.emplace_back();
			DrawTask& task = drawTasks.back();

			task.type = DrawTask::Type::HUDImage;
			task.hudImage = hudImage;
			task.layer = hudImage.layer;
			task.texture = hudImage.sprite->texture;
		}

		std::sort(drawTasks.begin(), drawTasks.end(), [](const DrawTask& a, const DrawTask& b) {
			if (a.layer == b.layer) {
				return a.texture->getId() < b.texture->getId();
		    } else {
				return a.layer < b.layer;
			}
		});

		std::vector<Vertex> verticies;
		std::vector<uint16_t> indicies;

		uint32_t elementsCtr = 0;

		Mat3 hudTransform = scale(Mat3(), Vec2(2.0f / (float)window.getSize().x, 2.0f / (float)window.getSize().y));
		hudTransform = translate(hudTransform, -Vec2((float)window.getSize().x, (float)window.getSize().y) * 0.5f);

		for (auto& task : drawTasks) {
			if (task.type == DrawTask::Type::Sprite) {
				Vec2 fSize(task.sprite.sprite->rect.size.x, task.sprite.sprite->rect.size.y);
				Vec2 a = -task.sprite.sprite->pivot / task.sprite.sprite->pixelsInUnit;
				Vec2 c = a + fSize / task.sprite.sprite->pixelsInUnit;
				Vec2 b(a.x, c.y);
				Vec2 d(c.x, a.y);

				Mat3 transform = viewProjectionMatrix *
								 translate(rotate(Mat3(), task.transform.rotation), task.transform.position);

				a = Vec2(transform * Vec3(a, 1));
				b = Vec2(transform * Vec3(b, 1));
				c = Vec2(transform * Vec3(c, 1));
				d = Vec2(transform * Vec3(d, 1));

				auto rect = task.sprite.sprite->rect;
				auto textureSize = task.sprite.sprite->texture->getSize();
				Vec2 ta((float) rect.origin.x / (float) textureSize.x, (float) rect.origin.y / (float) textureSize.y);
				Vec2 tc((float) (rect.origin.x + rect.size.x) / (float) textureSize.x,
						(float) (rect.origin.y + rect.size.y) / (float) textureSize.y);
				Vec2 tb(ta.x, tc.y);
				Vec2 td(tc.x, ta.y);

				auto id = (uint16_t) verticies.size();

				verticies.push_back(Vertex(a, ta));
				verticies.push_back(Vertex(b, tb));
				verticies.push_back(Vertex(c, tc));
				verticies.push_back(Vertex(d, td));

				indicies.push_back(id);
				indicies.push_back(id + (uint16_t) 2);
				indicies.push_back(id + (uint16_t) 1);
				indicies.push_back(id);
				indicies.push_back(id + (uint16_t) 3);
				indicies.push_back(id + (uint16_t) 2);

				task.elementsNum = 6;

			} else if (task.type == DrawTask::Type::HUDImage) {
				auto hudImage = task.hudImage;
				Vec2 a(hudImage.frame.origin.x, hudImage.frame.origin.y);
				Vec2 c(hudImage.frame.size.x + hudImage.frame.origin.x, hudImage.frame.size.y + hudImage.frame.origin.y);
				Vec2 b(a.x, c.y);
				Vec2 d(c.x, a.y);

				a = Vec2(hudTransform * Vec3(a, 1));
				b = Vec2(hudTransform * Vec3(b, 1));
				c = Vec2(hudTransform * Vec3(c, 1));
				d = Vec2(hudTransform * Vec3(d, 1));

				auto rect = hudImage.sprite->rect;
				auto textureSize = hudImage.sprite->texture->getSize();
				Vec2 ta((float) rect.origin.x / (float) textureSize.x, (float) rect.origin.y / (float) textureSize.y);
				Vec2 tc((float) (rect.origin.x + rect.size.x) / (float) textureSize.x,
						(float) (rect.origin.y + rect.size.y) / (float) textureSize.y);
				Vec2 tb(ta.x, tc.y);
				Vec2 td(tc.x, ta.y);

				auto id = (uint16_t) verticies.size();

				verticies.push_back(Vertex(a, ta));
				verticies.push_back(Vertex(b, tb));
				verticies.push_back(Vertex(c, tc));
				verticies.push_back(Vertex(d, td));

				indicies.push_back(id);
				indicies.push_back(id + (uint16_t) 2);
				indicies.push_back(id + (uint16_t) 1);
				indicies.push_back(id);
				indicies.push_back(id + (uint16_t) 3);
				indicies.push_back(id + (uint16_t) 2);

				task.elementsNum = 6;
			}
		}

		glBindVertexArray(vao);

		glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), verticies.data(), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint16_t), indicies.data(), GL_DYNAMIC_DRAW);

		glUseProgram(shader.getId());
		int uTexture = glGetUniformLocation(shader.getId(), "uTexture");
		glUniform1i(uTexture, 0);

		glActiveTexture(GL_TEXTURE0);


		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);


		uint32_t dcStart = 0;
		uint32_t dcSize = 0;
		Ref<Texture> lastTexture;
		for (auto& drawTask : drawTasks)  {
			if (lastTexture == nullptr || lastTexture == drawTask.texture) {
				lastTexture = drawTask.texture;
				dcSize += drawTask.elementsNum;
			} else {
				glBindTexture(GL_TEXTURE_2D, lastTexture->getId());
				glDrawElements(GL_TRIANGLES, dcSize, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(dcStart * sizeof(uint16_t)));
				dcStart += dcSize;
				dcSize = drawTask.elementsNum;
				lastTexture = drawTask.texture;
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
