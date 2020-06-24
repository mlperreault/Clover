#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <GL/glew.h>  
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <vector>

#include "colors.h"

/* clover engin namespace */
namespace ce {
    
    namespace graphic {

        using vertices = std::vector<GLfloat>;

        GLuint bindVertexBuffer(GLuint, vertices);
        GLuint getVertexArray();

        /* Encapsulate a GLFW (OpenGL) window */
        class glWindow {

        public:

            /* Class used for OpenGL draw operations */
            class glRenderer {

            public:

                glRenderer(glWindow* w);

                void draw();
                void clear();

                void setClearColor(color_f clrcolor);

                void drawTriangle(GLuint vertexarray, GLuint vertexbuffer);

            private:

                glWindow* WindowHndl_;
            };

            GLFWwindow* glWindow_;
            glRenderer glRenderer_;

            glWindow();
            ~glWindow();

            bool isOpen();

            GLFWwindow* getGLwindowPtr();
            glRenderer* getRendererPtr();

        private:
            bool init_glew();
            bool init_glfw();
        };

        void window_resized(GLFWwindow* window, int width, int height);
        void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
        void show_glfw_error(int error, const char* description);

    }
}



#endif
