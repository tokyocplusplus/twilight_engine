// for opengl functions
#include <glad/glad.h>

// for GLFW functions
#include <GLFW/glfw3.h>

// for matrix operations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// standard lib
#include <iostream>

// local header files
#include "Settings/Settings.h"

// for any circular matrix operations, such as rotation around a radius or rendering a circle, or even a sphere
#define M_PI 3.14159265358979323846

// vertex shader source code
const char* vertexShaderSource = R"(
#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 vColor;
void main() {
    vColor = aColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
})";

// fragment shader source code
const char* fragmentShaderSource = R"(
#version 450 core
in vec3 vColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(vColor.xyz, 1.0f);
})";

float deltaTime = 0.0;
float currentFrame = 0.0;
float lastFrame = 0.0;

// vertices array for a cube
float vertices[] = {
    // VAL1 = VERTEX,    // VAL2 = COLOR
    -0.5f, -0.5f, -0.5f,  1.0f,1.0f,0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,1.0f,0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,1.0f,0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,1.0f,1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,1.0f,1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,1.0f,1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,1.0f,1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,1.0f,1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,1.0f,1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f,0.0f,0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,0.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f,0.0f,0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,0.0f,0.0f,

     0.5f,  0.5f,  0.5f,  0.0f,0.0f,1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,0.0f,1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,0.0f,1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,0.0f,1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,0.0f,1.0f,

    -0.5f, -0.5f, -0.5f,  1.0f,0.0f,1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,0.0f,1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,0.0f,1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,0.0f,1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f,0.0f,1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,0.0f,1.0f,

    -0.5f,  0.5f, -0.5f,  1.0f,0.5f,0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,0.5f,0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,0.5f,0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,0.5f,0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,0.5f,0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,0.5f,0.0f,
};

float camX, camY, camZ;
// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// mouse
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// main function (always runs on the main thread)
int main() {
    Settings settings;
    // Initialize GLFW and create the Window Pointer Object
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Spinning Cube", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Initialize OpenGL function pointers
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Create Vertex Array Object and Vertex Buffer Object
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object and the Vertex Buffer Object
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Enable data sending to the GPU, all in strides of 12 bytes
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Send data. Since the date is only 9 bytes, it has to send a 'fake' block of 3 bytes in order to match the GPU's wants and needs regarding memory safety
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    // Create vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create full linked shader
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // VARIABLES
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glm::mat4 
        model,
        view,
        projection;

    // Enable the depth buffer bit
    glEnable(GL_DEPTH_TEST);

    // Enable vSync
    settings.enable_vsync();


    // Main window loop, runs every frame
    while (!glfwWindowShouldClose(window)) {

        // Clear the color black on the back buffer
        glClearColor(0, 0, 0, 1);

        // Clear the color buffer bit for color and the depth buffer bit for triangle order and rendering support
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        std::cout << deltaTime << std::endl;

        /*----- MATRICES -----*/

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

        // Set the model matrix to make the cube rotate a bit
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Create view matrix
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Create projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        processInput(window);

        /*----- MATRICES -----*/


        // Bind the vertex data
        glBindVertexArray(VAO);

        // Use the glDrawArrays() function to send a static draw call each frame, to the GPU
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap the front and back buffers as soon as the back buffer is finished rendering.
        glfwSwapBuffers(window);

        // Poll input events (currently not needed)
        glfwPollEvents();
    }

    // free the GLFWwindow* object
    glfwTerminate();

    // successful launch
    return 0x0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(5.0 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += glm::normalize(cameraUp) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= glm::normalize(cameraUp) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}