#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <fstream>
#include <map>
#include "enumc.h"

#include "MathsHeader.h"

#include "LUACallbacks.h"

using std::map;
using std::ifstream;
using std::ofstream;
using std::string;

namespace pp
{
	class ComponentsPool;
	class EntitiesPool;
	class Entity;
	class CameraC;
	class DirLightC;
	class lua_backend;
	class Collectable;

	class World : public LUACallbacks
	{
	public:
		World(const string &file_path, const string &scenetag);
		~World(void);

		// create with lua file
		bool create(void);

		// update the necessary stuff for all components and entities
		void update(const float& dt);

		// all the camera aspect update
		void updateALLCamAspect(const double & aspect);

		// all the mesh render into gpass
		void renderMeshGPASS(void) const;

		// all the mesh render to depth pass
		void renderMeshDepthPASS(void) const;

		// light volume debug
		void renderLightVolume(const bool & pon) const;

		// text render on screen
		void renderAllText(void) const;
		
		// debug mesh render for debug
		void renderDebugMesh(void) const;

		// mesh collision box render
		void renderMeshColliders(void) const;

		// mesh collision box render
		void renderEllipsoidColliders(void) const;

		// render all the collectables
		void renderAllCollectable(void) const;

		// late update
		void lateupdate(const float& dt);

		// load and init the lua
		void LUALoad(void);

		// get the dir
		DirLightC* getDirLight(void) const;

		// destroy everything 
		void destroy(void);

		// save file baby
		void save(void);

		CameraC* renderCam; // the cam that used to render all objects
		Entity* mainPlayer; // main player entity in the world
		DirLightC* dirlight; // main dir light in the world

		ComponentsPool* getAllComponents(void);
		EntitiesPool* getAllEntities(void);

	private:
		/* ALL lua register helpers*/
		void EntityRegister(void);
		void AllComponentsRegister(void);
		void TransformComponentRegister(void);
		void MeshRendererComponentRegister(void);
		void CameraComponentRegister(void);
		void ScriptComponentRegister(void);
		void DirLightComponentRegister(void);
		void PointLightComponentRegister(void);
		void SphereColliderComponentRegister(void);
		void AABBColliderComponentRegister(void);
		void MeshColliderComponentRegister(void);
		void EllipsoidColliderComponentRegister(void);
		void GUIComponentRegister(void);

		/* ALL lua callback functions */

		/* entity init and fetching functions related */
		// from here --
		int LUA_CreateNewEntityCB(lua_State* L) override;
		int LUA_EntityAddParentCB(lua_State* L) override;
		int LUA_EntitySetActiveCB(lua_State* L) override;
		int LUA_EntityAddTagCB(lua_State* L) override;
		// till here --
		int LUA_EntityAddCollectableCB(lua_State* L) override;
		/* transform component related */
		// from here--
		int LUA_setPositionCB(lua_State* L) override;
		int LUA_setRotationCB(lua_State* L) override;
		int LUA_setScaleCB(lua_State* L) override;
		// till here--

		/* cam component related */
		// from here--
		int LUA_SetCamPositionCB(lua_State* L) override;
		int LUA_SetCamTargetCB(lua_State* L) override;
		int LUA_SetCamUpCB(lua_State* L) override;
		int LUA_SetCamModeCB(lua_State* L) override;
		int LUA_SetMouseControlCB(lua_State* L) override;
		int LUA_SetLookingDirCB(lua_State* L) override;
		int LUA_SetMouseSensitivityCB(lua_State * L) override;
		int LUA_SetZoomDistanceCB(lua_State * L) override;
		int LUA_SetPitchLimitCB(lua_State * L) override;
		// till here--

		/* mesh renderer component related */
		// from here--
		int LUA_AddMeshRendererComponent(lua_State* L) override;
		int LUA_SetColorCB(lua_State* L) override;
		int LUA_SetEmissiveCB(lua_State* L) override;
		int LUA_SetShininessCB(lua_State* L) override;
		int LUA_SetObjectVisibilityCB(lua_State* L) override;
		int LUA_SetMeshNameCB(lua_State* L) override;
		// till here--

		/* dir light component related */
		// from here--
		int LUA_AddDirLightComponent(lua_State* L) override;
		int LUA_SetLightColorCB(lua_State* L) override;
		int LUA_SetAmbientCB(lua_State* L) override;
		int LUA_SetDiffuseCB(lua_State* L) override;
		int LUA_SetSpecularCB(lua_State* L) override;
		int LUA_SetLightDirectionCB(lua_State* L) override;
		// till here--

		/* script component related */
		// from here--
		int LUA_AddScriptComponent(lua_State* L) override;
		int LUA_setScriptPath(lua_State* L) override;
		// till here--

		/* point light component related */
		// from here--
		int LUA_AddPointLightComponent(lua_State* L) override;
		int LUA_PointLightSetLightColorCB(lua_State* L) override;
		int LUA_PointLightSetDiffuseCB(lua_State* L) override;
		int LUA_PointLightSetSpecularCB(lua_State* L) override;
		// till here--

		/* sphere collider component related */
		// from here--
		int LUA_AddSphereColliderComponent(lua_State* L) override;
		int LUA_setfradiusCB(lua_State* L) override;
		int LUA_SphereCollideAddTagCB(lua_State* L) override;
		// till here--

		/* ellipsoid collider component related */
		// from here--
		int LUA_AddEllipsoidColliderComponent(lua_State* L) override;
		int LUA_setEllipsoidRadiusCB(lua_State* L) override;
		// till here--

		/* aabb collider component related */
		// from here--
		int LUA_AddAABBColliderComponent(lua_State* L) override;
		int LUA_setPosCB(lua_State* L) override;
		int LUA_setHalfSizeCB(lua_State* L) override;
		int LUA_AABBCollideAddTagCB(lua_State* L) override;
		// till here--

		/* mesh collider component related */
		// from here--
		int LUA_AddMeshColliderComponent(lua_State* L) override;
		int LUA_setMeshColliderNameCB(lua_State* L) override;
		// till here--

		/*trigger component related */
		// from here--
		int LUA_AddTriggerComponent(lua_State* L) override;
		int LUA_TriggerLock(lua_State* L) override;
		// till here--

		/* dino ai component related */
		// from here--
		int LUA_addDinoAIComponent(lua_State* L) override;
		int LUA_shareDinoAIComponent(lua_State* L) override;
		// till here--

		/*UI related*/
		// from here --
		int LUA_addGUIText(lua_State * L) override;
		int LUA_setTextString(lua_State * L) override;
		int LUA_setTextColor(lua_State * L) override;
		int LUA_setTextMaterial(lua_State * L) override;
		int LUA_setFontType(lua_State * L) override;
		int LUA_setMaxLine(lua_State * L) override;
		// till here --

		/* Canvas related */
		// From here --
		int LUA_addCanvas(lua_State * L) override;
		// Till here

	private:
		// register lua
		void LUA_Registration(void);

		// all the components in this world
		ComponentsPool* allComponents;

		// all the entities in this world
		EntitiesPool* allEntities;

		// all the collectables in this world
		Collectable* allCollectables;

		// the file path to read entities
		string file_path;

		// scene tag
		string scenetag;

		// the lua state .. important pls
		lua_State* S;
		static lua_backend* luaHandle;
	};

}

#endif
