#ifndef SCRIPT_H
#define SCRIPT_H

#include "Component.h"
#include "LUACallbacks.h"
#include <string>
#include <vector>

namespace pp
{
	class lua_backend;
	class Keyboard;
	class Mouse;

	class ComponentsPool;

	// all the components class name
	class TransformationC;
	class MeshRendererC;
	class CameraC;
	class LightC;
	class DirLightC;
	class SphereColliderC;
	class AABB;
	class EllipsoidColliderC;
	class TriggerC;
	class LineRendererC;
	class DinoAIC;
	class CanvasC;

	class PlayerManager;
	class SceneManager;
	class GraphicEngine;

	class GUIName;
	class MousePicker;
	class FontsLibrary;
	class GUIText;

	class ScriptC : public Component, public LUACallbacks
	{
	public:
		ScriptC(void);
		virtual ~ScriptC(void);

		void update(const float& dt) override;
		void save(ofstream& myFile, const unsigned int & guid) override;

	public:
		// variables

		// the lua state .. important pls
		lua_State* S;

		// script file name
		std::string file_path;

		bool activeRun;

	private:
		/*ALL Lua CallBack function here*/

		/* transform component related*/
		// from here --
		int LUA_TranslateCB(lua_State* L) override;
		int LUA_RotateCB(lua_State* L) override;
		int LUA_pushRotateCB(lua_State* L) override;
		int LUA_RotateAroundCB(lua_State* L) override;
		int LUA_ScaleCB(lua_State* L) override;

		int LUA_setPositionCB(lua_State* L) override;
		int LUA_getPositionCB(lua_State* L) override;
		int LUA_setRotationCB(lua_State* L) override;
		int LUA_getRotationCB(lua_State* L) override;
		int LUA_setScaleCB(lua_State* L) override;
		int LUA_getScaleCB(lua_State* L) override;

		int LUA_setLocalPositionCB(lua_State* L) override;
		int LUA_getLocalPositionCB(lua_State* L) override;
		int LUA_setLocalRotationCB(lua_State* L) override;
		int LUA_getLocalRotationCB(lua_State* L) override;
		int LUA_setLocalScaleCB(lua_State* L) override;
		int LUA_getLocalScaleCB(lua_State* L) override;

		int LUA_LookAtCB(lua_State* L) override;
		int LUA_pushLookAtCB(lua_State* L) override;

		int LUA_setSDragRotateCB(lua_State* L) override;
		// till here --

		/* AABB component related */
		// from here--
		int LUA_setPosCB(lua_State* L) override;
		int LUA_setHalfSizeCB(lua_State* L) override;
		int LUA_getMinCB(lua_State* L) override;
		int LUA_getMaxCB(lua_State* L) override;
		int LUA_getRPosCB(lua_State* L) override;
		int LUA_setAABBCollideCB(lua_State* L) override;
		int LUA_isAABBCollideCB(lua_State* L) override;
		int LUA_checkAABBCollideCB(lua_State* L) override;
		int LUA_getAABBCollideInfoCB(lua_State* L) override;
		// till here--

		/* Sphere collider component related */
		// from here--
		int LUA_setfradiusCB(lua_State* L) override;
		int LUA_getfradiusCB(lua_State* L) override;
		int LUA_setSphereCollideCB(lua_State* L) override;
		int LUA_isSphereCollideCB(lua_State* L) override;
		// till here--

		/* ellipsoid collider component related */
		// from here--
		int LUA_setEllipsoidR3GravityCB(lua_State* L) override;
		int LUA_setEllipsoidRadiusCB(lua_State* L) override;
		int LUA_setEllipsoidR3VelCB(lua_State* L) override;
		int LUA_getEllipsoidR3GravityCB(lua_State* L) override;
		int LUA_getEllipsoidRadiusCB(lua_State* L) override;
		int LUA_getEllipsoidR3VelCB(lua_State* L) override;
		int LUA_isEllipsoidCollideCB(lua_State* L) override;
		int LUA_EllipsoidCollisionCheckCB(lua_State* L) override;
		// till here--

