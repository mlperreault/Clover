#ifndef EVENT_KEYS_H_INCLUDED
#define EVENT_KEYS_H_INCLUDED

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

namespace ce {
	namespace Event {

		/*
			ACTIONS
		*/

		// keyboard actions
		using ceKbActionType = decltype(GLFW_PRESS);

		auto const CE_KEY_PRESSED	= GLFW_PRESS;
		auto const CE_KEY_RELEASED	= GLFW_RELEASE;
		auto const CE_KEY_HOLD		= GLFW_REPEAT;

		// mouse actions
		using ceMouseActionType = decltype(GLFW_PRESS);
		using ceMouseMovedType = int;

		auto const CE_MOUSE_PRESSED = GLFW_PRESS;
		auto const CE_MOUSE_RELEASED = GLFW_RELEASE;
		auto const CE_MOUSE_MOVED = 1;

		/*
			KEYS
		*/

		// mouse keys
		using ceMouseButtonType = decltype(GLFW_MOUSE_BUTTON_RIGHT);
		
		auto const CE_MOUSE_R = GLFW_MOUSE_BUTTON_RIGHT;
		auto const CE_MOUSE_L = GLFW_MOUSE_BUTTON_LEFT;

		// keyboard keys 
		using ceKbKeyType = decltype(GLFW_KEY_UNKNOWN);

		auto const CE_KEY_UNKNOWN	= GLFW_KEY_UNKNOWN;

		// Controls
		auto const CE_KEY_SPACE		= GLFW_KEY_SPACE;
		auto const CE_KEY_ESCAPE	= GLFW_KEY_ESCAPE;
		auto const CE_KEY_ENTER		= GLFW_KEY_ENTER;
		auto const CE_KEY_TAB		= GLFW_KEY_TAB;
		auto const CE_KEY_BACKSPACE	= GLFW_KEY_BACKSPACE;
		auto const CE_KEY_DELETE	= GLFW_KEY_DELETE;
		auto const CE_KEY_SHIFT_L	= GLFW_KEY_LEFT_SHIFT;
		auto const CE_KEY_SHIFT_R	= GLFW_KEY_RIGHT_SHIFT;
		auto const CE_KEY_CONTROL_L	= GLFW_KEY_LEFT_CONTROL;
		auto const CE_KEY_CONTROL_R	= GLFW_KEY_RIGHT_CONTROL;
		auto const CE_KEY_ALT_L		= GLFW_KEY_LEFT_ALT;
		auto const CE_KEY_ALT_R		= GLFW_KEY_RIGHT_ALT;

		// Arrows
		auto const CE_KEY_RIGHT = GLFW_KEY_RIGHT;
		auto const CE_KEY_LEFT	= GLFW_KEY_LEFT;
		auto const CE_KEY_UP	= GLFW_KEY_UP;
		auto const CE_KEY_DOWN	 = GLFW_KEY_DOWN;

		// Function keys
		auto const CE_KEY_F1 = GLFW_KEY_F1;
		auto const CE_KEY_F2 = GLFW_KEY_F2;
		auto const CE_KEY_F3 = GLFW_KEY_F3;
		auto const CE_KEY_F4 = GLFW_KEY_F4;
		auto const CE_KEY_F5 = GLFW_KEY_F5;
		auto const CE_KEY_F6 = GLFW_KEY_F6;
		auto const CE_KEY_F7 = GLFW_KEY_F7;
		auto const CE_KEY_F8 = GLFW_KEY_F8;
		auto const CE_KEY_F9 = GLFW_KEY_F9;
		auto const CE_KEY_F10 = GLFW_KEY_F10;
		auto const CE_KEY_F11 = GLFW_KEY_F11;
		auto const CE_KEY_F12 = GLFW_KEY_F12;

