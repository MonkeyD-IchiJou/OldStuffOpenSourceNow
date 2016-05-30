#ifndef COMPONENT_POOL_H
#define COMPONENT_POOL_H

#include "MathsHeader.h"
#include "enumc.h"
#include "Component.h"

namespace pp
{
	class TransformationC;
	class MeshRendererC;
	class GrassRendererC;
	class DirLightC;
	class PointLightC;
	class CameraC;
	class ScriptC;
	class GUIText;
	class SphereColliderC;
	class AABB;
	class BulletC;
	class MeshColliderC;
	class EllipsoidColliderC;
	class TriggerC;
	class DinoAIC;
	class CanvasC;
	class LineRendererC;

	class PlayerManager;

	class ComponentsPool
	{
	public:

		/* ALL utils functions */

		// constructor with sceneName to indicate which scene it is in
		ComponentsPool(const string& sceneName);
		~ComponentsPool(void);

		// create number of components .. all of it is here
		void create(void);

		// data locality concept : same components update once for all
		void updateAllComponents(const float& dt);

		// update the prev transformation 
		void updatePrevMVP(const mat4f& prevView, const mat4f& prevProj);

		// update all the camera aspect
		void updateALLCamAspect(const double& aspect);

		// render all the mesh in the MeshRendererC
		void renderMesh(void) const;

		// render meshes for depth 
		void renderMeshDepth(void) const;

		// render all the sphere collider for debug purpose
		void renderSphereCollider(void) const;

		// render all the AABB collider for debug purpose
		void renderAABB(void) const;

		// render all the mesh collider
		void renderMeshCollider(void) const;

		// render all the ellipsoid collider
		void renderEllipsoidCollider(void) const;

		// pointlight transform matrix / pointlight info sent to shader
		void ReadPointLightsInfo(const bool & pon) const;

		// draw all the text 
		void drawALLText(void) const;

		// preload gui tex
		void loadGUITex(void);

		// delete all the components
		void destroyAllComponents(void);

		// setter for scene name
		inline void setSceneName(const string& scenename) { this->scenename = scenename; }

		// getter for scene name
		inline string getSceneName(void) { return this->scenename; }

		static CameraC* cameraComponent;

		void AABBvsAABBs(AABB& own, const std::string& tagToCollide);

		void cursorPosVSAABBs(void);

	public:

		/* ALL fetching functions */

		// return a transform component handle if it doesnt have an owner
		TransformationC* FetchTransformC(void);

		// return a meshrenderer component handle if it doesnt have an owner
		MeshRendererC* FetchMeshRendererC(void);

		// return a dirlight component handle if it doesnt have an owner
		DirLightC* FetchDirlightC(void);

		// get the legit dir light
		DirLightC* getDirLight(void) const;

		// return a pointlight component handle if it doesnt have an owner
		PointLightC* FetchPointlightC(void);

		// return a script component handle if it doent have an owner
		ScriptC* FetchScriptC(void);

		// return a guitext component handle if it doent have an owner
		GUIText* FetchGUITextC(void);

		// return a SphereColliderC component handle if it doent have an owner
		SphereColliderC* FetchSphereColliderC(void);

		// return a AABB component handle if it doent have an owner
		AABB* FetchAABBC(void);

		// return a bullet component handle if it doent have an owner
		BulletC* FetchBulletC(void);

		// return a MeshColliderC component handle if it doent have an owner
		MeshColliderC* FetchMeshColliderC(void);

		// return a EllipsoidColliderC component handle if it doent have an owner
		EllipsoidColliderC* FetchEllipsoidColliderC(void);

		// return a triggerC component handle if it doent have an owner
		TriggerC* FetchTriggerC(void);

		// return a dinoAIC component handle if it doesnt have an owner
		DinoAIC* FetchDinoAIC(void);

		// return a CanvasC componenthandle if it doesn't have an owner
		CanvasC* FetchCanvas(void);

		// return a Linerenderer componenthandle if it doesn't have an owner
		LineRendererC* FetchLineRendererC(void);

		void EllipsoidCollideAndSlide(EllipsoidColliderC* colPackage, const float& dt);
		void EllipsoidVsPlayerMesh(EllipsoidColliderC* packet, const float& dt);

	private:
		vec3f collideWithWorld(const vec3f & pos, const vec3f & vel, EllipsoidColliderC* packet, const bool& gravity, const float&dt);
		bool checkPointInTriangle(const vec3f& point, const vec3f& pa, const vec3f& pb, const vec3f& pc);
		bool getLowestRoot(const float& a, const float& b, const float& c, const float& maxR, float* root);

		bool checkTriangle(EllipsoidColliderC* colPackage, const vec3f& p1, const vec3f& p2, const vec3f& p3);
		void EllipsoidVsTriMesh(EllipsoidColliderC* packet, const float& dt);

	private:
		enum COMPONENTS_ALL_TYPE
		{
			TRANSFORM = 0,
			MESHRENDERER,
			DIRLIGHT,
			POINTLIGHT,
			CAMERAC,
			SCRIPT,
			GUITEXT,
			SPHERECOLLIDER,
			AABBCOLLIDER,
			BULLET,
			ELLIPSOIDCOLLIDER,
			MESHCOLLIDER,
			TRIGGER,
			DINOAI,
			CANVAS,
			LINERENDERER,
			END_ALL
		};

		// this components pool is belong to which scene
		string scenename;

		TransformationC* transformComponents;
		MeshRendererC* MeshRendererComponents;
		DirLightC* dirlightComponents;
		PointLightC* pointlightComponents;
		ScriptC* scriptComponents;
		GUIText* guitextComponents;
		SphereColliderC* spherecolliderComponents;
		AABB* aabbComponents;
		BulletC* bulletComponents;
		MeshColliderC* meshcolliderComponents;
		EllipsoidColliderC* ellipsoidcolliderComponents;
		TriggerC* triggerComponents;
		DinoAIC* dinoAIComponents;
		CanvasC* CanvasComponents;
		LineRendererC* lineRendererComponents;

		int CSize[END_ALL];

		static PlayerManager* playerHandle;

	};
}

#endif

