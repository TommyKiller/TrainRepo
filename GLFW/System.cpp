#include "System.h"

double System::deltaTime = 0.0f;

void System::InitialiseGLFW(unsigned int maj_version, unsigned int min_version)
{
	if (!glfwInit())
	{
		throw std::exception("Can not initialise GLFW!");
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min_version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

void System::InitialiseGLEW(System::Window* window)
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Can not initialize GLEW!");
		delete window;
		glfwTerminate();
	}
}

void System::CalcDeltaTime()
{
	static double last = 0.0f;
	double now = glfwGetTime();
	System::deltaTime = now - last;
	last = now;
}

double System::GetDeltaTime()
{
	return System::deltaTime;
}
