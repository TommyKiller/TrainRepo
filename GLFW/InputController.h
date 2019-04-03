#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "Event.h"

namespace Input
{
	enum Actions
	{
		ACTION_MOVE_FORWARD,
		ACTION_MOVE_BACKWARD,
		ACTION_MOVE_LEFT,
		ACTION_MOVE_RIGHT,
		ACTION_MOVE_JUMP,
		ACTION_MOVE_CROUCH,
		ACTION_EDITOR,
		ACTION_EDITOR_ADD_PYRAMID,
		ACTION_EDITOR_PLACE_ACTOR,
		ACTION_EDITOR_CANCEL,
		ACTION_EDITOR_MOVE_FORWARD,
		ACTION_EDITOR_MOVE_BACKWARD,
		ACTION_EDITOR_MOVE_LEFT,
		ACTION_EDITOR_MOVE_RIGHT,
		ACTION_SWITCH_SCREEN_MODE,
		ACTION_EXIT
	};

	enum InputEvents
	{
		EVENT_MOVE,
		EVENT_EDITOR,
		EVENT_EDITOR_ADD_ACTOR,
		EVENT_EDITOR_PLACE_ACTOR,
		EVENT_EDITOR_CANCEL,
		EVENT_EDITOR_MOVE,
		EVENT_MOUSE_ROTATE,
		EVENT_EXIT,
		EVENT_SWITCH_SCREEN_MODE
	};


	class InputController
	{
	public:
		static InputController& GetInstance();

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

		void PollEvents();

		void SubscribeTo(InputEvents event, Events::Delegate* delegate);

		void UnsubscribeTo(InputEvents event, Events::Delegate* delegate);

		double GetMouseXChange();

		double GetMouseYChange();

		int GetKey(Actions action);

		int GetKeyMods(int key);

		bool KeyModded(int key);

		bool KeyPressed(int key);

		bool KeyHandled(int key);

	private:
		struct Key
		{
			int scancode = 0;
			int mods = 0;
			bool modded = false;
			bool pressed = false;
			bool handled = true;
		};

		struct Action{}; // WILL BE USED IN THE FUTURE

		struct Mouse
		{
			double lastXPos;
			double lastYPos;
			double xChange = 0;
			double yChange = 0;
			bool firstMove = true;
			bool handled = true;
		};

		std::unordered_map<int, Key> keys;

		std::unordered_map<InputEvents, Events::Event*> events
		{
			{InputEvents::EVENT_MOVE,				new Events::Event()},
			{InputEvents::EVENT_EDITOR,				new Events::Event()},
			{InputEvents::EVENT_EDITOR_ADD_ACTOR,	new Events::Event()},
			{InputEvents::EVENT_EDITOR_PLACE_ACTOR,	new Events::Event()},
			{InputEvents::EVENT_EDITOR_CANCEL,		new Events::Event()},
			{InputEvents::EVENT_EDITOR_MOVE,		new Events::Event()},
			{InputEvents::EVENT_MOUSE_ROTATE,		new Events::Event()},
			{InputEvents::EVENT_EXIT,				new Events::Event()},
			{InputEvents::EVENT_SWITCH_SCREEN_MODE, new Events::Event()}
		};

		std::unordered_map<Actions, int> actions
		{
			{Actions::ACTION_MOVE_FORWARD,			GLFW_KEY_W},
			{Actions::ACTION_MOVE_BACKWARD,			GLFW_KEY_S},
			{Actions::ACTION_MOVE_LEFT,				GLFW_KEY_A},
			{Actions::ACTION_MOVE_RIGHT,			GLFW_KEY_D},
			{Actions::ACTION_MOVE_JUMP,				GLFW_KEY_SPACE},
			{Actions::ACTION_MOVE_CROUCH,			GLFW_KEY_LEFT_CONTROL},
			{Actions::ACTION_EDITOR,				GLFW_KEY_F10},
			{Actions::ACTION_EDITOR_ADD_PYRAMID,	GLFW_KEY_1},
			{Actions::ACTION_EDITOR_PLACE_ACTOR,	GLFW_KEY_ENTER},
			{Actions::ACTION_EDITOR_CANCEL,			GLFW_KEY_DELETE},
			{Actions::ACTION_EDITOR_MOVE_FORWARD,	GLFW_KEY_UP},
			{Actions::ACTION_EDITOR_MOVE_BACKWARD,	GLFW_KEY_DOWN},
			{Actions::ACTION_EDITOR_MOVE_LEFT,		GLFW_KEY_LEFT},
			{Actions::ACTION_EDITOR_MOVE_RIGHT,		GLFW_KEY_RIGHT},
			{Actions::ACTION_EXIT,					GLFW_KEY_ESCAPE},
			{Actions::ACTION_SWITCH_SCREEN_MODE,	GLFW_KEY_F11}
		};

		Mouse mouse;

		void PollEvent(InputEvents event);

		void AddKey(int key, int scancode);

		void SetKeyDefalut(int key);

		void SetKeyPressed(int key, bool pressed);

		void SetKeyHandled(int key, bool handled);

		void SetKeyMods(int key, int mods);

		bool HasKey(int key);

		Mouse& GetMouse();

		InputController();

		InputController(InputController&) = delete;

		InputController& operator=(const InputController&) = delete;

		~InputController();
	};
}


#endif
