#include "Editor.h"

Engine::Editor& Engine::Editor::GetInstance()
{
	static Engine::Editor instance;

	return instance;
}

void Engine::Editor::EditWorld(std::shared_ptr<Game::World> world)
{
	this->world = world;
}

void Engine::Editor::Enable()
{
	Graphics::Camera::GetInstance().Unbind();
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR, new Events::Delegate(this, &Engine::Editor::Enable));
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR, new Events::Delegate(this, &Engine::Editor::Disable));
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR_ADD_ACTOR, new Events::Delegate(this, &Engine::Editor::CreateActor));
}

void Engine::Editor::Disable()
{
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR, new Events::Delegate(this, &Engine::Editor::Enable));
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR, new Events::Delegate(this, &Engine::Editor::Disable));
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR_ADD_ACTOR, new Events::Delegate(this, &Engine::Editor::CreateActor));
}

void Engine::Editor::CreateActor()
{
	std::vector<GLfloat> vertex_data
	{
		// Coordinates					// Colours					// Texture coordinates
		 1.0f, -1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 1.0f,		1.0f, 0.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		 0.0f,  1.0f,  0.0f, 1.0f,		1.0f, 1.0f, 0.0f, 1.0f,		0.5f, 1.0f
	};

	std::vector<GLuint> elements =
	{
		0, 4, 1,
		1, 4, 2,
		2, 4, 3,
		3, 4, 0,
		0, 1, 2,
		0, 2, 3
	};

	static int actor_id = 0;

	active_actor = std::make_shared<Game::Actor>(actor_id++,
		new Graphics::Model(
			new Graphics::Mesh(vertex_data.data(), vertex_data.size(), elements.data(), elements.size(), GL_STATIC_DRAW),
			new Graphics::Texture("Resources/Textures/brick_wall.jpg", true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 0, GL_REPEAT, GL_REPEAT)),
		3.0f, 0.1f);
	world.lock()->GetActiveScene().lock()->AddActor(active_actor);
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR_ADD_ACTOR, new Events::Delegate(this, &Engine::Editor::CreateActor));
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR_MOVE, new Events::Delegate(&(*active_actor), &Game::Actor::Move));
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR_PLACE_ACTOR, new Events::Delegate(this, &Engine::Editor::AddActor));
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR_CANCEL, new Events::Delegate(this, &Engine::Editor::Cancel));
}

void Engine::Editor::AddActor()
{
	world.lock()->AddActor(active_actor);
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR_MOVE, new Events::Delegate(&(*active_actor), &Game::Actor::Move));
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR_ADD_ACTOR, new Events::Delegate(this, &Engine::Editor::CreateActor));
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR_PLACE_ACTOR, new Events::Delegate(this, &Engine::Editor::AddActor));
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR_CANCEL, new Events::Delegate(this, &Engine::Editor::Cancel));
	active_actor.reset();
}

void Engine::Editor::Cancel()
{
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR_MOVE, new Events::Delegate(&(*active_actor), &Game::Actor::Move));
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR_ADD_ACTOR, new Events::Delegate(this, &Engine::Editor::CreateActor));
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR_PLACE_ACTOR, new Events::Delegate(this, &Engine::Editor::AddActor));
	Input::InputController::GetInstance().UnsubscribeTo(Input::InputEvents::EVENT_EDITOR_CANCEL, new Events::Delegate(this, &Engine::Editor::Cancel));
	world.lock()->GetActiveScene().lock()->DeleteActor(active_actor->GetID());
	active_actor.reset();
}

Engine::Editor::Editor()
{
	Input::InputController::GetInstance().SubscribeTo(Input::InputEvents::EVENT_EDITOR, new Events::Delegate(this, &Engine::Editor::Enable));
}

Engine::Editor::~Editor()
{}
