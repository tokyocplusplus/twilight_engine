#pragma once
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void clear_color(float r, float g, float b, float a)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, a);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
void idkprintme(const char* printableshit)
{
	std::cout << printableshit << std::endl;
}

void updateCamera(glm::vec3 cameraDirection, glm::vec3 up, glm::vec3 cameraPos, glm::vec3 cameraTarget)
{
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}