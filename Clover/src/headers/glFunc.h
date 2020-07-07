#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include <vector>

//#define CE_VERBOSE

namespace ce {
	namespace Graphic {

        // Open GL param constants
        const auto CE_OPENGL_MAJOR = 3;
        const auto CE_OPENGL_MINOR = 3;
        const auto CE_GLFW_OPENGL_PROFILE = GLFW_OPENGL_CORE_PROFILE;
        const auto CE_GLFW_OPENGL_FORWARD_COMPAT = GL_TRUE;

        using vertices = std::vector<GLfloat>;

        class GLFunc {
        public:
            // context creation
            static GLFWwindow*  CreateContextWindow(std::string title, int w, int h, bool set_current_context = true);
            static void         SetContextWindow(GLFWwindow* cw);

            // gl elements handling : VAO , VBO , VIO , NORMALS, UVS
            static GLuint GetVAO();
            static void BindVAO(GLuint vao_id);
            static void UnbindVao();

            static GLuint BindVBO(GLuint vao_id, vertices vertex_buffer, bool unbind_vao = false);

            static void EnableAttribute(int attrib);
            static void DisableAttribute(int attrib);
            
            // shaders loading
            static GLuint LoadShadersFromFiles(const char* vertex_file_path, const char* fragment_file_path);
            static GLuint LoadStringShaders(std::string VertexShaderCode, std::string FragmentShaderCode);

        private:

            // manage gl state and avoid useless gl call
            struct InternalState {
                static bool         GLEW_INITIALIZED;
                static bool         GLFW_INITIALIZED;
                static bool         GLFUNC_READY;
                static GLFWwindow*  CURRENT_CONTEXT_WINDOW;
                static GLuint       BINDED_VAO;
                static GLuint       SHADER_PROGRAM_ID;
            };

            static bool vao_is_binded(GLuint vao_id);
            static bool init_glew();
            static bool init_glfw();
            static void show_glfw_error(int error, const char* description);
            static void TerminateGLFW();
            static void UseShader(GLuint program_id);
            static GLFWwindow* CreateWindow(std::string title, int w, int h);

        };

        // Initialization of the internal state
        bool        GLFunc::InternalState::GLEW_INITIALIZED         = false;
        bool        GLFunc::InternalState::GLFW_INITIALIZED         = false;
        bool        GLFunc::InternalState::GLFUNC_READY             = false;
        GLuint      GLFunc::InternalState::SHADER_PROGRAM_ID        = 0;
        GLFWwindow* GLFunc::InternalState::CURRENT_CONTEXT_WINDOW   = nullptr;
        GLuint      GLFunc::InternalState::BINDED_VAO               = 0;
	}
}

#endif
