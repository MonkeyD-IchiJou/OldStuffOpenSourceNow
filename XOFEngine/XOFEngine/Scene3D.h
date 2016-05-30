#ifndef SCENE_3D_H
#define SCENE_3D_H

#include "scenebase.h"
#include "MathsHeader.h"

namespace pp
{
	class GUIrenderEngine;

	class Scene3D : public scenebase
	{
	public:
		Scene3D(const std::string & sceneName, const std::string & worldPath);
		virtual ~Scene3D(void);

		bool Init(void) override;
		void update(const float &dt) override;
		void render(void) override;
		void lateupdate(const float &dt) override;
		void Restart(void) override;

		vec3f checkPoint;
		float totalPlayingTime;
		int totalDieingNumber;

		

	private:
		/* GLFW call back functions */

		void WindowResizeCB(const int& width, const int& height) override;
		void WindowIconifiyCB(const int& i) override;

	private:
		/* All Variable */

		GUIrenderEngine* guiHandle;
	};
}

#endif
