#ifndef GLFW_BACKEND_H
#define GLFW_BACKEND_H

#include "GLH.h"

struct GLFWwindow;

namespace pp
{
	class ICallbacks;
	
	class gl_backend
	{
	public:
		void GLBackendRun(ICallbacks* pCallbacks);
		void GLSwapBuffers(void);
		void GLPollEvents(void);
		void GLFWBackendTerminate(void);

		// Singleton class implementation
		static inline gl_backend* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new gl_backend();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	private:
		void initAllCB(void);

		gl_backend(void);
		~gl_backend(void);

		static gl_backend* s_instance;
		GLFWwindow* window;
	};
}
#endif

