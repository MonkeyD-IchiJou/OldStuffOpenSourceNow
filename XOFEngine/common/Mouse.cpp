#include "Mouse.h"
#include "utils.h"

namespace pp
{
	Mouse* Mouse::s_instance = nullptr;

	Mouse::Mouse(void) : l_pitch(0.f), l_yaw(0.f), mouseScroll(0.f), mouse_diff_x(0.f), mouse_diff_y(0.f), mouse_last_x(0.f), mouse_last_y(0.f), inBound(true), prevInbound(true)
	{
		resetALLKeysStates();
	}

	Mouse::~Mouse(void)
	{
	}

	void Mouse::setMousePos(const float & x, const float & y)
	{
		cursorPos.x = x;
		cursorPos.y = y;
	}

	void Mouse::setScrolling(const float & y)
	{
		mouseScroll = y;
	}

	void Mouse::updatePitchAndYaw(const float & dt)
	{
		// check whether got go out of the screen and come back or not
		if (prevInbound != inBound)
		{
			LastMousePosUpdate(cursorPos.x, cursorPos.y);
			prevInbound = inBound;
		}

		//// Calculate the difference in positions
		mouse_diff_x = cursorPos.x - mouse_last_x;
		mouse_diff_y = cursorPos.y - mouse_last_y;

		//Calculate the yaw and pitch
		l_yaw = mouse_diff_x * 0.0174555555555556f * dt; // * 3.142f / 180.0f;
		l_pitch = mouse_diff_y * 0.0174555555555556f * dt; // 3.142f / 180.0f );

		LastMousePosUpdate(cursorPos.x, cursorPos.y);
	}

	void Mouse::updateMouseCursorFontSpace(const float & windowWidth, const float& windowHeight, const float & dt)
	{
		cursorPosFont.Set( getMousePosX() / windowWidth, (getMousePosY() / windowHeight) * -1.f );
	}

	void Mouse::LastMousePosUpdate(const float & x, const float & y)
	{
		// Store the current position as the last position
		mouse_last_x = x;
		mouse_last_y = y;
	}

	float Mouse::getPitch(void) const
	{
		return l_pitch;
	}

	float Mouse::getYaw(void) const
	{
		return l_yaw;
	}

	vec2f Mouse::getMousePos(void) const
	{
		return cursorPos;
	}

	float Mouse::getMousePosX(void) const
	{
		return cursorPos.x;
	}

	float Mouse::getMousePosY(void) const
	{
		return cursorPos.y;
	}

	float Mouse::getScrolling(void) const
	{
		return mouseScroll;
	}

	bool Mouse::isInBound(void)
	{
		return inBound;
	}

	void Mouse::setInBound(const bool & inBound)
	{
		this->inBound = inBound;
	}

	void Mouse::updateKeyPressed(const MOUSE & key, const KEY_STATE & action)
	{
		mouseButt[key][action] = true;  // only press and release update here
		mouseButt[key][KEY_STATE_REPEAT] = true; // holding is true unless the action is release

		// when the action is release .. set holding state to false pls
		if (action == KEY_STATE_RELEASE)
		{
			mouseButt[key][KEY_STATE_REPEAT] = false;
		}
	}

	bool Mouse::isClick(const MOUSE & key)
	{
		return mouseButt[key][KEY_STATE_PRESS];
	}

	bool Mouse::isHold(const MOUSE & key)
	{
		return mouseButt[key][KEY_STATE_REPEAT];
	}

	void Mouse::resetALLKeysStates(void)
	{
		ZERO_MEM(mouseButt);
		for (int i = 0; i < MOUSE_UNDEFINED; ++i)
		{
			for (int j = 0; j < KEY_STATE_UNDEFINED; ++j)
			{
				mouseButt[i][j] = false;
			}
		}
	}

	void Mouse::resetKeyPressed(void)
	{
		for (int i = 0; i < MOUSE_UNDEFINED; ++i)
		{
			mouseButt[i][KEY_STATE_PRESS] = false;
		}
	}
}
