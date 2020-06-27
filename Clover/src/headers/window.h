#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <GL/glew.h>  
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <vector>

#include "colors.h"

namespace ce {
    namespace graphic {

        const auto CE_OPENGL_MAJOR = 3;
        const auto CE_OPENGL_MINOR = 3;
        const auto CE_GLFW_OPENGL_PROFILE = GLFW_OPENGL_CORE_PROFILE;
        const auto CE_GLFW_OPENGL_FORWARD_COMPAT = GL_TRUE;

        using vertices = std::vector<GLfloat>;

        GLuint bindVertexBuffer(GLuint, vertices);
        GLuint getVertexArray();

        // EVENTS SHOULD BE MOVED INTO AN EVENT SYSTEM
        void window_resized(GLFWwindow* window, int width, int height);
        void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
        void show_glfw_error(int error, const char* description);

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

                        // draw operations
                        void clear();
                        void draw();
                        void drawTriangle(GLuint vertexarray, GLuint vertexbuffer);

                        // render options
                        void setClearColor(color<float> clrcolor) {
                            glClearColor(clrcolor.r, clrcolor.g, clrcolor.b, clrcolor.a);
                        };

                        void setClearColor(color<int> clrcolor) {
                            glClearColor(clrcolor.r/255.0f, clrcolor.g/255.0f, clrcolor.b/255.0f, clrcolor.a/255.0f);
                        };

                        // not copyable
                        glRenderer(glRenderer const&) = delete;
                        glRenderer& operator=(glRenderer const&) = delete;

                        // movable
                        glRenderer(glRenderer&& other) noexcept;
                        glRenderer& operator=(glRenderer&& other) noexcept;


                    private:
                        // handle on the parent window
                        glWindow* WindowHndl_;

                }; // END glRender

                glWindow(std::string, std::size_t, std::size_t);
                ~glWindow();

                bool isOpen();

                GLFWwindow* getGLwindowPtr();
                glRenderer* getRendererPtr();

                // not copyable
                glWindow(glWindow const&) = delete;
                glWindow& operator=(glWindow const&) = delete;

                // movable
                glWindow(glWindow&& other) noexcept;
                glWindow& operator=(glWindow&& other) noexcept;

            private:
                bool init_glew();
                bool init_glfw();

                GLFWwindow* glWindow_;
                glRenderer glRenderer_;

                std::size_t Width_;
                std::size_t Height_;
                std::string Title_;

        }; // END glWindow
    }
}



#endif
