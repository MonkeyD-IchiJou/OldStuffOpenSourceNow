#ifndef WINDOW_CREATION_H
#define WINDOW_CREATION_H

#include <GLFW\glfw3.h>
#include <string>
using std::string;

namespace pp
{
	class GLFW_Window
	{
	public:
		// GLFW window object
		static GLFWwindow* m_window;
		static GLFWwindow* new_window;
		static GLFWmonitor* m_monitor;

		const GLFWvidmode* mode;

		// Singleton class implementation
		static inline GLFW_Window* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new GLFW_Window();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	public:
		void setUp(void);

		// destroy the current window
		void destroyWindow(void);

		// full screen toggle .. destroy prev window code included 
		void createFULLSCREEN(void);

		// defaultscreen toggle
		void createDEFAULTSCREEN(void);

		// set the window title
		void setWindowTitle(string title);

		// get and setters
		int getWindowWidth(void);
		int getWindowHeight(void);
		void setWidthAndHeight(int width, int height);

		int getMonitorWidth(void);
		int getMonitorHeight(void);

		int getWindowPosX(void);
		int getWindowPosY(void);
		void setWindowPosXAndY(int x, int y);

		bool getFullScreenInfo(void);

	private:
		// glfw need to be init before use
		void initGLFW(void);

		// window features 
		void initWindowHINT(void);

		// current monitor height and width
		void readCurrentMonitorINFO(void);

		// create window
		void createWINDOW(void);

		GLFW_Window(void);
		~GLFW_Window(void);

		// singleton properties
		static GLFW_Window* s_instance;

		// width of the window
		int m_width;

		// height of the window
		int m_height;

		// position x of the window
		int m_pos_x;

		// position y of the window
		int m_pos_y;

		// store the size of the monitor
		int m_monitor_size_width, m_monitor_size_height;

		// iconified state .. 0 is window appear .. 1 is minimized
		int iconified;

		// title of the window
		char *title;

		// check whether is full screen
		bool m_FullScreen;

	};
}


#endif

