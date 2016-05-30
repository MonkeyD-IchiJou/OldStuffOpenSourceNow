#ifndef MOUSE_H
#define MOUSE_H

#include "vec2.h"
#include "keys.h"
using namespace Math;

namespace pp
{

	class Mouse
	{
	public:
		// set the mousepos
		void setMousePos(const float& x, const float& y);

		// set scroll
		void setScrolling(const float& y);

		// update the pitch and yaw
		void updatePitchAndYaw(const float& dt);

		// update the mouse pos in correct font space
		void updateMouseCursorFontSpace(const float & windowWidth, const float& windowHeight, const float & dt);

		// get the mouse cursor moving up/down info
		float getPitch(void) const;

		// get the mouse cursor moving left/right info
		float getYaw(void) const;

		// get x and y pos of mouse cursor in float
		vec2f getMousePos(void) const;

		// get x position in float
		float getMousePosX(void) const;

		// get y position in float
		float getMousePosY(void) const;

		// get scrolling
		float getScrolling(void) const;

		// get the bound info, whether the cursor is inside the window or not
		bool isInBound(void);

		// set the info whether the cursor in inside the window or not
		void setInBound(const bool& inBound);

		// update the key inputs state
		void updateKeyPressed(const MOUSE& key, const KEY_STATE& action);

		// check whether got click the mouse button or not
		bool isClick(const MOUSE& key);

		// check whether the user is holding the mouse button or not
		bool isHold(const MOUSE& key);

		// reset all the key data to false
		void resetALLKeysStates(void);

		// reset all the key press to false
		void resetKeyPressed(void);

		vec2f cursorPosFont;

		// Singleton class implementation
		static inline Mouse* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new Mouse();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	protected:
		void LastMousePosUpdate(const float& x, const float& y);

	private:
		// singleton properties
		static Mouse* s_instance;

		// pitch and yaw
		float l_pitch, l_yaw;

		// the mouse cursor position
		vec2f cursorPos;

		// used for calculation of pitch and yaw
		float mouse_diff_x, mouse_diff_y, mouse_last_x, mouse_last_y;

		// scrolling
		float mouseScroll;

		// whether cursor inside the window or not
		bool inBound, prevInbound;

		bool mouseButt[MOUSE_UNDEFINED][KEY_STATE_UNDEFINED];

		Mouse(void);
		~Mouse(void);
	};
}

#endif