		/* keyboard & mouse component related */
		// from here--
		int LUA_isKeyPressedCB(lua_State* L) override;
		int LUA_isKeyHoldCB(lua_State* L) override;
		int LUA_isKeyTouchedCB(lua_State* L) override;
		int LUA_isMouseClickCB(lua_State* L) override;
		int LUA_isMouseHoldCB(lua_State* L) override;
		int LUA_getScrollingCB(lua_State* L) override;
		int LUA_setCursorEnableCB(lua_State * L) override;
		int LUA_getCursorPositionCB(lua_State * L) override;
		int LUA_CursorVsGUIAABBCB(lua_State * L) override;
		// till here--



		/*camera component related*/
		// from here --
		// Set fucntions
		int LUA_SetCamPositionCB(lua_State* L) override;
		int LUA_SetCamTargetCB(lua_State* L) override;
		int LUA_SetCamUpCB(lua_State* L) override;
		int LUA_SetCamModeCB(lua_State* L) override;
		int LUA_SetMouseControlCB(lua_State* L) override;
		int LUA_SetLookingDirCB(lua_State* L) override;
		int LUA_SetMouseSensitivityCB(lua_State* L) override;
		int LUA_SetZoomDistanceCB(lua_State * L) override;
		int LUA_SetZoomSpeedCB(lua_State * L) override;
		int LUA_SetPitchLimitCB(lua_State * L) override;
		int LUA_SetFOVYCB(lua_State * L) override;
		int LUA_SetZNearCB(lua_State * L) override;
		int LUA_SetZFarCB(lua_State * L) override;

		// Get functions
		int LUA_GetCamPositionCB(lua_State* L) override;
		int LUA_GetCamTargetCB(lua_State* L) override;
		int LUA_GetCamUpCB(lua_State* L) override;
		int LUA_GetCamModeCB(lua_State* L) override;
		int LUA_GetMouseControlCB(lua_State* L) override;
		int LUA_GetLookingDirCB(lua_State* L) override;
		int LUA_GetMouseSensitivityCB(lua_State* L) override;
		int LUA_GetZoomDistanceCB(lua_State * L) override;
		int LUA_GetZoomSpeedCB(lua_State * L) override;
		int LUA_GetPitchLimitCB(lua_State * L) override;
		int LUA_GetFOVYCB(lua_State * L) override;
		int LUA_GetZNearCB(lua_State * L) override;
		int LUA_GetZFarCB(lua_State * L) override;
		// till here --


		/* Mesh Renderer CallBack function here*/
		// From here --
		int LUA_SetColorCB(lua_State* L) override;
		int LUA_SetEmissiveCB(lua_State* L) override;
		int LUA_SetShininessCB(lua_State* L) override;
		int LUA_SetObjectVisibilityCB(lua_State* L) override;
		int LUA_SetMeshNameCB(lua_State* L) override;
		int LUA_GetColorCB(lua_State* L) override;
		int LUA_GetEmissiveCB(lua_State* L) override;
		int LUA_GetShininessCB(lua_State* L) override;
		int LUA_GetObjectVisibilityCB(lua_State* L) override;
		int LUA_GetMeshNameCB(lua_State* L) override;
		// Till here--

		/* Light Callback functions here */
		// From here--
		int LUA_SetLightPosCB(lua_State* L) override;
		int LUA_SetLightColorCB(lua_State* L) override;
		int LUA_SetAmbientCB(lua_State* L) override;
		int LUA_SetDiffuseCB(lua_State* L) override;
		int LUA_SetSpecularCB(lua_State* L) override;
		int LUA_GetLightPosCB(lua_State* L) override;
		int LUA_GetLightColorCB(lua_State* L) override;
		int LUA_GetAmbientCB(lua_State* L) override;
		int LUA_GetDiffuseCB(lua_State* L) override;
		int LUA_GetSpecularCB(lua_State* L) override;
		// Till here--

		/* Light Callback functions here */
		// From here--
		int LUA_isTriggerCB(lua_State* L) override;
		int LUA_setTriggerCB(lua_State* L) override;
		// Till here--

		/* Directional Light Callback functions here */
		// From here--
		int LUA_SetLightDirectionCB(lua_State* L) override;
		int LUA_GetLightDirectionCB(lua_State* L) override;
		int LUA_ChangeLightDirectionCB(lua_State* L) override;
		int LUA_ShadowSizeCB(lua_State * L) override;
		// Till here--

