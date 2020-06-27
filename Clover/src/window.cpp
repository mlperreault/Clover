#include "headers/window.h"

namespace ce {
    namespace graphic {

        // THIS SHOULD MOVE   V
        
        /// <summary>
        ///     Print the glfw error to the error stream
        /// </summary>
        /// <param name="error"> Error code </param>
        /// <param name="description"> Error description </param>
        void show_glfw_error(int error, const char* description) {
            std::cerr << "Error[" <<error <<"] :" << description << '\n';
        }

        /// <summary>
        ///     Window resized event callback
        /// </summary>
        /// <param name="wind"> The windows that has been resized </param>
        /// <param name="width"> New width </param>
        /// <param name="height"> New height </param>
        void window_resized(GLFWwindow* wind, int width, int height) {
            std::cout << "Window resized, new window size: " << width << " x " << height << '\n';

            glClearColor(0, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(wind);
        }

        /// <summary>
        ///     Key pressed event callback
        /// </summary>
        /// <param name="window"> Window that triggered the event </param>
        /// <param name="key"> The key value ( ex: 81 => 'Q' ) </param>
        /// <param name="scancode"></param>
        /// <param name="action"> GLFW action enum ( pressed , released .. ) </param>
        /// <param name="mods"></param>
        void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
            std::cout << "KEY PRESSED : " << key << std::endl;
            if (key == 'Q' && action == GLFW_PRESS) {
                glfwTerminate();
                exit(0);
            }
        }
        // THIS SHOULD MOVE   ^

        /// <summary>
        ///     Generate an OpenGL Vertex Array Object (VAO)
        /// </summary>
        /// <returns> The VAO ID </returns>
        GLuint getVertexArray()
        {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);

            return VertexArrayID;
        }

        /// <summary>
        ///     Generate and bind a Vertex Buffer Object(VBO) to a VAO
        /// </summary>
        /// <param name="vertex_array_id"> VAO ID returned by 'getVertexArray()' </param>
        /// <param name="vertex_buffer">The vertex buffer containing the vertices data</param>
        /// <returns> The VBO ID </returns>
        GLuint bindVertexBuffer(
            GLuint vertex_array_id,
            vertices vertex_buffer)
        {
            GLuint vertexBufferID;

            // talk with the VAO
            glBindVertexArray(vertex_array_id);

            // generate , bind and fill the VBO
            glGenBuffers(1, &vertexBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
            glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

            // enable the attributes array
            glEnableVertexAttribArray(0);

            // bind the vertices
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
            glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );

            // unbind attributes array and VAO
            glDisableVertexAttribArray(0);
            glBindVertexArray(0);

            return vertexBufferID;
        }

        /// <summary>
        ///     Constructor
        /// </summary>
        glWindow::glWindow()
            :
            glRenderer_{ this }
        {

            // GLFW MUST be initialized before glew
            init_glfw();
            init_glew();
        }

        /// <summary>
        ///     Destructor
        /// </summary>
        glWindow::~glWindow() {

            glfwDestroyWindow(glWindow_);
            glfwTerminate();
        }

        /// <summary>
        ///     Tells if the window is still open
        /// </summary>
        /// <returns> True or False </returns>
        bool glWindow::isOpen() {
            return !glfwWindowShouldClose(glWindow_);
        }

        /// <summary>
        ///     Get a pointer on the glfw window
        /// </summary>
        /// <returns> A Pointer on the glfw window </returns>
        GLFWwindow* glWindow::getGLwindowPtr() {
            return glWindow_;
        }

        /// <summary>
        ///     Get a pointer on the window renderer
        /// </summary>
        /// <returns> A pointer on the window renderer </returns>
        glWindow::glRenderer* glWindow::getRendererPtr() {
            return &glRenderer_;
        }

        /// <summary>
        ///     Initialize GLEW library
        /// </summary>
        /// <returns>true or false</returns>
        bool glWindow::init_glew() {

            glewExperimental = GL_TRUE;

            GLenum error = glewInit();

            if (error != GLEW_OK) {
                std::cerr << "GLEW error : " << glewGetErrorString(error) << '\n';
                glfwTerminate();

                // maybe usefull for error handling ?
                return false;
            }

            // maybe usefull for error handling ?
            return true;
        }

        /// <summary>
        ///     Initialize GLFW library
        /// </summary>
        /// <returns>true or false</returns>
        bool glWindow::init_glfw() {

            glfwSetErrorCallback(show_glfw_error);


            if (!glfwInit()) {
                std::cerr << "GLFW init failed." << '\n';

                // maybe usefull for error handling ?
                return false;
            }


            // some glfw parameters
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
                std::cerr << "Can not instantiate GLFW window." << '\n';
                glfwTerminate();

                // maybe usefull for error handling ?
                return false;
            }

            glfwMakeContextCurrent(glWindow_);

            // set event callbacks
            glfwSetWindowSizeCallback(glWindow_, window_resized);
            glfwSetKeyCallback(glWindow_, key_pressed);


            glfwSwapInterval(1);

            // maybe usefull for error handling ?
            return true;
        }


        /// <summary>
        ///     Constructor
        /// </summary>
        /// <param name="w"> Parent window handle pointer </param>
        glWindow::glRenderer::glRenderer(glWindow* w) {
            WindowHndl_ = w;
        }

        /// <summary>
        ///     Draw backbuffer to screen
        /// </summary>
        void glWindow::glRenderer::draw() {

            // Swap the buffers !
            glfwSwapBuffers(WindowHndl_->getGLwindowPtr());

            //this should be moved into an event system
            glfwPollEvents();
        }

        /// <summary>
        ///     Change the base clear color
        /// </summary>
        /// <param name="clrcolor"> New color (rgba) </param>
        void glWindow::glRenderer::setClearColor(color_f clrcolor) {
            glClearColor(clrcolor.r, clrcolor.g, clrcolor.b, clrcolor.a);
        }

        /// <summary>
        ///     Clear the window
        /// </summary>
        void glWindow::glRenderer::clear() {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        /// <summary>
        ///     Draw a triangle on the backbuffer
        /// </summary>
        /// <param name="vertexarray"> VAO ID </param>
        /// <param name="vertexbuffer"> VBO ID </param>
        void glWindow::glRenderer::drawTriangle(GLuint vertexarray, GLuint vertexbuffer) {

            // talk to our VAO
            glBindVertexArray(vertexarray);

            // enable the attributes array
            glEnableVertexAttribArray(0);


            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
            
            // disable attributes and unbind to avoid errors
            glDisableVertexAttribArray(0);
            glBindVertexArray(0);
        }

    } // graphic namespace
} // ce namespace

