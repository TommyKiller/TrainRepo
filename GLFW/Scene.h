#ifndef SCENE_H
#define SCENE_H
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>
#include "Actor.h"


namespace Game
{
	class Scene
	{
	public:
		Scene(int id, glm::mat4 projection = glm::mat4(1));

		void AddActor(std::shared_ptr<Actor> actor);

		void DeleteActor(int actor_id);

		void SetProjection(float fovy, float aspect, float near, float far);

		void SetProjection(glm::mat4 projection);

		std::unordered_map<int, std::weak_ptr<Actor>>& GetActors();

		int GetID();

		glm::mat4 GetProjection();

		void Dispose();

		~Scene();

	private:
		std::unordered_map<int, std::weak_ptr<Actor>> actors;

		glm::mat4 projection;

		int id;
	};
}


#endif
