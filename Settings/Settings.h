#ifndef SETTINGS
#define SETTINGS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Settings {
public:

	void enable_vsync();

	void enable_depth();

	void enable_stencil();

	void ClearScreen(GLfloat r, GLfloat b, GLfloat g);

	void PrintSpecs();

private:
};

#endif