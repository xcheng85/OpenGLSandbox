#include <iostream>
#include <vector>
#include <string>

#include <memory>

#include <Application.h>

using namespace std;
using namespace OpenGLSandbox::Common;

int main()
{
    std::unique_ptr<Application> app = std::make_unique<Application>();
    app->run();
}