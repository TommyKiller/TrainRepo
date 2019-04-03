#include "ShaderProgram.h"

Graphics::ShaderProgram::ShaderProgram(ShaderProgram& shader_program)
{
	ID = shader_program.ID;
	shaders_sources = shader_program.shaders_sources;
}

Graphics::ShaderProgram::ShaderProgram(std::unordered_map<GLenum, const char*> shaders_files)
{
	std::vector<GLuint> shaders_list;
	for (const auto& [key, value] : shaders_files)
	{
		shaders_sources[key] = LoadShader(key, value);
		shaders_list.push_back(CreateShader(key, shaders_sources[key].c_str()));
	}

	ID = CreateProgram(shaders_list);
}

void Graphics::ShaderProgram::SetShader(GLenum shader_type, const char* file_name)
{
	Dispose();

	shaders_sources[shader_type] = LoadShader(shader_type, file_name);

	std::vector<GLuint> shaders_list;
	for (const auto& [key, value] : shaders_sources)
	{
		shaders_list.push_back(CreateShader(key, value.c_str()));
	}

	ID = CreateProgram(shaders_list);
}

void Graphics::ShaderProgram::Use()
{
	glUseProgram(ID);
}

GLuint Graphics::ShaderProgram::GetAttribLocation(std::string attribute_name)
{
	return glGetAttribLocation(ID, attribute_name.c_str());
}

void Graphics::ShaderProgram::SetUniform(std::string uniform_name, int uniform_value)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniform1i(uniform_location, uniform_value);
}

void Graphics::ShaderProgram::SetUniform(std::string uniform_name, float uniform_value)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniform1f(uniform_location, uniform_value);
}

void Graphics::ShaderProgram::SetUniform(std::string uniform_name, int uniform_value1, int uniform_value2)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniform2i(uniform_location, uniform_value1, uniform_value2);
}

void Graphics::ShaderProgram::SetUniform(std::string uniform_name, int count, GLboolean transpose, glm::mat4 uniform_value)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniformMatrix4fv(uniform_location, count, transpose, glm::value_ptr(uniform_value));
}

void Graphics::ShaderProgram::Dispose()
{
	if (ID != 0)
	{
		glDeleteProgram(ID);
		ID = 0;
	}
}

Graphics::ShaderProgram::~ShaderProgram()
{
	Dispose();
}

std::string Graphics::ShaderProgram::LoadShader(GLenum shader_type, const char* file_name)
{
	std::ifstream fileStream(file_name, std::ios::in);
	if (!fileStream.is_open())
	{
		throw std::exception("Can not open file!");
	}

	std::string shader_source;
	std::string line;
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		shader_source.append(line + "\n");
	}

	return shader_source;
}

GLuint Graphics::ShaderProgram::CreateShader(GLenum shader_type, const char* shader_source)
{
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLint info_log_len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_len);
		GLchar* info_log = new GLchar[info_log_len + 1];
		glGetShaderInfoLog(shader, info_log_len, &info_log_len, info_log);
		std::cout << info_log << std::endl;
		throw std::exception(info_log);
	
		delete[] info_log;
	}
	
	return shader;
}

GLuint Graphics::ShaderProgram::CreateProgram(std::vector<GLuint> shaders_list)
{
	GLuint program = glCreateProgram();
	
	for (const GLuint& shader : shaders_list)
	{
		glAttachShader(program, shader);
	}
	
	glLinkProgram(program);
	
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLint info_log_len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_len);
		GLchar* info_log = new GLchar[info_log_len + 1];
		glGetProgramInfoLog(program, info_log_len, &info_log_len, info_log);
		std::cout << info_log << std::endl;
		throw std::exception(info_log);

		delete[] info_log;
	}
	
	glValidateProgram(program);
	
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (!status)
	{
		GLint info_log_len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_len);
		GLchar* info_log = new GLchar[info_log_len + 1];
		glGetProgramInfoLog(program, info_log_len, &info_log_len, info_log);
		std::cout << info_log << std::endl;
		throw std::exception(info_log);
	
		delete[] info_log;
	}

	std::for_each(shaders_list.begin(), shaders_list.end(), [&program](GLuint shader)
		{
			glDetachShader(program, shader);
			glDeleteShader(shader);
		});

	return program;
}
