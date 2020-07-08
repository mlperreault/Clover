#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>

#include "headers/glFunc.h"

//#define CE_VERBOSE

namespace ce {
    namespace Graphic {

        // Initialization of the internal state
        bool        GLFunc::InternalState::GLEW_INITIALIZED = false;
        bool        GLFunc::InternalState::GLFW_INITIALIZED = false;
        bool        GLFunc::InternalState::GLFUNC_READY = false;
        GLuint      GLFunc::InternalState::SHADER_PROGRAM_ID = 0;
        GLFWwindow* GLFunc::InternalState::CURRENT_CONTEXT_WINDOW = nullptr;
        GLuint      GLFunc::InternalState::BINDED_VAO = 0;


        void GLFunc::SetContextWindow(GLFWwindow* cw)
        {
            // avoid rebinding the same context
            if (cw != nullptr && InternalState::CURRENT_CONTEXT_WINDOW != cw)
            {
                glfwMakeContextCurrent(cw);
                InternalState::CURRENT_CONTEXT_WINDOW = cw;
                glfwSwapInterval(1);
#ifdef CE_VERBOSE
                std::cout << "Successfully set context window." << std::endl;
#endif
            }
        }

        GLFWwindow* GLFunc::CreateContextWindow(std::string title, int w, int h, bool set_current_context) {

            if (!InternalState::GLFW_INITIALIZED)
                init_glfw();

            if (!InternalState::GLFW_INITIALIZED)
            {
                std::cerr << "Failed to initialize GLFW." << std::endl;
                return nullptr;
            }

            GLFWwindow* win = CreateWindow(title, w, h);

            if (win == nullptr)
            {
                std::cerr << "Failed to create the window." << std::endl;
            }

            if (set_current_context)
                SetContextWindow(win);

            if (!InternalState::GLEW_INITIALIZED)
                init_glew();

            if (!InternalState::GLEW_INITIALIZED)
            {
                std::cerr << "Failed to initialize glew." << std::endl;
                TerminateGLFW();
            }

            InternalState::GLFUNC_READY = InternalState::GLEW_INITIALIZED &&
                InternalState::GLFW_INITIALIZED &&
                InternalState::CURRENT_CONTEXT_WINDOW != nullptr;

            return win;
        }

        void GLFunc::BindVAO(GLuint vao_id) {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");

            if (InternalState::BINDED_VAO != vao_id) {
                glBindVertexArray(vao_id);
                InternalState::BINDED_VAO = vao_id;
#ifdef CE_VERBOSE
                std::cout << "Binded VAO : " << vao_id << std::endl;
#endif
            }
        }

        void GLFunc::UnbindVao() {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");

            BindVAO(0);
        }

        void GLFunc::EnableAttribute(int attrib) {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");


            if (InternalState::BINDED_VAO != 0)
            {
                glEnableVertexAttribArray(attrib);
#ifdef CE_VERBOSE
                std::cout << "Enabled Attrib Array : " << attrib << std::endl;
#endif
            }
        }

        void GLFunc::DisableAttribute(int attrib) {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");

            if (InternalState::BINDED_VAO != 0)
            {
                glDisableVertexAttribArray(attrib);
#ifdef CE_VERBOSE
                std::cout << "Disabled Attrib Array : " << attrib << std::endl;
#endif
            }
        }

        GLuint GLFunc::GetVAO() {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");

            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);

#ifdef CE_VERBOSE
            std::cout << "Generated VAO id : " << VertexArrayID << std::endl;
#endif

            return VertexArrayID;
        }

        GLuint GLFunc::BindVBO(GLuint vao_id, vertices vertex_buffer, bool rebind_vao){
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");

#ifdef CE_VERBOSE
            std::cout << "Binding a VBO to VAO id : " << vao_id << std::endl;
#endif

            GLuint vertexBufferID;
            GLuint old_vao = 0;

            if (!vao_is_binded(vao_id)) {

#ifdef CE_VERBOSE
                std::cout << "VAO was not binded , binding VAO id : " << vao_id << std::endl;
#endif
                if (InternalState::BINDED_VAO != 0)
                {
                    old_vao = InternalState::BINDED_VAO;
                    GLFunc::UnbindVao();
                    rebind_vao = true;
                }
                
                GLFunc::BindVAO(vao_id);
                
            }

            // generate , bind and fill the VBO
            glGenBuffers(1, &vertexBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
            glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                vertex_buffer.size() / 3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );

            if (rebind_vao)
            {
                GLFunc::UnbindVao();
                GLFunc::BindVAO(old_vao);
            }

#ifdef CE_VERBOSE
            std::cout << "Generated VBO ID : " << vertexBufferID << std::endl;
#endif

            return vertexBufferID;
        }

        GLFWwindow* GLFunc::CreateWindow(std::string title, int w, int h)
        {

            auto window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);

            if (!window)
            {
                std::cerr << "Can not instantiate GLFW window." << std::endl;
                return nullptr;
            }

#ifdef CE_VERBOSE
            std::cout << "Created window titled [" << title << "] with size [" << w << " ," << h << std::endl;
#endif