		// Symbols
		auto const CE_KEY_APOSTROPHE	= GLFW_KEY_APOSTROPHE;
		auto const CE_KEY_COMMA			= GLFW_KEY_COMMA;
		auto const CE_KEY_MINUS			= GLFW_KEY_MINUS;
		auto const CE_KEY_PERIOD		= GLFW_KEY_PERIOD;
		auto const CE_KEY_SLASH			= GLFW_KEY_SLASH;
		auto const CE_KEY_BACKSLASH		= GLFW_KEY_BACKSLASH;
		auto const CE_KEY_SEMICOLON		= GLFW_KEY_SEMICOLON;
		auto const CE_KEY_EQUAL			= GLFW_KEY_EQUAL;
		auto const CE_KEY_BRACKET_L		= GLFW_KEY_LEFT_BRACKET;
		auto const CE_KEY_BRACKET_R		= GLFW_KEY_RIGHT_BRACKET;

		// Numbers
		auto const CE_KEY_0	= GLFW_KEY_0;
		auto const CE_KEY_1	= GLFW_KEY_1;
		auto const CE_KEY_2	= GLFW_KEY_2;
		auto const CE_KEY_3	= GLFW_KEY_3;
		auto const CE_KEY_4	= GLFW_KEY_4;
		auto const CE_KEY_5	= GLFW_KEY_5;
		auto const CE_KEY_6	= GLFW_KEY_6;
		auto const CE_KEY_7	= GLFW_KEY_7;
		auto const CE_KEY_8	= GLFW_KEY_8;
		auto const CE_KEY_9	= GLFW_KEY_9;

		// Letters
		auto const CE_KEY_A = GLFW_KEY_A;
		auto const CE_KEY_B = GLFW_KEY_B;
		auto const CE_KEY_C = GLFW_KEY_C;
		auto const CE_KEY_D = GLFW_KEY_D;
		auto const CE_KEY_E = GLFW_KEY_E;
		auto const CE_KEY_F = GLFW_KEY_F;
		auto const CE_KEY_G = GLFW_KEY_G;
		auto const CE_KEY_H = GLFW_KEY_H;
		auto const CE_KEY_I = GLFW_KEY_I;
		auto const CE_KEY_J = GLFW_KEY_J;
		auto const CE_KEY_K = GLFW_KEY_K;
		auto const CE_KEY_L = GLFW_KEY_L;
		auto const CE_KEY_M = GLFW_KEY_M;
		auto const CE_KEY_N = GLFW_KEY_N;
		auto const CE_KEY_O = GLFW_KEY_O;
		auto const CE_KEY_P = GLFW_KEY_P;
		auto const CE_KEY_Q = GLFW_KEY_Q;
		auto const CE_KEY_R = GLFW_KEY_R;
		auto const CE_KEY_S = GLFW_KEY_S;
		auto const CE_KEY_T = GLFW_KEY_T;
		auto const CE_KEY_U = GLFW_KEY_U;
		auto const CE_KEY_V = GLFW_KEY_V;
		auto const CE_KEY_W = GLFW_KEY_W;
		auto const CE_KEY_X = GLFW_KEY_X;
		auto const CE_KEY_Y = GLFW_KEY_Y;
		auto const CE_KEY_Z = GLFW_KEY_Z;

/*
	GLFW_KEY_KP_0   320
	GLFW_KEY_KP_1   321
	GLFW_KEY_KP_2   322
	GLFW_KEY_KP_3   323
	GLFW_KEY_KP_4   324
	GLFW_KEY_KP_5   325
	GLFW_KEY_KP_6   326
	GLFW_KEY_KP_7   327
	GLFW_KEY_KP_8   328
	GLFW_KEY_KP_9   329
	GLFW_KEY_KP_DECIMAL   330
	GLFW_KEY_KP_DIVIDE   331
	GLFW_KEY_KP_MULTIPLY   332
	GLFW_KEY_KP_SUBTRACT   333
	GLFW_KEY_KP_ADD   334
	GLFW_KEY_KP_ENTER   335
	GLFW_KEY_KP_EQUAL   336
*/

	}
}

#endif
