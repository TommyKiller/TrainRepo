#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <utility>


namespace Graphics
{
	class Mesh
	{
	public:
		Mesh() = delete;

		Mesh(Mesh& mesh);

		Mesh(GLfloat* vertex_data, size_t vertex_data_size,
			GLuint* elements, size_t elements_count, GLenum usage);

		void Use();

		size_t GetElementsCount() const;

		template<class data_t>
		GLuint CreateBuffer(GLenum target, data_t* data, size_t data_size, GLenum usage)
		{
			GLuint BO;
			glGenBuffers(1, &BO);

			glBindBuffer(target, BO);
			glBufferData(target, sizeof(data_t) * data_size, data, usage);
			glBindBuffer(target, 0);

			return BO;
		}

		GLuint CreateVAO(GLuint VBO, GLuint EBO);

		void Dispose();

		~Mesh();
	private:
		GLuint VAO, VBO, EBO;

		size_t elements_count;
	};
}


#endif
