#include "gl_backend.h"
#include "callbacks.h"
#include "GLFW_Window.h"

namespace pp
{
	// Points to the object implementing the ICallbacks interface which was delivered to
	// GLBackendRun(). All events are forwarded to this object.
	static ICallbacks* s_pCallbacks = nullptr;
	gl_backend* gl_backend::s_instance = nullptr;

	static void KeyboardCB(GLFWwindow* window, int Key, int scancode, int action, int mods)
	{
		KEY glfwKey = (KEY)Key;
		KEY_STATE keyaction = (KEY_STATE)action;
		s_pCallbacks->KeyboardCB(glfwKey, keyaction);

		if (action != GLFW_RELEASE)
		{
			s_pCallbacks->TYPE_NormalKeyCB((KEY)Key);
		}
	}

	static void MouseCursorEnterCB(GLFWwindow* window, int enter)
	{
		// check whether got go out or not, the cursor
		// for now is like this
		s_pCallbacks->MouseCursorEnterCB(enter == 1 ? true:false);
	}

	static void PassiveMouseCB(GLFWwindow* window, double x, double y)
	{
		s_pCallbacks->MouseCursorCB(x, y);
	}

	static void MouseButtCB(GLFWwindow* window, int button, int action, int mods)
	{
		s_pCallbacks->MouseButtCB((KEY)button, (KEY_STATE)action);
	}

	static void MouseScrollCB(GLFWwindow* window, double xoffset, double yoffset)
	{
		s_pCallbacks->MouseScrollCB(xoffset, yoffset);
	}

	static void WindowShldCloseCB(GLFWwindow* window)
	{
		s_pCallbacks->WindowShldCloseCB(1);
	}

	static void WindowPosCB(GLFWwindow* window, int x, int y)
	{
		s_pCallbacks->WindowPosCB(x, y);
	}

	static void WindowResizeCB(GLFWwindow* window, int width, int height)
	{
		s_pCallbacks->WindowResizeCB(width, height);
	}

	gl_backend::gl_backend(void)
	{
		window = GLFW_Window::getInstance()->m_window;
	}

	gl_backend::~gl_backend(void)
	{
	}

	void gl_backend::GLBackendRun(ICallbacks * pCallbacks)
	{
		if (!pCallbacks)
		{
			printf("inapropriate scenes input callbacks, CB \n");
			throw 0;
		}

		// important one
		s_pCallbacks = pCallbacks;
		window = GLFW_Window::getInstance()->m_window;

		initAllCB();
	}


	void gl_backend::GLSwapBuffers(void)
	{
		glfwSwapBuffers(window);

	}

	void gl_backend::GLPollEvents(void)
	{
		glfwPollEvents();
	}

	void gl_backend::GLFWBackendTerminate(void)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void gl_backend::initAllCB(void)
	{
		glfwSetKeyCallback(window, KeyboardCB);
		glfwSetCursorEnterCallback(window, MouseCursorEnterCB);
		glfwSetCursorPosCallback(window, PassiveMouseCB);
		glfwSetMouseButtonCallback(window, MouseButtCB);
		glfwSetScrollCallback(window, MouseScrollCB);

		glfwSetWindowCloseCallback(window, WindowShldCloseCB);
		glfwSetWindowPosCallback(window, WindowPosCB);
		glfwSetWindowSizeCallback(window, WindowResizeCB);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}


