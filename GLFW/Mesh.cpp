#include "Mesh.h"

Graphics::Mesh::Mesh(Mesh& mesh)
{
	VAO = mesh.VAO;
	EBO = mesh.EBO;
	VBO = mesh.VBO;
	elements_count = mesh.elements_count;
}

Graphics::Mesh::Mesh(GLfloat* vertex_data, size_t vertex_data_size,
	GLuint* elements, size_t elements_count, GLenum usage)
	: elements_count(elements_count)
{
	VBO = CreateBuffer(GL_ARRAY_BUFFER, vertex_data, vertex_data_size, usage);
	EBO = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, elements, elements_count, usage);
	VAO = CreateVAO(VBO, EBO);
}

void Graphics::Mesh::Use()
{
	glBindVertexArray(VAO);
}

size_t Graphics::Mesh::GetElementsCount() const
{
	return elements_count;
}

GLuint Graphics::Mesh::CreateVAO(GLuint VBO, GLuint EBO)
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	unsigned int stride = 10 * sizeof(GL_FLOAT);

	// Coordinates
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (const void*) 0);
	glEnableVertexAttribArray(0);
	// Colours
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const void*)(4 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	// Texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (const void*)(8 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBindVertexArray(0);

	return VAO;
}

void Graphics::Mesh::Dispose()
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (EBO != 0)
	{
		glDeleteBuffers(1, &EBO);
		EBO = 0;
	}

	elements_count = 0;
}

Graphics::Mesh::~Mesh()
{
	Dispose();
}
