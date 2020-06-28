#include <iostream>

#include "src/headers/colors.h"
#include "src/headers/entity.h"
#include "src/headers/base_component.h"
#include "src/headers/event_system.h"


class Main_KBListener : public ce::Event::KbListener {
public :
    void receive(ce::Event::KbEvent event) {
        if (event.action == ce::Event::CE_KEY_PRESSED) {
            std::cout << " KEY PRESSED : " << event.key << std::endl;
        }
        else if (event.action == ce::Event::CE_KEY_RELEASED) {
            std::cout << " KEY RELEASED : " << event.key << std::endl;
        }
        else if (event.action == ce::Event::CE_KEY_HOLD) {
            std::cout << " KEY HOLD : " << event.key << std::endl;
        }
    }
};

class Main_MouseMovedListener : public ce::Event::MouseMovedListener 
{
public:
    void receive(ce::Event::MouseMovedEvent event) {
        std::cout << "Mouse moved to position : " << event.mouse.x <<"," <<event.mouse.y << std::endl;
    }
};

class Main_MouseActionListener : public ce::Event::MouseActionListener {
public:
    void receive(ce::Event::MouseActionEvent event) {
        if (event.action == ce::Event::CE_MOUSE_PRESSED)
        {
            std::cout << "MOUSE PRESSED AT : " << event.mouse.x << "," << event.mouse.y << std::endl;
        }
        else if (event.action == ce::Event::CE_MOUSE_RELEASED) 
        {
            std::cout << "MOUSE RELEASED AT : " << event.mouse.x << "," << event.mouse.y << std::endl;
        }     
    }
};


int main()
{
    ce::Graphic::glWindow w{ "Clover Engine - Test Window", 800, 600 };
    auto e = ce::Core::Entity{};
    //auto c = ce::core::Node{ e };
    auto r = w.getRendererPtr();

    ce::Event::glEventSystem es{&w};

    Main_KBListener kb_main{};
    es.bindKeyPressedListener(&kb_main);

    Main_MouseMovedListener mm_main{};
    es.bindMouseMovedListener(&mm_main);

    Main_MouseActionListener ma_main{};
    es.bindMouseActionListener(&ma_main);

    // An array of 3 vectors which represents 3 vertices
    ce::Graphic::vertices triangle_1_data = {
       -1.0f, -1.0f, 0.0f, //point1
       1.0f, -1.0f, 0.0f,  //point2
       0.0f,  0.0f, 0.0f,  //point3
    };

    ce::Graphic::vertices triangle_2_data = {
       -1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
    };

    GLuint vertexarrayID_1 = ce::Graphic::getVertexArray();
    GLuint vertexbufferID_1 = ce::Graphic::bindVertexBuffer(vertexarrayID_1, triangle_1_data);

    GLuint vertexarrayID_2 = ce::Graphic::getVertexArray();
    GLuint vertexbufferID_2 = ce::Graphic::bindVertexBuffer(vertexarrayID_2, triangle_2_data);

    r->setClearColor(WHITE);

    while (w.isOpen()) {
        r->clear();
        r->drawTriangle(vertexarrayID_1, vertexbufferID_1);
        r->drawTriangle(vertexarrayID_2, vertexbufferID_2);
        r->draw();
        es.update(0);
    }

    return 0;
}