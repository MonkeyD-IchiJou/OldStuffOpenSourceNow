#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "keys.h"

namespace pp
{

	class Keyboard
	{
	public:
		
		// reset all the keys and its state to false 
		void resetAllKeys(void);

		// set the specifice key to true 
		void updateKey(const KEY& key, const KEY_STATE& action);

		// check if the specific key is pressed for that frame .. if holding then cannot
		bool isKeyTouched(const KEY& key);

		// is the user holding the key
		bool isKeyHold(const KEY& key);

		// normal key checking .. sensitivity high
		bool isKeyPressed(const KEY& key);

		// Singleton class implementation
		static inline Keyboard* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new Keyboard();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	private:
		// singleton properties
		static Keyboard* s_instance;

		bool Keys[KEY_UNDEFINED][KEY_STATE_UNDEFINED];

		Keyboard(void);
		~Keyboard(void);
	};
}

#endif
