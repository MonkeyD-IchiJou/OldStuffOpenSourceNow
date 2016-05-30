#ifndef LUA_CALLBACKS_H
#define LUA_CALLBACKS_H

struct lua_State;

namespace pp
{
	class LUACallbacks
	{
	public:
		
		/* window related */
		// from here --
		virtual int LUA_setWindowSizeCB(lua_State* L) { return 0; };
		virtual int LUA_setWindowFullScreenCB(lua_State* L) { return 0; };

		virtual int LUA_setCursorEnableCB(lua_State* L) { return 0; };
		virtual int LUA_getCursorPositionCB(lua_State * L) { return 0; };
		virtual int LUA_CursorVsGUIAABBCB(lua_State * L) { return 0; };
		// till here --

		/* scene related */
		// from here --
		virtual int LUA_createSceneCB(lua_State* L) { return 0; };
		virtual int LUA_setActiveSceneCB(lua_State* L) { return 0; };
		virtual int LUA_SaveSceneCB(lua_State* L) { return 0; };
		virtual int LUA_LoadSceneCB(lua_State* L) { return 0; };
		// till here --

		/* graphics related */
		// from here --
		virtual int LUA_DebugMeshSphereEnableCB(lua_State* L) { return 0; };
		virtual int LUA_DebugMeshAABBEnableCB(lua_State* L) { return 0; };

		virtual int LUA_SSAOEnableCB(lua_State* L) { return 0; };
		virtual int LUA_SSAOKernelSizeCB(lua_State* L) { return 0; };
		virtual int LUA_SSAORadiusCB(lua_State* L) { return 0; };
		virtual int LUA_SSAOStrengthCB(lua_State* L) { return 0; };

		virtual int LUA_MBEnableCB(lua_State* L) { return 0; };
		virtual int LUA_MBMaxSampleCB(lua_State* L) { return 0; };
		virtual int LUA_MBScaleCB(lua_State* L) { return 0; };

		virtual int LUA_getSceneResolutionCB(lua_State* L) { return 0; };
		virtual int LUA_getShadowResolutionCB(lua_State* L) { return 0; };

		virtual int LUA_BloomEnableCB(lua_State* L) { return 0; };
		virtual int LUA_BloomRadiusCB(lua_State* L) { return 0; };
		virtual int LUA_BloomSizeCB(lua_State* L) { return 0; };

		virtual int LUA_FXAAEnableCB(lua_State* L) { return 0; };
		virtual int LUA_FXAASizeCB(lua_State* L) { return 0; };

		virtual int LUA_LFEnableCB(lua_State* L) { return 0; };
		virtual int LUA_LFScaleCB(lua_State* L) { return 0; };
		virtual int LUA_LFBiasCB(lua_State* L) { return 0; };
		virtual int LUA_LFDistortionCB(lua_State* L) { return 0; };
		virtual int LUA_LFGhostCB(lua_State* L) { return 0; };
		virtual int LUA_LFGhostDispersalCB(lua_State* L) { return 0; };
		virtual int LUA_LFHaloWidthCB(lua_State* L) { return 0; };

		virtual int LUA_ShadowQualityCB(lua_State * L) { return 0; };
		virtual int LUA_ShadowSizeCB(lua_State * L) { return 0; };
		virtual int LUA_BlurBackgroundEnableCB(lua_State * L) { return 0; };
		virtual int LUA_FadeCB(lua_State * L) { return 0; };
		virtual int getLUA_FadeCB(lua_State * L) { return 0; };
		// till here --

		/* transform component related */
		// from here --
		virtual int LUA_TranslateCB(lua_State* L) { return 0; };
		virtual int LUA_RotateCB(lua_State* L) { return 0; };
		virtual int LUA_pushRotateCB(lua_State* L) { return 0; };
		virtual int LUA_RotateAroundCB(lua_State* L) { return 0; };
		virtual int LUA_ScaleCB(lua_State* L) { return 0; };

		virtual int LUA_setPositionCB(lua_State* L) { return 0; };
		virtual int LUA_getPositionCB(lua_State* L) { return 0; };
		virtual int LUA_setRotationCB(lua_State* L) { return 0; };
		virtual int LUA_getRotationCB(lua_State* L) { return 0; };
		virtual int LUA_setScaleCB(lua_State* L) { return 0; };
		virtual int LUA_getScaleCB(lua_State* L) { return 0; };

