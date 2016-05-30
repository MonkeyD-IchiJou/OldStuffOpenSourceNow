#include "Keyboard.h"

#include <memory>
#include "utils.h"

namespace pp
{
	Keyboard* Keyboard::s_instance = nullptr;

	void Keyboard::resetAllKeys(void)
	{
		ZERO_MEM(Keys);

		for (int i = 0; i < KEY_UNDEFINED; ++i)
		{
			for (int j = 1; j < KEY_STATE_UNDEFINED; ++j)
			{
				Keys[i][j] = false;
			}
			Keys[i][KEY_STATE_RELEASE] = true;
		}
	}

	void Keyboard::updateKey(const KEY & key, const KEY_STATE & action)
	{
		Keys[key][KEY_STATE_RELEASE] = false; // reinit to false for releasing state
		Keys[key][action] = true;
	}

	bool Keyboard::isKeyTouched(const KEY & key)
	{
		bool pressed = Keys[key][KEY_STATE_PRESS];
		Keys[key][KEY_STATE_PRESS] = false;
		return pressed;
	}

	bool Keyboard::isKeyHold(const KEY & key)
	{
		bool hold = Keys[key][KEY_STATE_REPEAT];
		Keys[key][KEY_STATE_REPEAT] = false;
		return hold;
	}

	bool Keyboard::isKeyPressed(const KEY & key)
	{
		return !Keys[key][KEY_STATE_RELEASE];
	}

	Keyboard::Keyboard(void)
	{
		ZERO_MEM(Keys);
	}

	Keyboard::~Keyboard(void)
	{
	}
}
