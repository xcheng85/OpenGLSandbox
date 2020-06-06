/**
 * Application.cpp
 * Contributors:
 *      * Xiao Cheng (author)
 * Licence:
 *      * MIT
 */

#pragma once

#include <string>

struct GLFWwindow;

namespace OpenGLSandbox
{
    namespace Common
    {
        class Application
        {
        public:
            Application(unsigned int width = 1920, unsigned int height = 1080, std::string title = "OpenGLSandbox");
            virtual ~Application(){};
            Application &operator=(const Application &) = delete;
            Application(const Application &) = delete;

            void run();

        protected:
            static void error_callback(int error, const char *description);
            static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
            static void resize_callback(GLFWwindow *window, int newWidth, int newHeight);

            GLFWwindow *window_;
            unsigned int width_;
            unsigned int height_;
            std::string title_;

            float time;
            float deltaTime;
        };
    } // namespace Common
} // namespace OpenGLSandbox