		virtual int LUA_setLocalPositionCB(lua_State* L) { return 0; };
		virtual int LUA_getLocalPositionCB(lua_State* L) { return 0; };
		virtual int LUA_setLocalRotationCB(lua_State* L) { return 0; };
		virtual int LUA_getLocalRotationCB(lua_State* L) { return 0; };
		virtual int LUA_setLocalScaleCB(lua_State* L) { return 0; };
		virtual int LUA_getLocalScaleCB(lua_State* L) { return 0; };

		virtual int LUA_LookAtCB(lua_State* L) { return 0; };
		virtual int LUA_pushLookAtCB(lua_State* L) { return 0; };

		virtual int LUA_setSDragRotateCB(lua_State* L) { return 0; };
		

		// till here


		/*camera component related*/
		// from here --

		virtual int LUA_AddCamComponent(lua_State* L) { return 0; };

		// Set fucntions
		virtual int LUA_SetCamPositionCB(lua_State* L) { return 0; };
		virtual int LUA_SetCamTargetCB(lua_State* L) { return 0; };
		virtual int LUA_SetCamUpCB(lua_State* L) { return 0; };
		virtual int LUA_SetCamModeCB(lua_State* L) { return 0; };
		virtual int LUA_SetMouseControlCB(lua_State* L) { return 0; };
		virtual int LUA_SetLookingDirCB(lua_State* L) { return 0; };
		virtual int LUA_SetMouseSensitivityCB(lua_State * L) { return 0; };
		virtual int LUA_SetZoomDistanceCB(lua_State * L) { return 0; };
		virtual int LUA_SetZoomSpeedCB(lua_State * L) { return 0; };
		virtual int LUA_SetPitchLimitCB(lua_State * L) { return 0; };
		virtual int LUA_SetFOVYCB(lua_State * L) { return 0; };
		virtual int LUA_SetZNearCB(lua_State * L) { return 0; };
		virtual int LUA_SetZFarCB(lua_State * L) { return 0; };

		// Get functions
		virtual int LUA_GetCamPositionCB(lua_State* L) { return 0; };
		virtual int LUA_GetCamTargetCB(lua_State* L) { return 0; };
		virtual int LUA_GetCamUpCB(lua_State* L) { return 0; };
		virtual int LUA_GetCamModeCB(lua_State* L) { return 0; };
		virtual int LUA_GetMouseControlCB(lua_State* L) { return 0; };
		virtual int LUA_GetLookingDirCB(lua_State* L) { return 0; };
		virtual int LUA_GetMouseSensitivityCB(lua_State * L) { return 0; };
		virtual int LUA_GetZoomDistanceCB(lua_State * L) { return 0; };
		virtual int LUA_GetZoomSpeedCB(lua_State * L) { return 0; };
		virtual int LUA_GetPitchLimitCB(lua_State * L) { return 0; };
		virtual int LUA_GetFOVYCB(lua_State * L) { return 0; };
		virtual int LUA_GetZNearCB(lua_State * L) { return 0; };
		virtual int LUA_GetZFarCB(lua_State * L) { return 0; };
		// till here --

		/*---Render Component Relations---*/
		virtual int LUA_AddMeshRendererComponent(lua_State* L) { return 0; };
		virtual int LUA_SetColorCB(lua_State* L) { return 0; };
		virtual int LUA_SetEmissiveCB(lua_State* L) { return 0; };
		virtual int LUA_SetShininessCB(lua_State* L) { return 0; };
		virtual int LUA_SetObjectVisibilityCB(lua_State* L) { return 0; };
		virtual int LUA_SetMeshNameCB(lua_State* L) { return 0; };
		virtual int LUA_GetColorCB(lua_State* L) { return 0; };
		virtual int LUA_GetEmissiveCB(lua_State* L) { return 0; };
		virtual int LUA_GetShininessCB(lua_State* L) { return 0; };
		virtual int LUA_GetObjectVisibilityCB(lua_State* L) { return 0; };
		virtual int LUA_GetMeshNameCB(lua_State* L) { return 0; };
		/*--------------------------------*/
		
