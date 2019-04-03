#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "System.h"
#include "InputController.h"


namespace Graphics
{
	class Camera
	{
	public:
		static Camera& GetInstance();

		void Initialise(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);

		void Bind();

		void Unbind();

		void MoveToPos(glm::vec3 position, GLfloat yaw, GLfloat pitch);

		void Rotate();

		void Move();

		glm::mat4 CalcViewMat();

	private:
		glm::vec3 position;
		glm::vec3 up;
		glm::vec3 front;
		glm::vec3 right;
		glm::vec3 worldUp;
		GLfloat yaw, pitch;
		GLfloat moveSpeed;
		GLfloat turnSpeed;

		void UpdateAxes();

		Camera();

		Camera(Camera&) = delete;

		Camera& operator= (Camera&) = delete;

		~Camera();
	};
}


#endif
