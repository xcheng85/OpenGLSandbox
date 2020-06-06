#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

using namespace OpenGLSandbox::Common;

Application::Application(unsigned int width, unsigned int height, std::string title) : width_(width), height_(height),
                                                                                       title_(title)
{
    glfwSetErrorCallback(error_callback);

    // initialize the GLFW library
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to init GLFW");
    }

    // setting the opengl version
    int major = 4;
    int minor = 5;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window
    window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window_)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create a window");
    }

    glfwSetKeyCallback(window_, key_callback);

    glfwMakeContextCurrent(window_);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        glfwTerminate();
        throw std::runtime_error(std::string("Failed to initialize GLEW, error = ") +
                                 (const char *)glewGetErrorString(err));
    }

    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;
}

void Application::run()
{
    // Make the window's context current
    glfwMakeContextCurrent(window_);

    while (!glfwWindowShouldClose(window_))
    {

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Application::error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Application::resize_callback(GLFWwindow *window, int newWidth, int newHeight)
{

}