		/*---Light Component Relations---*/
		virtual int LUA_SetLightPosCB(lua_State* L) { return 0; };
		virtual int LUA_SetLightColorCB(lua_State* L) { return 0; };
		virtual int LUA_SetAmbientCB(lua_State* L) { return 0; };
		virtual int LUA_SetDiffuseCB(lua_State* L) { return 0; };
		virtual int LUA_SetSpecularCB(lua_State* L) { return 0; };
		virtual int LUA_GetLightPosCB(lua_State* L) { return 0; };
		virtual int LUA_GetLightColorCB(lua_State* L) { return 0; };
		virtual int LUA_GetAmbientCB(lua_State* L) { return 0; };
		virtual int LUA_GetDiffuseCB(lua_State* L) { return 0; };
		virtual int LUA_GetSpecularCB(lua_State* L) { return 0; };
		/*-------------------------------*/

		/*---Directional Light Component Relations---*/
		virtual int LUA_AddDirLightComponent(lua_State* L) { return 0; };
		virtual int LUA_SetLightDirectionCB(lua_State* L) { return 0; };
		virtual int LUA_GetLightDirectionCB(lua_State* L) { return 0; };
		virtual int LUA_ChangeLightDirectionCB(lua_State* L) { return 0; };
		/*-------------------------------------------*/

		/* ellipsoid component related */
		// from here--
		virtual int LUA_AddEllipsoidColliderComponent(lua_State* L) { return 0; };
		virtual int LUA_setEllipsoidR3GravityCB(lua_State* L) { return 0; };
		virtual int LUA_setEllipsoidRadiusCB(lua_State* L) { return 0; };
		virtual int LUA_setEllipsoidR3VelCB(lua_State* L) { return 0; };
		virtual int LUA_getEllipsoidR3GravityCB(lua_State* L) { return 0; };
		virtual int LUA_getEllipsoidRadiusCB(lua_State* L) { return 0; };
		virtual int LUA_getEllipsoidR3VelCB(lua_State* L) { return 0; };
		virtual int LUA_isEllipsoidCollideCB(lua_State* L) { return 0; };
		virtual int LUA_EllipsoidCollisionCheckCB(lua_State* L) { return 0; };
		// till here--

		/* AABB component related */
		// from here--
		virtual int LUA_AddAABBColliderComponent(lua_State* L) { return 0; };
		virtual int LUA_setPosCB(lua_State* L) { return 0; };
		virtual int LUA_setHalfSizeCB(lua_State* L) { return 0; };
		virtual int LUA_getMinCB(lua_State* L) { return 0; };
		virtual int LUA_getMaxCB(lua_State* L) { return 0; };
		virtual int LUA_getRPosCB(lua_State* L) { return 0; };
		virtual int LUA_setAABBCollideCB(lua_State* L) { return 0; };
		virtual int LUA_isAABBCollideCB(lua_State* L) { return 0; };
		virtual int LUA_AABBCollideAddTagCB(lua_State* L) { return 0; };
		virtual int LUA_checkAABBCollideCB(lua_State* L) { return 0; };
		virtual int LUA_getAABBCollideInfoCB(lua_State* L) { return 0; };
		// till here--

		/* Sphere collider component related */
		// from here--
		virtual int LUA_AddSphereColliderComponent(lua_State* L) { return 0; };
		virtual int LUA_setfradiusCB(lua_State* L) { return 0; };
		virtual int LUA_getfradiusCB(lua_State* L) { return 0; };
		virtual int LUA_setSphereCollideCB(lua_State* L) { return 0; };
		virtual int LUA_isSphereCollideCB(lua_State* L) { return 0; };
		virtual int LUA_SphereCollideAddTagCB(lua_State* L) { return 0; };
		// till here--

		/* script component related */
		// from here--
		virtual int LUA_AddScriptComponent(lua_State* L) { return 0; };
		virtual int LUA_setScriptPath(lua_State* L) { return 0; };
		// till here--

		/* point light component related */
		// from here--
		virtual int LUA_AddPointLightComponent(lua_State* L) { return 0; };
		virtual int LUA_PointLightSetLightColorCB(lua_State* L) { return 0; };
		virtual int LUA_PointLightSetDiffuseCB(lua_State* L) { return 0; };
		virtual int LUA_PointLightSetSpecularCB(lua_State* L) { return 0; };
		// till here--

		/* mesh collider component related */
		// from here--
		virtual int LUA_AddMeshColliderComponent(lua_State* L) { return 0; };
		virtual int LUA_setMeshColliderNameCB(lua_State* L) { return 0; };
		// till here--

