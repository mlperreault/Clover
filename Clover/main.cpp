#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/headers/window.h"
#include "src/headers/colors.h"
#include "src/headers/entity.h"
#include "src/headers/base_component.h"

int main()
{
    ce::graphic::glWindow w{"Clover Engine - Test Window", 800, 600};
    auto e = ce::core::Entity{};
    //auto c = ce::core::Node{ e };
    auto r = w.getRendererPtr();

    // An array of 3 vectors which represents 3 vertices
    ce::graphic::vertices triangle_1_data = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  0.0f, 0.0f,
    };

    ce::graphic::vertices triangle_2_data = {
       -1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
    };

    GLuint vertexarrayID_1 = ce::graphic::getVertexArray();
    GLuint vertexbufferID_1 = ce::graphic::bindVertexBuffer(vertexarrayID_1, triangle_1_data);

    GLuint vertexarrayID_2 = ce::graphic::getVertexArray();
    GLuint vertexbufferID_2 = ce::graphic::bindVertexBuffer(vertexarrayID_2, triangle_2_data);

    r->setClearColor(WHITE);

    while (w.isOpen()) {
        r->clear();
        r->drawTriangle(vertexarrayID_1, vertexbufferID_1);
        r->drawTriangle(vertexarrayID_2, vertexbufferID_2);
        r->draw();
    }

    return 0;
}