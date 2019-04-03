#ifndef SYSTEM_H
#define SYSTEM_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include "Window.h"


namespace System
{
	void InitialiseGLFW(unsigned int maj_version, unsigned int min_version);

	void InitialiseGLEW(System::Window* window);

	void CalcDeltaTime();

	double GetDeltaTime();

	extern double deltaTime;
}


#endif