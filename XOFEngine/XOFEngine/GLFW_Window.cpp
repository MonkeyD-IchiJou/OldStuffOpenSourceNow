#include "GLFW_Window.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>


namespace pp
{
	GLFWwindow* GLFW_Window::m_window = nullptr;
	GLFWwindow* GLFW_Window::new_window = nullptr;
	GLFWmonitor* GLFW_Window::m_monitor = nullptr;
	GLFW_Window* GLFW_Window::s_instance = nullptr;

	// for glfw to set error callback
	static void Error_Callback(int error, const char* description)
	{
		fputs(description, stderr);
		_fgetchar();
	}

	GLFW_Window::GLFW_Window(void) :
		m_FullScreen(false),
		m_monitor_size_height(0),
		m_monitor_size_width(0),
		iconified(0),
		title("Bravely Dragon"),
		mode(nullptr)
	{
		m_width = 1280;
		m_height = 720;
		m_pos_x = 70;
		m_pos_y = 40;
	}

	GLFW_Window::~GLFW_Window(void)
	{
	}

	void GLFW_Window::setUp(void)
	{
		initGLFW();
		initWindowHINT();
		readCurrentMonitorINFO();
		createWINDOW();
	}

	void GLFW_Window::initGLFW(void)
	{
		//initialising glfw
		//Set the error callback
		glfwSetErrorCallback(Error_Callback);

		//Initialize GLFW
		if (!glfwInit())
		{
			exit(EXIT_FAILURE);
		}
	}

	void GLFW_Window::initWindowHINT(void)
	{
		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // opengl 4.5
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // dun want the old opengl
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_DECORATED, GL_TRUE); // let user see the decoration
	}

	void GLFW_Window::readCurrentMonitorINFO(void)
	{
		m_monitor = glfwGetPrimaryMonitor();
		mode = glfwGetVideoMode(m_monitor);

		m_monitor_size_height = mode->height;
		m_monitor_size_width = mode->width;
	}

	void GLFW_Window::createWINDOW(void)
	{
		m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);
		
		//If the window couldn't be created
		if (!m_window)
		{
			fprintf(stderr, "Failed to open GLFW window.\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwSetWindowPos(m_window, m_pos_x, m_pos_y);

		glfwMakeContextCurrent(m_window);
	}

	void GLFW_Window::destroyWindow(void)
	{
		glfwDestroyWindow(m_window);
	}

	void GLFW_Window::createFULLSCREEN(void)
	{
		m_FullScreen = true;

		new_window = glfwCreateWindow(m_monitor_size_width, m_monitor_size_height, title, m_monitor, m_window); 
		
		destroyWindow();

		// small window back to the new full screen window
		m_window = new_window;

		if (!m_window)
		{
			fprintf(stderr, "Failed to open GLFW window.\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(m_window);

		glViewport(0, 0, m_monitor_size_width, m_monitor_size_height);
	}

	void GLFW_Window::createDEFAULTSCREEN(void)
	{
		m_FullScreen = false;
		new_window = glfwCreateWindow(m_width, m_height, title, NULL, m_window);

		destroyWindow();

		// small window back to the new full screen window
		m_window = new_window;

		if (!m_window)
		{
			fprintf(stderr, "Failed to open GLFW window.\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(m_window);

		glViewport(0, 0, m_width, m_height);

	}
	void GLFW_Window::setWindowTitle(string title)
	{
		glfwSetWindowTitle(m_window, title.c_str());
	}
	int GLFW_Window::getWindowWidth(void)
	{
		return this->m_width;
	}
	int GLFW_Window::getWindowHeight(void)
	{
		return m_height;
	}
	void GLFW_Window::setWidthAndHeight(int width, int height)
	{
		this->m_width = width;
		this->m_height = height;
	}
	int GLFW_Window::getMonitorWidth(void)
	{
		return m_monitor_size_width;
	}
	int GLFW_Window::getMonitorHeight(void)
	{
		return m_monitor_size_height;
	}
	int GLFW_Window::getWindowPosX(void)
	{
		return m_pos_x;
	}
	int GLFW_Window::getWindowPosY(void)
	{
		return m_pos_y;
	}
	void GLFW_Window::setWindowPosXAndY(int x, int y)
	{
		this->m_pos_x = x;
		this->m_pos_y = y;
	}
	bool GLFW_Window::getFullScreenInfo(void)
	{
		return m_FullScreen;
	}
}


