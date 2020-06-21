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
            static void focus_callback(GLFWwindow *window, int focus);
            static void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);
            static void mouseMove_callback(GLFWwindow* window, double xoffset, double yoffset);


            virtual void loop() = 0;

            GLFWwindow *window_;
            unsigned int width_;
            unsigned int height_;
            std::string title_;

            // gl version
            unsigned int majorVersion_;
            unsigned int minVersion_;


        };
    } // namespace Common
} // namespace OpenGLSandbox
