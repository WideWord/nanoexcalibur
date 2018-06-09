#include <glad/glad.h>
#include "Shader.hpp"
#include "../util/Assert.hpp"

namespace nexc {

	Shader::Shader() {
		id = glCreateProgram();
	}

	Shader::~Shader() {
		glDeleteProgram(id);
		if (vertex != 0) glDeleteShader(vertex);
		if (fragment != 0) glDeleteShader(fragment);
	}

	void Shader::build(const char* vs, const char* fs) {
		vertex = glCreateShader(GL_VERTEX_SHADER);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);

		size_t vsLen = strlen(vs);
		glShaderSource(vertex, 1, (const GLchar**)&vs, (const GLint*)&vsLen);
		glCompileShader(vertex);

		GLint status;
		GLsizei _len;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[1024];
			glGetShaderInfoLog(vertex, 1024, &_len, buffer);
			panic(buffer);
		}

		size_t fsLen = strlen(fs);
		glShaderSource(fragment, 1, (const GLchar**)&fs, (const GLint*)&fsLen);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[1024];
			glGetShaderInfoLog(fragment, 1024, &_len, buffer);
			panic(buffer);
		}

		glAttachShader(id, vertex);
		glAttachShader(id, fragment);

		glLinkProgram(id);

		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			char buffer[1024];
			glGetProgramInfoLog(id, 1024, &_len, buffer);
			panic(buffer);
		}
	}

}

