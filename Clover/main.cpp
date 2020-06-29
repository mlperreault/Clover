#include <iostream>

#include "src/headers/colors.h"
#include "src/headers/entity.h"
#include "src/headers/base_component.h"
#include "src/headers/event_system.h"
#include "src/headers/store.h"
#include "src/headers/core_components.h"

// Receive and handle keyboard events
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

// Receive and handle mouse clicks events
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

struct TemporaryStructJustToDraw2Triangles {

    TemporaryStructJustToDraw2Triangles() {

        this->T1_VAO_ID = ce::Graphic::getVertexArray();
        this->T1_VBO_ID = ce::Graphic::bindVertexBuffer(T1_VAO_ID, triangle_1_data);

        this->T2_VAO_ID = ce::Graphic::getVertexArray();
        this->T2_VBO_ID = ce::Graphic::bindVertexBuffer(T2_VAO_ID, triangle_2_data);

    }

    GLuint T1_VAO_ID;
    GLuint T2_VAO_ID;

    GLuint T1_VBO_ID;
    GLuint T2_VBO_ID;

    // 3 vectors of 3 vertices => vertices positions to draw the triangle
    ce::Graphic::vertices triangle_1_data = {
       -1.0f, -1.0f, 0.0f, //point1
       1.0f, -1.0f, 0.0f,  //point2
       0.0f,  0.0f, 0.0f,  //point3
    };

    // 3 vectors of 3 vertices => vertices positions to draw the triangle
    ce::Graphic::vertices triangle_2_data = {
       -1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
    };

};


int main()
{
    // Rendering
    ce::Graphic::glWindow w{ "Clover Engine - Test Window", 800, 600 };
    auto renderer = w.getRendererPtr();

    // Events
    ce::Event::glEventSystem event_system{ &w };

    // World
    ce::Core::Store store{};

    // Creating an entity with a position component
    auto game_entity_1 = ce::Core::Entity{0};
    auto entity_1_position = std::make_unique<ce::Core::Node>(game_entity_1, 10, 10, 0);
    auto entity_1_position_hndl = store.Add<ce::Core::Node>(std::move(entity_1_position)); // give component ownership to the store

    // move the entity and verify we did not work on a copy by asking back a handle on the component
    if (entity_1_position_hndl != nullptr) 
    {
        // move
        entity_1_position_hndl->x = 20;
        entity_1_position_hndl->y = 20;

        // ask back handle
        entity_1_position_hndl = store.Get<ce::Core::Node>(ce::Core::NODE_TYPE, game_entity_1);

        if (entity_1_position_hndl != nullptr) 
        {
            std::cout << "Successfully retrieved the component from the store." << std::endl;

            if (entity_1_position_hndl->x == 20 && entity_1_position_hndl->y == 20)
                std::cout << "The move work correctly and you did not work on a copy." << std::endl;
            else
                std::cout << "something is wrong : values did not change and you worked on a copy." << std::endl;
        }
        else {
            std::cout << "Something is wrong : the store Get() function returned a null pointer." << std::endl;
        }
    }

    // Bind the keyboard event listener to the event system
    Main_KBListener kb_main{};
    event_system.bindKeyPressedListener(&kb_main);

    // Bind the mouse clicks event listener to the event system
    Main_MouseActionListener ma_main{};
    event_system.bindMouseActionListener(&ma_main);

    // Let's just instantiate 2 triangles.
    TemporaryStructJustToDraw2Triangles triangles;

    
    // Start drawing operations
    renderer->setClearColor(WHITE);

    // main loop
    while (w.isOpen()) {
        renderer->clear(); // clear the backbuffer
        renderer->drawTriangle(triangles.T1_VAO_ID, triangles.T1_VBO_ID); // draw triangle 1 on backbuffer
        renderer->drawTriangle(triangles.T2_VAO_ID, triangles.T2_VBO_ID); // draw triangle 2 on backbuffer
        renderer->draw(); // swap the buffers !
        event_system.update(0); // update the event system
    }

    return 0;
}