		/* trigger component related */
		// from here--
		virtual int LUA_AddTriggerComponent(lua_State* L) { return 0; };
		virtual int LUA_TriggerLock(lua_State* L) { return 0; };
		virtual int LUA_isTriggerCB(lua_State* L) { return 0; };
		virtual int LUA_setTriggerCB(lua_State* L) { return 0; };
		// till here--

		/* keyboard & mouse component related */
		// from here--
		virtual int LUA_isKeyPressedCB(lua_State* L) { return 0; };
		virtual int LUA_isKeyHoldCB(lua_State* L) { return 0; };
		virtual int LUA_isKeyTouchedCB(lua_State* L) { return 0; };
		virtual int LUA_isMouseClickCB(lua_State* L) { return 0; };
		virtual int LUA_isMouseHoldCB(lua_State* L) { return 0; };
		virtual int LUA_getScrollingCB(lua_State* L) { return 0; };
		// till here--

		/* entity init and fetching functions related */
		// from here --
		virtual int LUA_CreateNewEntityCB(lua_State* L) { return 0; };
		virtual int LUA_EntityAddParentCB(lua_State* L) { return 0; };
		virtual int LUA_EntitySetActiveCB(lua_State* L) { return 0; };
		virtual int LUA_EntityAddTagCB(lua_State* L) { return 0; };
		// till here --

		/* player callback functions here*/
		// from here--
		virtual int LUA_getPlayerHeadPosCB(lua_State* L) { return 0; };
		virtual int LUA_getPlayerBody1PosCB(lua_State* L) { return 0; };
		virtual int LUA_getPlayerBody2PosCB(lua_State* L) { return 0; };
		virtual int LUA_getPlayerTailPosCB(lua_State* L) { return 0; };
		virtual int LUA_getPlayerTail1PosCB(lua_State* L) { return 0; };
		virtual int LUA_getPlayerTail2PosCB(lua_State* L) { return 0; };
		virtual int LUA_getPlayerTail3PosCB(lua_State* L) { return 0; };
		virtual int LUA_getPlayerPosCB(lua_State* L) { return 0; };

		virtual int LUA_setPlayerPosCB(lua_State* L) { return 0; };
		virtual int LUA_playerDeadStateCB(lua_State* L) { return 0; };

		virtual int LUA_EndGameCB(lua_State* L) { return 0; };

		virtual int LUA_setPlayerVelCB(lua_State* L) { return 0; };
		virtual int LUA_setHeadVelCB(lua_State* L){ return 0; };
		virtual int LUA_setBody1VelCB(lua_State* L){ return 0; };
		virtual int LUA_setBody2VelCB(lua_State* L){ return 0; };
		virtual int LUA_setTailVelCB(lua_State* L){ return 0; };
		virtual int LUA_getHeadVelCB(lua_State* L){ return 0; };
		virtual int LUA_getBody1VelCB(lua_State* L){ return 0; };
		virtual int LUA_getBody2VelCB(lua_State* L){ return 0; };
		virtual int LUA_getTailVelCB(lua_State* L){ return 0; };

		virtual int LUA_getAddedVelCB(lua_State * L) { return 0; };


		virtual int LUA_setPlayerGravityVelCB(lua_State* L) { return 0; };

		virtual int LUA_setPlayerStateCB(lua_State* L) { return 0; };
		virtual int LUA_getPlayerStateCB(lua_State* L) { return 0; };

		virtual int LUA_playerHeadECollisionCheckCB(lua_State* L) { return 0; };
		virtual int LUA_playerBody1ECollisionCheckCB(lua_State* L) { return 0; };
		virtual int LUA_playerBody2ECollisionCheckCB(lua_State* L) { return 0; };
		virtual int LUA_playerTailECollisionCheckCB(lua_State* L) { return 0; };
		virtual int LUA_playerECollisionCheckCB(lua_State* L) { return 0; };
		virtual int LUA_playerAllECollisionCheckCB(lua_State* L) { return 0; };
		virtual int LUA_getHeadCommandStateCB(lua_State* L) { return 0; };
		virtual int LUA_getHeadAssPosCB(lua_State* L) { return 0; };
		virtual int LUA_getOldHeadAssPosCB(lua_State* L) { return 0; };
		virtual int LUA_setOldHeadAssPosCB(lua_State* L) { return 0; };

