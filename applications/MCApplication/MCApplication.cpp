#include "MCApplication.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

//#define SHADER_DIR "../shader/"

MCApplication::MCApplication(unsigned int width, unsigned int height, std::string title)
    : Application(width, height, title)
{
    // glCheckError(__FILE__, __LINE__);
}

void MCApplication::loop()
{

}

void MCApplication::loadShaders()
{
    
}