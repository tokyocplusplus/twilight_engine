#ifndef MESH_HANDLER
#define MESH_HANDLER
#include<vector>
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

struct MESH {
	std::vector<float> Vertices0;
	std::vector<float> Vertices1;
	std::vector<float> Vertices2;
	std::vector<float> Vertices3;
	std::vector<float> Vertices4;
	std::vector<float> Vertices5;
	std::vector<float> Vertices6;
	std::vector<float> Vertices7;
	uint32_t
		VAO0,
		VBO0;
	//TODO: calculate the full amount in one go, without user input except for vertices
	uint16_t VerticesCount;
	//To render a cube we need a total of 36 vertices (6 faces * 2 triangles * 3 vertices each).
	void init(int8_t num_of_faces, int8_t triangles_per_face, int8_t values_per_vertex);
	void drawTris();
	void bindVAO();
	void getError();
};

//TODO: USE THE VERTICES AND VAO PREDEFINED
void MESH::init(int8_t num_of_faces, int8_t triangles_per_face, int8_t values_per_vertex)
{
	VerticesCount = num_of_faces * triangles_per_face * values_per_vertex;
	std::cout << "DO NOT CALL THIS IN THE MAIN LOOP\n" << "ONLY CALL THE DRAW FUNCTION AFTER INIT HAS BEEN CALLED" << std::endl;
	std::cout << "wwww何で" << std::endl;
	printf("Generating VAO... ");
	glGenVertexArrays(1, &VAO0);
	printf("Done\n");
	glGenBuffers(1, &VBO0);
	glBindVertexArray(VAO0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBufferData(GL_ARRAY_BUFFER, Vertices0.size() * sizeof(float), Vertices0.data(), 0x88E4);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, 0x0, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, 0x0, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, 0x0, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void MESH::drawTris()
{
	glBindVertexArray(VAO0);
	glDrawArrays(GL_TRIANGLES, 0, VerticesCount);
	//std::cout << glGetError() << std::endl;
}

void MESH::getError() {
	printf("%d\n", glGetError());
}

void MESH::bindVAO() {
	glBindVertexArray(VAO0);
}

#endif //!MESH_HANDLER