		/* line mesh callback functions here*/
		// from here--
		int LUA_StartLineCB(lua_State * L) override;
		int LUA_EndLineCB(lua_State * L) override;
		// Till here--

		/*Graphics component related*/
		// From here -- 
		int LUA_SSAOEnableCB(lua_State * L) override;
		int LUA_FXAAEnableCB(lua_State * L) override;
		int LUA_BloomEnableCB(lua_State * L) override;
		int LUA_MBEnableCB(lua_State * L) override;
		int LUA_ShadowQualityCB(lua_State * L) override;
		
		int LUA_BlurBackgroundEnableCB(lua_State * L) override;
		int LUA_FadeCB(lua_State * L) override;
		int getLUA_FadeCB(lua_State * L) override;

		int LUA_QuitGameCB(lua_State * L) override;
		int LUA_sceneRestartCB(lua_State * L) override;

		int LUA_getSceneResolutionCB(lua_State* L) override;
		int LUA_getShadowResolutionCB(lua_State* L) override;

		/* player callback functions here*/
		// from here--
		int LUA_setPlayerPosCB(lua_State* L) override;
		int LUA_getPlayerHeadPosCB(lua_State* L) override;
		int LUA_getPlayerBody1PosCB(lua_State* L) override;
		int LUA_getPlayerBody2PosCB(lua_State* L) override;
		int LUA_getPlayerTailPosCB(lua_State* L) override;
		int LUA_getPlayerTail1PosCB(lua_State* L) override;
		int LUA_getPlayerTail2PosCB(lua_State* L) override;
		int LUA_getPlayerTail3PosCB(lua_State* L) override;
		int LUA_getPlayerPosCB(lua_State* L) override;

		int LUA_setPlayerVelCB(lua_State* L) override;
		int LUA_setHeadVelCB(lua_State* L) override;
		int LUA_setBody1VelCB(lua_State* L) override;
		int LUA_setBody2VelCB(lua_State* L) override;
		int LUA_setTailVelCB(lua_State* L) override;
		int LUA_getHeadVelCB(lua_State* L) override;
		int LUA_getBody1VelCB(lua_State* L) override;
		int LUA_getBody2VelCB(lua_State* L) override;
		int LUA_getTailVelCB(lua_State* L) override;
		int LUA_getAddedVelCB(lua_State * L) override;

		int LUA_setPlayerGravityVelCB(lua_State* L) override;
		int LUA_playerDeadStateCB(lua_State* L) override;

		int LUA_EndGameCB(lua_State* L) override;

		int LUA_setPlayerStateCB(lua_State* L) override;
		int LUA_getPlayerStateCB(lua_State* L) override;

		int LUA_playerHeadECollisionCheckCB(lua_State* L) override;
		int LUA_playerBody1ECollisionCheckCB(lua_State* L) override;
		int LUA_playerBody2ECollisionCheckCB(lua_State* L) override;
		int LUA_playerTailECollisionCheckCB(lua_State* L) override;
		int LUA_playerECollisionCheckCB(lua_State* L) override;
		int LUA_playerAllECollisionCheckCB(lua_State* L) override;
		int LUA_getHeadCommandStateCB(lua_State* L) override;
		int LUA_getHeadAssPosCB(lua_State* L) override;
		int LUA_getOldHeadAssPosCB(lua_State* L) override;
		int LUA_setOldHeadAssPosCB(lua_State* L) override;

		int LUA_setHeadCommandStateCB(lua_State* L) override;
		int LUA_getBody1AssPosCB(lua_State* L) override;
		int LUA_getBody2AssPosCB(lua_State* L) override;
		int LUA_getTailAssPosCB(lua_State* L) override;
		int LUA_getTail1AssPosCB(lua_State* L) override;
		int LUA_getTail2AssPosCB(lua_State* L) override;
		int LUA_getTail3AssPosCB(lua_State* L) override;

		int LUA_getHeadDistCB(lua_State* L) override;
		int LUA_getBody1DistCB(lua_State* L) override;
		int LUA_getBody2DistCB(lua_State* L) override;
		int LUA_getTailDistCB(lua_State* L) override;
		int LUA_getTail1DistCB(lua_State* L) override;
		int LUA_getTail2DistCB(lua_State* L) override;
		int LUA_getTail3DistCB(lua_State* L) override;

