#include "window.h"

namespace ce {
    namespace graphic {

        GLuint getVertexArray()
        {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);

            return VertexArrayID;
        }

        GLuint bindVertexBuffer(
            GLuint vertex_array_id,
            vertices vertex_buffer)
        {
            GLuint vertexBufferID;

            glBindVertexArray(vertex_array_id);
            glGenBuffers(1, &vertexBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
            glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

            glBindVertexArray(0);

            return vertexBufferID;
        }

        // THIS SHOULD MOVE ELSEWHERE
        void show_glfw_error(int error, const char* description) {
            std::cerr << "Error: " << description << '\n';
        }

        void window_resized(GLFWwindow* wind, int width, int height) {
            std::cout << "Window resized, new window size: " << width << " x " << height << '\n';

            glClearColor(0, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(wind);
        }

        void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
            std::cout << "KEY PRESSED : " << key << std::endl;
            if (key == 'Q' && action == GLFW_PRESS) {
                glfwTerminate();
                exit(0);
            }
        }

        // WINDOW CLASS
        glWindow::glWindow()
            :
            glRenderer_{ this }
        {
            init_glfw();
            init_glew();
        }

        glWindow::~glWindow() {

            glfwDestroyWindow(glWindow_);
            glfwTerminate();
        }

        bool glWindow::isOpen() {
            return !glfwWindowShouldClose(glWindow_);
        }

        GLFWwindow* glWindow::getGLwindowPtr() {
            return glWindow_;
        }

        glWindow::glRenderer* glWindow::getRendererPtr() {
            return &glRenderer_;
        }

        bool glWindow::init_glew() {

            glewExperimental = GL_TRUE;

            GLenum error = glewInit();

            // TODO : Error handling and logs
            if (error != GLEW_OK) {
                std::cerr << "GLEW ERROR" << glewGetErrorString(error) << '\n';
                glfwTerminate();
                return false;
            }

            return true;
        }

        bool glWindow::init_glfw() {
            glfwSetErrorCallback(show_glfw_error);


            if (!glfwInit()) {
                std::cerr << "GLFW" << '\n';
                return false;
            }


            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


            glWindow_ = glfwCreateWindow(
                800, // width
                600, // height
                "OpenGL Example",
                NULL, NULL);
            if (!glWindow_)
            {
                std::cerr << "윈도우 생성 실패" << '\n';
                glfwTerminate();
                return false;
            }


            glfwMakeContextCurrent(glWindow_);

            glfwSetWindowSizeCallback(glWindow_, window_resized);
            glfwSetKeyCallback(glWindow_, key_pressed);


            glfwSwapInterval(1);

            return true;
        }


        // RENDERER CLASS
        glWindow::glRenderer::glRenderer(glWindow* w) {
            WindowHndl_ = w;
        }

        void glWindow::glRenderer::draw() {
            glfwSwapBuffers(WindowHndl_->getGLwindowPtr());

            //this should be moved into an event system
            glfwPollEvents();
        }

        void glWindow::glRenderer::setClearColor(color_f clrcolor) {
            glClearColor(clrcolor.r, clrcolor.g, clrcolor.b, clrcolor.a);
        }

        void glWindow::glRenderer::clear() {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void glWindow::glRenderer::drawTriangle(GLuint vertexarray, GLuint vertexbuffer) {

            glBindVertexArray(vertexarray);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
            glDisableVertexAttribArray(0);
            glBindVertexArray(0);
        }

    } // graphic namespace
} // ce namespace

