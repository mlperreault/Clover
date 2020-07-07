#include "headers/event_system.h"

namespace ce {
	namespace Event {

		/// <summary>
		///		Constructor. This event system may only be binded once to a window. Unbinded event system won't dispatch events. Use 1 event system by window.
		/// </summary>
		/// <param name="w">Window from which the event system will receive events</param>
		glEventSystem::glEventSystem(ce::Graphic::glWindow::glRenderer* w)
		{
			if (w)
			{
				auto const window = w->GetContextWindow();
				// see if there is already an event system pointer for this window
				auto es = static_cast<glEventSystem*>(glfwGetWindowUserPointer(window));

				if (es == nullptr) { // just 1 event system by window !

					// store a pointer on this event class into glfw
					// to get it back into the callbacks
					glfwSetWindowUserPointer(window, this);

					glfwSetKeyCallback(window, kb_action_callback);
					glfwSetCursorPosCallback(window, mouse_moved_callback);
					glfwSetMouseButtonCallback(window, mouse_action_callback);
					glfwSetWindowSizeCallback(window, window_resized_callback);

					bindedWindow_ = w;
					return;
				}
			}

			bindedWindow_ = nullptr;
		}

		/// <summary>
		///		Move constructor
		/// </summary>
		/// <param name="other">Event system to move</param>
		glEventSystem::glEventSystem(glEventSystem&& other) noexcept 
		:	KeyboardListeners_{std::move(other.KeyboardListeners_)},
			bindedWindow_{other.bindedWindow_}
		{}

		/// <summary>
		///		Move assignement
		/// </summary>
		/// <param name="other">Event system to move</param>
		glEventSystem& glEventSystem::operator=(glEventSystem&& other) noexcept
		{
			KeyboardListeners_ = std::move(other.KeyboardListeners_);
			bindedWindow_ = other.bindedWindow_;

			return *this;
		}

		/// <summary>
		///		Bind a keyboard listener to receive keyboard events
		/// </summary>
		/// <param name="listener">The listener to bind to this system</param>
		void glEventSystem::bindKeyPressedListener(KbListener* listener)
		{
			if (listener != nullptr)
				KeyboardListeners_.push_back(listener);
		};

		/// <summary>
		///		Bind a mouse moved listener to receive mouse the new mouse position
		/// </summary>
		/// <param name="listener">The listener to bind to this system</param>
		void glEventSystem::bindMouseMovedListener(MouseMovedListener* listener)
		{
			if (listener != nullptr)
				MouseMovedListeners_.push_back(listener);
		};

		/// <summary>
		///		Bind a mouse action listener to receive mouse button release/press and position
		/// </summary>
		/// <param name="listener">The listener to bind to this system</param>
		void glEventSystem::bindMouseActionListener(MouseActionListener* listener)
		{
			if (listener != nullptr)
				MouseActionListeners_.push_back(listener);
		};


		/// <summary>
		///		Poll and send the events
		/// </summary>
		/// <param name="time_delta">Time elapsed since the last call for update control</param>
		void glEventSystem::update(int time_delta)
		{
			// do not poll events if the system is not binded to window
			// which happens when trying to bind 2 glEventSystem to a same window
			if (bindedWindow_ != nullptr)
				glfwPollEvents();
		}

		/// <summary>
		///		Send the keyboard action to the listeners
		/// </summary>
		void glEventSystem::sendKbEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			for (auto listener : KeyboardListeners_) {
				listener->receive(KbEvent{ action,key });
			}
		}
		
		/// <summary>
		///		GLFW keyboard action callback
		/// </summary>
		void glEventSystem::kb_action_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			// get back the pointer on this system stored by glfw (see constructor)
			// to send the action to the listeners
			glEventSystem* es = static_cast<glEventSystem*>(glfwGetWindowUserPointer(window));
			
			if(es != nullptr)
				es->sendKbEvent(window, key, scancode, action, mods);
		}

		/// <summary>
		///		Send the mouse movement event to the listeners
		/// </summary>
		void glEventSystem::sendMouseMovedEvent(GLFWwindow* window, int xpos, int ypos)
		{
			for (auto listener : MouseMovedListeners_) {
				listener->receive(MouseMovedEvent{ 0, 0, MousePosition{xpos,ypos}});
			}
		}
		

		/// <summary>
		///		GLFW mouse moved callback
		/// </summary>
		/// <param name="window">GLFW window that triggered the event</param>
		/// <param name="xpos">New mouse X position</param>
		/// <param name="ypos">New mouse Y position</param>
		void glEventSystem::mouse_moved_callback(GLFWwindow* window, double xpos, double ypos)
		{
			// get back the pointer on this system stored by glfw (see constructor)
			// to send the action to the listeners
			glEventSystem* es = static_cast<glEventSystem*>(glfwGetWindowUserPointer(window));
			
			if(es != nullptr)
				es->sendMouseMovedEvent(window, xpos, ypos);
		}

		/// <summary>
		///		Send the mouse action event to the listeners
		/// </summary>
		void glEventSystem::sendMouseActionEvent(GLFWwindow* window, int button, int action, int mods)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			for (auto listener : MouseActionListeners_) {
				listener->receive(MouseActionEvent{ action, button, MousePosition{(int)xpos,(int)ypos} });
			}
		}

		/// <summary>
		///		GLFW mouse action callback
		/// </summary>
		/// <param name="window">Window that triggered the event</param>
		/// <param name="button">Mouse button</param>
		/// <param name="action">Press or release</param>
		/// <param name="mods"></param>
		void glEventSystem::mouse_action_callback(GLFWwindow* window, int button, int action, int mods)
		{
			// get back the pointer on this system stored by glfw (see constructor)
			// to send the action to the listeners
			glEventSystem* es = static_cast<glEventSystem*>(glfwGetWindowUserPointer(window));
			
			if(es != nullptr)
				es->sendMouseActionEvent(window, button, action, mods);
		}

		/// <summary>
		///     Window resized event callback
		/// </summary>
		/// <param name="wind"> The windows that has been resized </param>
		/// <param name="width"> New width </param>
		/// <param name="height"> New height </param>
		void glEventSystem::window_resized_callback(GLFWwindow* window, int width, int height) {
			// get back the pointer on this system stored by glfw (see constructor)
			// to send the action to the listeners
			glEventSystem* es = static_cast<glEventSystem*>(glfwGetWindowUserPointer(window));
			
			if(es != nullptr)
				es->bindedWindow_->resize(width, height); // let the window deal with resizing !
		}
	}
}