		int LUA_getHeadDirCB(lua_State* L) override;
		int LUA_setHeadDirCB(lua_State* L) override;

		int LUA_getHeadMovingCB(lua_State* L) override;

		int LUA_getInactiveBlockCB(lua_State* L) override;
		// till here--

		/*Scene registration here*/
		// from here--
		int LUA_LoadSceneCB(lua_State * L) override;

		int LUA_CurrentLevelCB(lua_State * L) override;
		// till here --
		
		/*dino AI registration here*/
		// from here--
		int LUA_setDinoHeadLookingDirCB(lua_State* L) override;
		int LUA_setDinoBodyLookingDirCB(lua_State* L) override;
		int LUA_setDinoTailLookingDirCB(lua_State* L) override;
		int LUA_getDinoHeadLookingDirCB(lua_State* L) override;
		int LUA_getDinoBodyLookingDirCB(lua_State* L) override;
		int LUA_getDinoTailLookingDirCB(lua_State* L) override;
		int LUA_getDinoHeadPositionCB(lua_State* L) override;
		int LUA_getDinoBodyPositionCB(lua_State* L) override;
		int LUA_getDinoTailPositionCB(lua_State* L) override;
		int LUA_getDinoHeadFSMCB(lua_State* L) override;
		int LUA_setDinoHeadFSMCB(lua_State* L) override;
		int LUA_DinoSeePlayerCB(lua_State* L) override;
		int LUA_DinoAttackPlayerCB(lua_State* L) override;
		// till here--

		/*UI related*/
		// from here --
		int LUA_SkyboxEnableCB(lua_State * L) override;
		int LUA_PlayerEnableCB(lua_State * L) override;
		int LUA_setTextString(lua_State * L) override;
		int LUA_setTextColor(lua_State * L) override;
		int LUA_setTextMaterial(lua_State * L) override;
		int LUA_setFontType(lua_State * L) override;
		int LUA_setMaxLine(lua_State * L) override;
		int LUA_setAlpha(lua_State * L) override;
		// till here --

		/* Camvas related */
		// From here --
		int LUA_setInstructionCB(lua_State * L) override;
		int LUA_getInstructionCB(lua_State * L) override;
		// Till here --

		int LUA_PointCB(lua_State * L) override;

		int LUA_CheckpointCB(lua_State * L) override;

		/*all lua registration helper here*/
		void TransformComponentRegister(void);
		void MeshRendererComponentRegister(void);
		void CameraComponentRegister(void);
		void DirLightComponentRegister(void);
		void LightComponentRegister(void);
		void SphereColliderComponentRegister(void);
		void EllipsoidColliderComponentRegister(void);
		void AABBColliderComponentRegister(void);
		void TriggerComponentRegister(void);
		void LineRendererComponenetRegister(void);
		void DinoAIComponentRegister(void);
		void GUIComponentRegister(void);
		void CanvasComponentRegister(void);
		void InputRegister(void);
		void PlayerRegister(void);
		void SceneRegister(void);
		void GraphicsSettingRegister(void);

		

	private:
		static lua_backend* luaHandle;
		static Keyboard* keyboardHandle;
		static Mouse* mouseHandle;
		static SceneManager* sceneHandle;
		static GraphicEngine* gHandle;
		static PlayerManager* playerHandle;


		ComponentsPool* componentsDaddy;

		void registration(void);
		void run(const float &dt);

		MousePicker* pickerHandle;
		CameraC* camHandle;
		TransformationC* transformHandle;
		MeshRendererC* rendererHandle;
		LightC* lightHandle;
		DirLightC* dirlightHandle;
		EllipsoidColliderC* ellipsoidHandle;
		TriggerC* triggerhandle;
		SphereColliderC* spherecolliderHandle;
		LineRendererC* linerendererhandle;
		Entity* GUIName;
		DinoAIC* dinoAIHandle;
		GUIText* guiHandle;
		CanvasC* canvasHandle;
		std::vector<AABB*> aabbHandles;
	};
}

#endif
