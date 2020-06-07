#include <iostream>
#include <vector>
#include <string>

#include <memory>

#include "MCApplication.h"

using namespace std;
//using namespace OpenGLSandbox::Common;

int main()
{
    std::unique_ptr<MCApplication> app = std::make_unique<MCApplication>();
    app->run();
}