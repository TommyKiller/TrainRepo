#ifndef MODEL_H
#define MODEL_H
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <memory>
#include "Mesh.h"
#include "Texture.h"


namespace Graphics
{
	class Model
	{
	public:
		Model(Graphics::Mesh* mesh, Graphics::Texture* texture, glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f),
			glm::vec3 rotation_axis = glm::vec3(1.0f), float rotation_angle = 0);

		void UseMesh();

		void UseTexture();

		size_t GetElementsCount();

		glm::mat4 CalcModelMat();

		void Scale(glm::vec3 scale);

		void Rotate(float rotation_angle, glm::vec3 rotation_axis);

		void Move(glm::vec3 direction, float distance);

		void MoveTo(glm::vec3 position);

		void Dispose();

		~Model();

	private:
		std::unique_ptr<Graphics::Mesh> mesh;
		std::unique_ptr<Graphics::Texture> texture;

		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation_axis;
		float rotation_angle;

		Model(Model& model) = delete;
	};
}


#endif
