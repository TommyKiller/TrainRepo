#ifndef WORLD_H
#define WORLD_H
#include "Scene.h"


namespace Game
{
	class World
	{
	public:
		void AddScene(Scene* scene);

		void AddActor(std::shared_ptr<Actor> actor, int scene_id);

		void AddActor(std::shared_ptr<Actor> actor);

		void SetActiveScene(int scene_id);

		std::weak_ptr<Scene> GetActiveScene();

		void Dispose();

		~World();

	private:
		std::unordered_map<int, std::shared_ptr<Scene>> scenes;
		std::unordered_map<int, std::shared_ptr<Actor>> actors;
		std::weak_ptr<Scene> active_scene;
	};
}


#endif
