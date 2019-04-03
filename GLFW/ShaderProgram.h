#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <GL/glew.h>
#include <GLM/gtc/type_ptr.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>


namespace Graphics
{
	class ShaderProgram
	{
	public:
		ShaderProgram() = delete;

		ShaderProgram(ShaderProgram& shader_program);

		ShaderProgram(std::unordered_map<GLenum, const char*> shaders_files);

		void SetShader(GLenum shader_type, const char* file_name);

		void Use();

		GLuint GetAttribLocation(std::string attribute_name);

		void SetUniform(std::string uniform_name, int uniform_value);

		void SetUniform(std::string uniform_name, float uniform_value);

		void SetUniform(std::string uniform_name, int uniform_value1, int uniform_value2);

		void SetUniform(std::string uniform_name, int count, GLboolean transpose, glm::mat4 uniform_value);

		void Dispose();

		~ShaderProgram();

	private:
		GLuint ID;

		std::unordered_map<GLenum, std::string> shaders_sources;

		std::string LoadShader(GLenum shader_type, const char* file_name);

		GLuint CreateShader(GLenum shader_type, const char* shader_source);

		GLuint CreateProgram(std::vector<GLuint> shaders_list);
	};
}


#endif
