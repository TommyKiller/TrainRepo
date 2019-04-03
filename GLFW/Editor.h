#ifndef EDITOR_H
#define EDITOR_H
#include "World.h"
#include "Camera.h"


namespace Engine
{
	class Editor
	{
	public:
		static Editor& GetInstance();

		void EditWorld(std::shared_ptr<Game::World> world);

		void Enable();

		void Disable();

		void CreateActor();

		void AddActor();

		void Cancel();

	private:
		std::weak_ptr<Game::World> world;
		std::shared_ptr<Game::Actor> active_actor;

		Editor();

		Editor(Editor&) = delete;

		Editor& operator=(Editor&) = delete;

		~Editor();
	};
}


#endif
