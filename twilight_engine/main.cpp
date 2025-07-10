#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define EXIT_SUCCESS 0
#define WIDTH 800
#define HEIGHT 600
#define TITLE "Pink Window"

int main()
{
    //intialize windowing backend
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    //initialize glfw version majors and minors
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create window object, set variables
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    //error checking to see if the window failed to create
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    //tell the window "hey, you can be used by a graphics API now"
    glfwMakeContextCurrent(window);
    //load all opengl function pointers (required for unsafe API calls)
    gladLoadGL();
  
    //set the render view to the top left of the window, and then the width and height
    glViewport(0, 0, W, H);
    //render loop
    while (!glfwWindowShouldClose(window))
    {
        //send data to the color buffer, and then clear the color buffer for the next refresh
        glClearColor(1.1f, 0.0f, 1.1f, 1.0f);  // bright pink
        glClear(GL_COLOR_BUFFER_BIT);

        //swap the buffers to ensure that the window isn't just a blank screen after the data is sent and cleared
        glfwSwapBuffers(window);
        //poll input events
        glfwPollEvents();
    }

    //after the render loop has ended, destroy the object(s) and free all memory to ensure no leaks, and optimal code.
    glfwDestroyWindow(window);
    glfwTerminate();
    //return an exit code to let the developer know that the application has ran perfectly (or at least, subpar).
    return EXIT_SUCCESS;
}
