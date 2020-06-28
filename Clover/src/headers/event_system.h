#ifndef EVENT_SYSTEM_H_INCLUDED
#define EVENT_SYSTEM_H_INCLUDED

#include <vector>

#include "system.h"
#include "event_keys.h"
#include "window.h"

namespace ce {
	namespace Event {
		struct MousePosition {
			int x;
			int y;
		};

		/// <summary>
		///		Generic event struct
		/// </summary>
		/// <typeparam name="action_type">action type</typeparam>
		/// <typeparam name="key_type">key type</typeparam>
		template<class action_type, class key_type>
		struct Event {
			action_type action;
			key_type key;
			MousePosition mouse;
		};

		// Event types
		using KbEvent = Event<ceKbActionType, ceKbKeyType>;
		using MouseMovedEvent = Event<ceMouseMovedType, int>;
		using MouseActionEvent = Event<ceMouseActionType, ceMouseButtonType>;

		/// <summary>
		///		Generic Listener class
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template<class T>
		class Listener {
			public:
				virtual void receive(T) = 0;
		};

		// listener types
		using KbListener = Listener<KbEvent>;
		using MouseMovedListener = Listener<MouseMovedEvent>;
		using MouseActionListener = Listener<MouseActionEvent>;
		

		/// <summary>
		///		Receive and dispatch events emitted by GLFW
		/// </summary>
		class glEventSystem : public ce::Core::System {
			public:

				// constructor
				glEventSystem(ce::Graphic::glWindow* w);

				// not copyable
				glEventSystem(glEventSystem const&) = delete;
				glEventSystem& operator=(glEventSystem const&) = delete;

				// movable
				glEventSystem(glEventSystem&& other) noexcept;
				glEventSystem& operator=(glEventSystem&& other) noexcept;

				void update(int);

				// bind functions
				void bindKeyPressedListener(KbListener* listener);
				void bindMouseMovedListener(MouseMovedListener* listener);
				void bindMouseActionListener(MouseActionListener* listener);

			private:
				// static callbacks for glfw
				static void kb_action_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void mouse_moved_callback(GLFWwindow* window, double xpos, double ypos);
				static void mouse_action_callback(GLFWwindow* window, int button, int action, int mods);
				static void window_resized_callback(GLFWwindow* wind, int width, int height);
				
				// send functions
				void sendKbEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
				void sendMouseMovedEvent(GLFWwindow* window, int xpos, int ypos);
				void sendMouseActionEvent(GLFWwindow* window, int button, int action, int mods);

				// listeners list
				std::vector<KbListener*> KeyboardListeners_;
				std::vector<MouseMovedListener*> MouseMovedListeners_;
				std::vector<MouseActionListener*> MouseActionListeners_;

				ce::Graphic::glWindow* bindedWindow_;
		};
	}
}

#endif
