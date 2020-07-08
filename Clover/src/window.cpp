#include <iostream>

#include "headers/window.h"
#include "headers/glFunc.h"

namespace ce {
    namespace Graphic {

        /// <summary>
        ///     Constructor
        /// </summary>
        ceWindow::ceWindow(std::string title, std::size_t width, std::size_t height)
            : Title_{ title }, Width_{ width }, Height_{ height }
        {
            ceRenderer_ = ceRenderer{ this };
        }


        /// <summary>
        ///     Tells if the window is still open
        /// </summary>
        /// <returns> True or False </returns>
        bool ceWindow::isOpen() {
            return ceRenderer_.ContextIsRunning();
        }

        /// <summary>
        ///     Get a pointer on the window renderer
        /// </summary>
        /// <returns> A pointer on the window renderer </returns>
        ceWindow::ceRenderer* ceWindow::getRendererPtr() {
            return &ceRenderer_;
        }



        /// <summary>
        ///     Move constructor
        /// </summary>
        /// <param name="other"></param>
        ceWindow::ceWindow(ceWindow&& other) noexcept
            : Width_{ other.Width_ },
            Height_{ other.Height_ },
            Title_{ std::move(other.Title_) },
            ceRenderer_{ std::move(other.ceRenderer_) }
        {

        }

        /// <summary>
        ///     Move assignement
        /// </summary>
        /// <param name="other"></param>
        ceWindow& ceWindow::operator=(ceWindow&& other) noexcept
        {
            ceRenderer_ = std::move(other.ceRenderer_);
            Width_ = other.Width_;
            Height_ = other.Height_;
            Title_ = std::move(other.Title_);

            return *this;
        }

        /// <summary>
        ///     Constructor
        /// </summary>
        /// <param name="w"> Parent window handle pointer </param>
        ceWindow::ceRenderer::ceRenderer(ceWindow* w) {
            WindowHndl_ = w;

            ceWindow_ = GLFunc::CreateContextWindow(w->Title_, w->Width_, w->Height_);


            // Projection matrix : 90° Field of View, 1/1 ratio, display range : 0.1 unit <-> 100 units
            ProjectionMatrix_ = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);

            // Camera matrix
            CameraViewMatrix_ = glm::lookAt(
                glm::vec3(0,0,1), // Camera is at (0,0,1), in World Space
                glm::vec3(0, 0, 0), // and looks at the origin
                glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
            );

            ShaderProgramID_ = GLFunc::LoadStringShaders(CE_VERTEX_SHADER, CE_FRAGMENT_SHADER);
            GLFunc::UseShader(ShaderProgramID_);

            VAO_ID_ = GLFunc::GetVAO();
        }

        ceWindow::ceRenderer::ceRenderer()
        : WindowHndl_{ nullptr },
            ceWindow_{ nullptr },
            ProjectionMatrix_{},
            CameraViewMatrix_{},
            ShaderProgramID_{},
            VAO_ID_{0}
         {
            
         }

        /// <summary>
        ///     Move constructor
        /// </summary>
        /// <param name="other"></param>
        ceWindow::ceRenderer::ceRenderer(ceRenderer&& other) noexcept
        : WindowHndl_{ other.WindowHndl_ },
            ceWindow_{other.ceWindow_},
            ProjectionMatrix_{other.ProjectionMatrix_},
            CameraViewMatrix_{other.CameraViewMatrix_},
            ShaderProgramID_{other.ShaderProgramID_},
            VAO_ID_{other.VAO_ID_}
        {}

        /// <summary>
        ///     Move assignement
        /// </summary>
        /// <param name="other"></param>
        ceWindow::ceRenderer& ceWindow::ceRenderer::operator=(ceRenderer&& other) noexcept
        {
            WindowHndl_ = other.WindowHndl_;
            ceWindow_ = other.ceWindow_;
            ProjectionMatrix_ = other.ProjectionMatrix_;
            CameraViewMatrix_ = other.CameraViewMatrix_;
            ShaderProgramID_ = other.ShaderProgramID_;
            VAO_ID_ = other.VAO_ID_;

            return *this;
        }

        /// <summary>
        ///     Draw backbuffer to screen
        /// </summary>
        void ceWindow::ceRenderer::draw() {

            // Swap the buffers !
            glfwSwapBuffers(ceWindow_);

        }

        /// <summary>
        ///     Clear the window
        /// </summary>
        void ceWindow::ceRenderer::clear() {
            GLFunc::ClearBuffers();
        }

        void ceWindow::ceRenderer::drawTriangle(Triangle t) {

            
            // Model matrix : an identity matrix (model will be at the origin)
            glm::mat4 Model = CE_IDENTITY_MATRIX;

            // Our ModelViewProjection : multiplication of our 3 matrices
            glm::mat4 mvp = ProjectionMatrix_ * CameraViewMatrix_ * Model; // Remember, matrix multiplication is the other way around

             // talk to our VAO
            GLFunc::BindVAO(VAO_ID_);

            // Get the shader
            GLuint ShaderMatrixID_ = GLFunc::GetShaderMatrixID(ShaderProgramID_, "MVP");

            // Send our transformation to the currently bound shader, in the "MVP" uniform
            // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
            GLFunc::BindShaderMatrixData(ShaderMatrixID_, &mvp[0][0]);

            // enable the attributes array
            GLFunc::EnableAttribute(0);

            vertices v = vertices{
                t.point_1.x, t.point_1.y, t.point_1.z,
                t.point_2.x, t.point_2.y, t.point_2.z,
                t.point_3.x, t.point_3.y, t.point_3.z
            };

            GLuint VBO_ID = GLFunc::BindVBO( VAO_ID_, v);

            // Draw the triangle !
            GLFunc::DrawArrays(GL_TRIANGLES, 0, v.size()/3); // Starting from vertex 0; 3 vertices total -> 1 triangle

            // disable attributes and unbind to avoid errors
            GLFunc::DisableAttribute(0);
            GLFunc::UnbindVao();
        }

        bool ceWindow::ceRenderer::ContextIsRunning() {
            return ceWindow_ != nullptr && !GLFunc::WindowShouldClose(ceWindow_);
        }

        GLFWwindow* ceWindow::ceRenderer::GetContextWindow()
        {
            return ceWindow_;
        }

        void ceWindow::ceRenderer::resize(int width, int height)
        {
            // just clear and swapbuffer
            WindowHndl_->resize(width, height);
            clear();
            draw();
        }

    } // graphic namespace
} // ce namespace

