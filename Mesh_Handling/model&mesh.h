#ifndef STUFF_H
#define STUFF_H
#include<glm/glm.hpp>
#include<vector>
#include<iostream>

//TODO: add texture and obj loading
//TODO: change vertex layout to match .obj files

struct Vertex
{
	glm::vec3 Position;
    glm::vec3 Colors;

    Vertex(float x, float y, float z, float r, float g, float b) : Position(x, y, z), Colors(r, g, b) 
    {
    }
};

struct vec3
{
    float // xyz coords, no math ops implemented yet
        x,
        y,
        z;

    vec3() : x(0), y(0), z(0) {}

    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // in-house replacement for glm::vec3()
};

struct vec4
{
    float // xyzw coords, no math ops implemented yet
        x,
        y,
        z,
        w;

    vec4() : x(0), y(0), z(0), w(0) {}

    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

class Mesh
{
public:
    glm::mat4 model;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;

        setup_mesh();
    }

    void setup_mesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

        // vertex positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // vertex colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0); // de-init vertex array for the next mesh object if possible
    }

    void assign_shader(unsigned int shaderProg)
    {
        shaderID = shaderProg;
    }

    void draw_mesh()
    {
        glUseProgram(shaderID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    }

    void setup_model_matrix()
    {
        modelLoc = glGetUniformLocation(shaderID, "model");
        model = glm::mat4(1.0f);
    }

    void rotate_mesh()
    {
        model = glm::rotate(model, 0.01f, glm::vec3(1.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    }

private:
    unsigned int VAO, VBO, EBO;
    uint32_t modelLoc;
    unsigned int shaderID;
};

#endif // no more STUFF_H :(
