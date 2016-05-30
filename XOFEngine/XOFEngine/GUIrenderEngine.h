#ifndef GUI_GRAPHIC_ENGINE_H
#define GUI_GRAPHIC_ENGINE_H

#include <string>
using std::string;

namespace pp
{
	class GLFW_Window;
	class FontShader;
	class FontType;

	class Entity;

	class World;

	class GUIrenderEngine
	{
	public:
		void setUp(void);
		void Update(const float &dt);
		void renderGUI(const World& world) const;

		string typestr;

		// Singleton class implementation
		static inline GUIrenderEngine* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new GUIrenderEngine();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	private:
		GLFW_Window *windowHandle;

		FontShader* fontshader;
		FontType* font;
		FontType* polygon;
		FontType* forcesquare;

		GUIrenderEngine(void);
		~GUIrenderEngine(void);

		static GUIrenderEngine* s_instance;

		void render(Entity& entity) const;
	};
}
#endif

