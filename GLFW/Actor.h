#ifndef ACTOR_H
#define ACTOR_H
#include "Model.h"
#include "InputController.h"
#include "System.h"


namespace Game
{
	class Actor
	{
	public:
		Actor(int id, Graphics::Model* model, float moveSpeed, float turnSpeed);

		Graphics::Model* GetModel();

		int GetID();

		void Bind();

		void Unbind();

		void Move();

		void Dispose();

		~Actor();

	private:
		std::unique_ptr<Graphics::Model> model;
		float moveSpeed;
		float turnSpeed;
		int id;
	};
}


#endif
