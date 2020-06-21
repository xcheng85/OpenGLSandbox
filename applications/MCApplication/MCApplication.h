#pragma once

#include <Application.h>

using namespace OpenGLSandbox::Common;

class MCApplication : public Application
{
public:
    MCApplication(unsigned int width = 1920, unsigned int height = 1080, std::string title = "OpenGLSandbox");
    virtual ~MCApplication(){};

protected:
    virtual void loop();

private:
    void loadShaders();
};
