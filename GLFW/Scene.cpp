#include "Scene.h"

Game::Scene::Scene(int id, glm::mat4 projection)
	: id(id),
	projection(projection)
{}

void Game::Scene::AddActor(std::shared_ptr<Game::Actor> actor)
{
	actors[actor->GetID()] = actor;
}

void Game::Scene::DeleteActor(int actor_id)
{
	actors.erase(actor_id);
}

void Game::Scene::SetProjection(float fovy, float aspect, float near, float far)
{
	projection = glm::perspective(fovy, aspect, near, far);
}

void Game::Scene::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

std::unordered_map<int, std::weak_ptr<Game::Actor>>& Game::Scene::GetActors()
{
	return actors;
}

int Game::Scene::GetID()
{
	return id;
}

glm::mat4 Game::Scene::GetProjection()
{
	return projection;
}

void Game::Scene::Dispose()
{
	actors.clear();
}

Game::Scene::~Scene()
{
	Dispose();
}
