#include "InputController.h"

Input::InputController::InputController()
{}

Input::InputController& Input::InputController::GetInstance()
{
	static Input::InputController instance;

	return instance;
}

void Input::InputController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key != GLFW_KEY_UNKNOWN)
	{
		switch (action)
		{
		case GLFW_PRESS:
		{
			if (!Input::InputController::GetInstance().HasKey(key))
			{
				Input::InputController::GetInstance().AddKey(key, scancode);
			}
			if (!Input::InputController::GetInstance().KeyPressed(key))
			{
				Input::InputController::GetInstance().SetKeyPressed(key, true);
				Input::InputController::GetInstance().SetKeyHandled(key, false);
			}
			break;
		}
		case GLFW_RELEASE:
		{
			Input::InputController::GetInstance().SetKeyDefalut(key);
			break;
		}
		}
	}
}

void Input::InputController::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	using namespace Input;
	if (InputController::GetInstance().GetMouse().firstMove)
	{
		InputController::GetInstance().GetMouse().lastXPos = xpos;
		InputController::GetInstance().GetMouse().lastYPos = ypos;
		InputController::GetInstance().GetMouse().firstMove = false;
	}

	InputController::GetInstance().GetMouse().xChange = xpos - InputController::GetInstance().GetMouse().lastXPos;
	InputController::GetInstance().GetMouse().yChange = InputController::GetInstance().GetMouse().lastYPos - ypos;
	InputController::GetInstance().GetMouse().lastXPos = xpos;
	InputController::GetInstance().GetMouse().lastYPos = ypos;
	InputController::GetInstance().GetMouse().handled = false;
}

void Input::InputController::PollEvents()
{
	if (KeyPressed(GetKey(ACTION_MOVE_FORWARD)) || KeyPressed(GetKey(ACTION_MOVE_LEFT)) ||
		KeyPressed(GetKey(ACTION_MOVE_BACKWARD)) || KeyPressed(GetKey(ACTION_MOVE_RIGHT)) ||
		KeyPressed(GetKey(ACTION_MOVE_JUMP)) || KeyPressed(GetKey(ACTION_MOVE_CROUCH)))
	{
		PollEvent(EVENT_MOVE);
	}
	if (KeyPressed(GetKey(ACTION_EDITOR_MOVE_FORWARD)) || KeyPressed(GetKey(ACTION_EDITOR_MOVE_LEFT)) ||
		KeyPressed(GetKey(ACTION_EDITOR_MOVE_BACKWARD)) || KeyPressed(GetKey(ACTION_EDITOR_MOVE_RIGHT)))
	{
		PollEvent(EVENT_EDITOR_MOVE);
	}
	if (KeyPressed(GetKey(ACTION_EXIT)) && !KeyHandled(GetKey(ACTION_EXIT)))
	{
		PollEvent(EVENT_EXIT);
		SetKeyHandled(GetKey(ACTION_EXIT), true);
	}
	if (KeyPressed(GetKey(ACTION_SWITCH_SCREEN_MODE)) && !KeyHandled(GetKey(ACTION_SWITCH_SCREEN_MODE)))
	{
		PollEvent(EVENT_SWITCH_SCREEN_MODE);
		SetKeyHandled(GetKey(ACTION_SWITCH_SCREEN_MODE), true);
	}
	if (KeyPressed(GetKey(ACTION_EDITOR)) && !KeyHandled(GetKey(ACTION_EDITOR)))
	{
		PollEvent(EVENT_EDITOR);
		SetKeyHandled(GetKey(ACTION_EDITOR), true);
	}
	if (KeyPressed(GetKey(ACTION_EDITOR_ADD_PYRAMID)) && !KeyHandled(GetKey(ACTION_EDITOR_ADD_PYRAMID)))
	{
		PollEvent(EVENT_EDITOR_ADD_ACTOR);
		SetKeyHandled(GetKey(ACTION_EDITOR_ADD_PYRAMID), true);
	}
	if (KeyPressed(GetKey(ACTION_EDITOR_PLACE_ACTOR)) && !KeyHandled(GetKey(ACTION_EDITOR_PLACE_ACTOR)))
	{
		PollEvent(EVENT_EDITOR_PLACE_ACTOR);
		SetKeyHandled(GetKey(ACTION_EDITOR_PLACE_ACTOR), true);
	}
	if (KeyPressed(GetKey(ACTION_EDITOR_CANCEL)) && !KeyHandled(GetKey(ACTION_EDITOR_CANCEL)))
	{
		PollEvent(EVENT_EDITOR_CANCEL);
		SetKeyHandled(GetKey(ACTION_EDITOR_CANCEL), true);
	}
	if (!GetMouse().handled)
	{
		PollEvent(EVENT_MOUSE_ROTATE);
		GetMouse().handled = true;
	}
}

void Input::InputController::SubscribeTo(Input::InputEvents event, Events::Delegate* delegate)
{
	*events[event] += *delegate;
}

void Input::InputController::UnsubscribeTo(Input::InputEvents event, Events::Delegate* delegate)
{
	*events[event] -= *delegate;
}

double Input::InputController::GetMouseXChange()
{
	return mouse.xChange;
}

double Input::InputController::GetMouseYChange()
{
	return mouse.yChange;
}

int Input::InputController::GetKey(Input::Actions action)
{
	return actions[action];
}

void Input::InputController::PollEvent(Input::InputEvents event)
{
	(*events[event])();
}

void Input::InputController::AddKey(int key, int scancode)
{
	keys[key].scancode = scancode;
}

void Input::InputController::SetKeyDefalut(int key)
{
	keys[key].pressed = false;
	keys[key].handled = true;
	keys[key].modded = false;
}

void Input::InputController::SetKeyPressed(int key, bool pressed)
{
	keys[key].pressed = pressed;
}

void Input::InputController::SetKeyHandled(int key, bool handled)
{
	keys[key].handled = handled;
}

void Input::InputController::SetKeyMods(int key, int mods)
{
	keys[key].mods = mods;
	keys[key].modded = true;
}

int Input::InputController::GetKeyMods(int key)
{
	return keys[key].mods;
}

bool Input::InputController::HasKey(int key)
{
	return keys.count(key);
}

Input::InputController::Mouse& Input::InputController::GetMouse()
{
	return mouse;
}

bool Input::InputController::KeyPressed(int key)
{
	return keys[key].pressed;
}

bool Input::InputController::KeyHandled(int key)
{
	return keys[key].handled;
}

bool Input::InputController::KeyModded(int key)
{
	return keys[key].mods;
}

Input::InputController::~InputController()
{}
