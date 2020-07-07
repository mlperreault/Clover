#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include "colors.h"
#include "utils.h"

namespace ce {
    namespace Graphic {

        // temporary string shader. TODO : Fix the load from files method.
        const std::string CE_VERTEX_SHADER =
            "#version 330 core \n\
            \n\
            layout(location = 0) in vec3 vertexPosition_modelspace;\n\
            uniform mat4 MVP;\n\
            void main() {\n\
                // Output position of the vertex, in clip space : MVP * position\n\
                gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
            }";

        // temporary string shader. TODO : Fix the load from files method.
        const std::string CE_FRAGMENT_SHADER =
            "#version 330 core\n\
            \n\
            out vec3 color;\n\
            \n\
            void main() {\n\
                color = vec3(0,0,1);\n\
            }";

        struct Triangle {
            ce::Core::fVec3 point_1;
            ce::Core::fVec3 point_2;
            ce::Core::fVec3 point_3;
        };

        const glm::mat4 CE_IDENTITY_MATRIX = glm::mat4(1.0f);

        /// <summary>
        ///     Encapsulate an OpenGL (glfw) window.
        /// </summary>
        class glWindow {
            public:

                /// <summary>
                ///     Class for draw operations in the window
                /// </summary>
                class glRenderer {

                public:
                    //move constructor private or protected and make window class friend ?
                    glRenderer(glWindow* w);
                    glRenderer();

                    // draw operations
                    void clear();
                    void draw();
                    void drawTriangle(Triangle t);

                    // render options
                    void setClearColor(color<float> clrcolor) {
                        glClearColor(clrcolor.r, clrcolor.g, clrcolor.b, clrcolor.a);
                    };

                    void setClearColor(color<int> clrcolor) {
                        glClearColor(clrcolor.r / 255.0f, clrcolor.g / 255.0f, clrcolor.b / 255.0f, clrcolor.a / 255.0f);
                    };

                    // not copyable
                    glRenderer(glRenderer const&) = delete;
                    glRenderer& operator=(glRenderer const&) = delete;

                    // movable
                    glRenderer(glRenderer&& other) noexcept;
                    glRenderer& operator=(glRenderer&& other) noexcept;

                    bool ContextIsRunning() {
                        return glWindow_ != nullptr && !glfwWindowShouldClose(glWindow_);
                    }

                    GLFWwindow* GetContextWindow()
                    {
                        return glWindow_;
                    }

                    void resize(int width, int height)
                    {
                        // just clear and swapbuffer
                        WindowHndl_->resize(width, height);
                        clear();
                        draw();
                    }

                    private:
                        // handle on the parent window
                        GLFWwindow* glWindow_;
                        glWindow* WindowHndl_;
                        GLuint ShaderProgramID_;
                        GLuint VAO_ID_;

                        glm::mat4 ProjectionMatrix_;
                        glm::mat4 CameraViewMatrix_;

                }; // END glRender

                glWindow(std::string, std::size_t, std::size_t);

                bool isOpen();

                glRenderer* getRendererPtr();

                // not copyable
                glWindow(glWindow const&) = delete;
                glWindow& operator=(glWindow const&) = delete;

                // movable
                glWindow(glWindow&& other) noexcept;
                glWindow& operator=(glWindow&& other) noexcept;

                void resize(int width, int height)
                {
                    //do nothing yet
                }

            private:
                glRenderer glRenderer_;

                std::size_t Width_;
                std::size_t Height_;
                std::string Title_;

        }; // END glWindow
    }
}



#endif
