#pragma once
#include<random>
#include<iostream>
#include<glm/glm.hpp>

struct vec3 {
    glm::vec3 data;

    vec3(float x, float y, float z) : data(x, y, z) {}

    // Implicit conversion to glm::vec3
    operator glm::vec3() const { return data; }

    // accessors for individual types and floats
    float x() const { return data.x; }
    float y() const { return data.y; }
    float z() const { return data.z; }
};


float randposf()
{
	srand(static_cast<unsigned int>(time(NULL)));

	int randomNumber = rand() % 3;

	return (float)randomNumber;
}