		virtual int LUA_setHeadCommandStateCB(lua_State* L) { return 0; };
		virtual int LUA_getBody1AssPosCB(lua_State* L) { return 0; };
		virtual int LUA_getBody2AssPosCB(lua_State* L) { return 0; };
		virtual int LUA_getTailAssPosCB(lua_State* L) { return 0; };
		virtual int LUA_getTail1AssPosCB(lua_State* L) { return 0; };
		virtual int LUA_getTail2AssPosCB(lua_State* L) { return 0; };
		virtual int LUA_getTail3AssPosCB(lua_State* L) { return 0; };


		virtual int LUA_getHeadDistCB(lua_State* L) { return 0; };
		virtual int LUA_getBody1DistCB(lua_State* L) { return 0; };
		virtual int LUA_getBody2DistCB(lua_State* L) { return 0; };
		virtual int LUA_getTailDistCB(lua_State* L) { return 0; };
		virtual int LUA_getTail1DistCB(lua_State* L) { return 0; };
		virtual int LUA_getTail2DistCB(lua_State* L) { return 0; };
		virtual int LUA_getTail3DistCB(lua_State* L) { return 0; };

		virtual int LUA_getHeadDirCB(lua_State* L) { return 0; };
		virtual int LUA_setHeadDirCB(lua_State* L) { return 0; };

		virtual int LUA_getHeadMovingCB(lua_State* L) { return 0; };

		virtual int LUA_getInactiveBlockCB(lua_State* L) { return 0; };
		virtual int LUA_EntityAddCollectableCB(lua_State* L) { return 0; };
		// till here--


		virtual int LUA_StartLineCB(lua_State * L) { return 0; };
		virtual int LUA_EndLineCB(lua_State * L) { return 0; };

		// dino ai component
		// from here--
		virtual int LUA_addDinoAIComponent(lua_State* L) { return 0; };
		virtual int LUA_shareDinoAIComponent(lua_State* L) { return 0; };
		virtual int LUA_setDinoHeadLookingDirCB(lua_State* L) { return 0; };
		virtual int LUA_setDinoBodyLookingDirCB(lua_State* L) { return 0; };
		virtual int LUA_setDinoTailLookingDirCB(lua_State* L) { return 0; };
		virtual int LUA_getDinoTailLookingDirCB(lua_State* L) { return 0; };
		virtual int LUA_getDinoHeadLookingDirCB(lua_State* L) { return 0; };
		virtual int LUA_getDinoBodyLookingDirCB(lua_State* L) { return 0; };
		virtual int LUA_getDinoHeadPositionCB(lua_State* L) { return 0; };
		virtual int LUA_getDinoBodyPositionCB(lua_State* L) { return 0; };
		virtual int LUA_getDinoTailPositionCB(lua_State* L) { return 0; };
		virtual int LUA_getDinoHeadFSMCB(lua_State* L) { return 0; };
		virtual int LUA_setDinoHeadFSMCB(lua_State* L) { return 0; };
		virtual int LUA_DinoSeePlayerCB(lua_State* L) { return 0; };
		virtual int LUA_DinoAttackPlayerCB(lua_State* L) { return 0; };
		// till here--


		/* UI related */
		// from here -- 
		virtual int LUA_addGUIText(lua_State * L) { return 0; };
		virtual int LUA_SkyboxEnableCB(lua_State * L) { return 0; };
		virtual int LUA_PlayerEnableCB(lua_State * L) { return 0; };
		virtual int LUA_QuitGameCB(lua_State * L) { return 0; };
		virtual int LUA_sceneRestartCB(lua_State * L) { return 0; };
		virtual int LUA_CurrentLevelCB(lua_State * L) { return 0; };
		virtual int LUA_PointCB(lua_State * L) { return 0; };
		virtual int LUA_CheckpointCB(lua_State * L) { return 0; };

		virtual int LUA_setTextString(lua_State * L) { return 0; };
		virtual int LUA_setTextColor(lua_State * L) { return 0; };
		virtual int LUA_setTextMaterial(lua_State * L) { return 0; };
		virtual int LUA_setFontType(lua_State * L) { return 0; };
		virtual int LUA_setMaxLine(lua_State * L) { return 0; };
		virtual int LUA_setAlpha(lua_State * L) { return 0; };
		// till here --

		/* Canvas related */
		// From here --
		virtual int LUA_addCanvas(lua_State * L) { return 0; };
		virtual int LUA_setInstructionCB(lua_State * L) { return 0; };
		virtual int LUA_getInstructionCB(lua_State * L) { return 0; };
		// Till here --
	};
}

#endif