            return window;
        }

        GLuint GLFunc::LoadShadersFromFiles(const char* vertex_file_path, const char* fragment_file_path) {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");

            // Create the shaders
            GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            // Read the Vertex Shader code from the file
            std::string VertexShaderCode;
            std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
            if (VertexShaderStream.is_open()) {
                std::stringstream sstr;
                sstr << VertexShaderStream.rdbuf();
                VertexShaderCode = sstr.str();
                VertexShaderStream.close();
            }
            else {
                printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
                getchar();
                return 0;
            }

            // Read the Fragment Shader code from the file
            std::string FragmentShaderCode;
            std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
            if (FragmentShaderStream.is_open()) {
                std::stringstream sstr;
                sstr << FragmentShaderStream.rdbuf();
                FragmentShaderCode = sstr.str();
                FragmentShaderStream.close();
            }

            return LoadStringShaders(VertexShaderCode, FragmentShaderCode);
        }

        GLuint GLFunc::LoadStringShaders(std::string VertexShaderCode, std::string FragmentShaderCode) {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");

#ifdef CE_VERBOSE
            std::cout << "Loading shaders" << std::endl;
#endif

            // Create the shaders
            GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            GLint Result = GL_FALSE;
            int InfoLogLength;

            // Compile Vertex Shader
            std::cout << "Compiling vertex shader." << std::endl;
            char const* VertexSourcePointer = VertexShaderCode.c_str();
            glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
            glCompileShader(VertexShaderID);

            // Check Vertex Shader
            glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0) {
                std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
                glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
                printf("%s\n", &VertexShaderErrorMessage[0]);
            }

            // Compile Fragment Shader
            std::cout << "Compiling fragment shader." << std::endl;
            char const* FragmentSourcePointer = FragmentShaderCode.c_str();
            glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
            glCompileShader(FragmentShaderID);

            // Check Fragment Shader
            glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0) {
                std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
                glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
                printf("%s\n", &FragmentShaderErrorMessage[0]);
            }

            // Link the program
            std::cout << "Linking Program" << std::endl;
            GLuint ProgramID = glCreateProgram();
            glAttachShader(ProgramID, VertexShaderID);
            glAttachShader(ProgramID, FragmentShaderID);
            glLinkProgram(ProgramID);

            // Check the program
            glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
            glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0) {
                std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
                glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
                printf("%s\n", &ProgramErrorMessage[0]);
            }

            glDetachShader(ProgramID, VertexShaderID);
            glDetachShader(ProgramID, FragmentShaderID);

            glDeleteShader(VertexShaderID);
            glDeleteShader(FragmentShaderID);

            return ProgramID;
        }

        bool GLFunc::vao_is_binded(GLuint vao_id) {
            return InternalState::BINDED_VAO == vao_id;
        }

        bool GLFunc::init_glew() {

            if (InternalState::GLEW_INITIALIZED)
                return true;

#ifdef CE_VERBOSE
            std::cout << "Initializing GLEW." << std::endl;
#endif

            glewExperimental = GL_TRUE;

            GLenum error = glewInit();

            if (error != GLEW_OK) {
                std::cerr << "GLEW error : " << glewGetErrorString(error) << std::endl;
                glfwTerminate();
                return false;
            }

            InternalState::GLEW_INITIALIZED = true;

#ifdef CE_VERBOSE
            std::cout << "GLEW initializede successfully." << std::endl;
#endif
            return true;
        }


        bool GLFunc::init_glfw() {

            if (InternalState::GLFW_INITIALIZED)
                return true;


#ifdef CE_VERBOSE
            std::cout << "Initializing GLFW" << std::endl;
#endif

            glfwSetErrorCallback(show_glfw_error);

            if (!glfwInit()) {
                std::cerr << "GLFW init failed." << std::endl;
                return false;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CE_OPENGL_MAJOR);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CE_OPENGL_MINOR);
            glfwWindowHint(GLFW_OPENGL_PROFILE, CE_GLFW_OPENGL_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, CE_GLFW_OPENGL_FORWARD_COMPAT);

            InternalState::GLFW_INITIALIZED = true;

#ifdef CE_VERBOSE
            std::cout << "GLFW initialized successfully." << std::endl;
#endif
            return true;
        }

        void GLFunc::show_glfw_error(int error, const char* description) {
            std::cerr << "Error[" << error << "] :" << description << '\n';
        }

        void GLFunc::TerminateGLFW()
        {
            glfwTerminate();
        }

        void GLFunc::UseShader(GLuint program_id)
        {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");

            if (program_id != InternalState::SHADER_PROGRAM_ID)
            {
#ifdef CE_VERBOSE
                std::cout  << "Setting shader program id to : " << program_id << std::endl;
#endif
                glUseProgram(program_id);
            }
        }

        GLuint GLFunc::GetShaderMatrixID(GLuint program_id, std::string matrix_name)
        {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");
            assert(program_id != 0 && "Shader program id is not valid.");
               
            return glGetUniformLocation(program_id, matrix_name.c_str());
        }

        void GLFunc::BindShaderMatrixData(GLuint matrix_id, float* data)
        {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");
            assert(matrix_id != -1 && "Shader matrix id is not valid.");

            glUniformMatrix4fv(matrix_id, 1, GL_FALSE, data);
        }

        void GLFunc::DrawArrays(GLenum mode, GLint start, GLsizei count)
        {
            assert(InternalState::GLFUNC_READY && "GLFunc is not Ready. CreateContextWindow( ) must be called first.");
            assert(InternalState::BINDED_VAO != 0 && "There is no binded vao.");

            glDrawArrays(GL_TRIANGLES, start, count);
        }

    }
}

