#include"Settings.h"

void Settings::enable_vsync()
{
	glfwSwapInterval(1);
}

void Settings::enable_stencil()
{
	glEnable(GL_STENCIL_BUFFER_BIT);
}

void Settings::enable_depth()
{
	glEnable(GL_DEPTH_BUFFER_BIT);
}

void Settings::ClearScreen(GLfloat r, GLfloat g, GLfloat b)
{
	glClearColor(r, g, b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
