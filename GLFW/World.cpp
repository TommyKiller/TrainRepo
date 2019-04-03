#include "World.h"

void Game::World::AddScene(Scene* scene)
{
	scenes[scene->GetID()] = std::shared_ptr<Scene>(scene);
}

void Game::World::AddActor(std::shared_ptr<Actor> actor, int scene_id)
{
	actors[actor->GetID()] = actor;
	scenes[scene_id]->AddActor(actor);
}

void Game::World::AddActor(std::shared_ptr<Actor> actor)
{
	actors[actor->GetID()] = actor;
}

void Game::World::SetActiveScene(int scene_id)
{
	if (scenes.count(scene_id))
	{
		active_scene = scenes[scene_id];
	}
}

std::weak_ptr<Game::Scene> Game::World::GetActiveScene()
{
	return active_scene;
}

void Game::World::Dispose()
{
	actors.clear();
	scenes.clear();
}

Game::World::~World()
{
	Dispose();
}
