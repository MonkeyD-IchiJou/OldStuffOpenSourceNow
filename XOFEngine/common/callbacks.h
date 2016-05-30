/*****************************************************************************/
//                                                                           //
//	this class serve as a bridge (link) for the glfw inputs callback         //
//                                                                           //
/*****************************************************************************/

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "keys.h"

namespace pp
{
	class ICallbacks
	{
	public:

		// key pressing callback from GLFW
		virtual void KeyboardCB(const KEY& Key, const KEY_STATE& action) {};

		// for typing 
		virtual void TYPE_NormalKeyCB(const KEY& Key) {};

		// mouse cursor position callback from GLFW
		virtual void MouseCursorCB(const double& x, const double& y) {};

		// mouse button key press from GLFW
		virtual void MouseButtCB(const KEY& Key, const KEY_STATE& action) {};

		// mouse cursor enter the screen or not callback from GLFW
		virtual void MouseCursorEnterCB(const bool& enter) {};

		// mouse scroll callback
		virtual void MouseScrollCB(const double& xoffset, const double& yoffset) {};

		// window resize callback from glfw. Width : New Window Width. Height : New Window Height
		virtual void WindowResizeCB(const int& width, const int& height) {};

		// window pos has changed 
		virtual void WindowPosCB(const int& x, const int& y) {};

		// window has minimised or not
		virtual void WindowIconifiyCB(const int& i) {};

		// window closing 
		virtual void WindowShldCloseCB(const int& i) {};
	};
}

#endif
