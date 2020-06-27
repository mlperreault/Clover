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

                        glRenderer(glWindow* w);

                        // draw operations
                        void clear();
                        void draw();
                        void drawTriangle(GLuint vertexarray, GLuint vertexbuffer);

                        // render options
                        void setClearColor(color_f clrcolor);

                    private:

                        // handle on the parent window
                        glWindow* WindowHndl_;

                }; // END glRender

                GLFWwindow* glWindow_;
                glRenderer glRenderer_;

                glWindow(std::string, std::size_t, std::size_t);
                ~glWindow();

                bool isOpen();

                GLFWwindow* getGLwindowPtr();
                glRenderer* getRendererPtr();

            private:
                bool init_glew();
                bool init_glfw();

                std::size_t Width_;
                std::size_t Height_;
                std::string Title_;

        }; // END glWindow
    }
}



#endif
