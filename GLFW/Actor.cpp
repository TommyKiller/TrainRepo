#include "Actor.h"

Game::Actor::Actor(int id, Graphics::Model* model, float moveSpeed, float turnSpeed)
	: id(id),
	model(std::move(model)),
	moveSpeed(moveSpeed),
	turnSpeed(turnSpeed)
{}

Graphics::Model* Game::Actor::GetModel()
{
	return model.get();
}

int Game::Actor::GetID()
{
	return id;
}

void Game::Actor::Bind()
{
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_MOVE, new Events::Delegate(this, &Game::Actor::Move));
}

void Game::Actor::Unbind()
{
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_MOVE, new Events::Delegate(this, &Game::Actor::Move));
}

void Game::Actor::Move()
{
	GLfloat velocity = System::GetDeltaTime() * moveSpeed;
	glm::vec3 direction(0);
	using namespace Input;
	if (InputController::GetInstance().KeyPressed(InputController::GetInstance().GetKey(Actions::ACTION_EDITOR_MOVE_FORWARD)))
	{
		direction.z += 1.0f;
	}
	if (InputController::GetInstance().KeyPressed(InputController::GetInstance().GetKey(Actions::ACTION_EDITOR_MOVE_BACKWARD)))
	{
		direction.z -= 1.0f;
	}
	if (InputController::GetInstance().KeyPressed(InputController::GetInstance().GetKey(Actions::ACTION_EDITOR_MOVE_LEFT)))
	{
		direction.x += 1.0f;
	}
	if (InputController::GetInstance().KeyPressed(InputController::GetInstance().GetKey(Actions::ACTION_EDITOR_MOVE_RIGHT)))
	{
		direction.x -= 1.0f;
	}

	model->Move(direction, velocity);
}

void Game::Actor::Dispose()
{
	model.reset(nullptr);
}

Game::Actor::~Actor()
{
	Dispose();
}
