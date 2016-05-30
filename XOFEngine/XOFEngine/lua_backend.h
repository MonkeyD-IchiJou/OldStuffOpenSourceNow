#ifndef LUA_BACKEND_H
#define LUA_BACKEND_H

struct lua_State;

namespace pp
{
	class LUACallbacks;
	
	class lua_backend
	{
	public:

		void setCallBack(LUACallbacks* pCallbacks);

		/* window related */
		// from here --
		void pushLUA_setWindowSizeCB(lua_State* L);
		void pushLUA_setWindowFullScreenCB(lua_State* L);

		void pushLUA_setCursorEnableCB(lua_State* L);
		void pushLUA_getCursorPositionCB(lua_State * L);
		void pushLUA_CursorVsGUIAABBCB(lua_State * L);
		// till here --

		/* scene related */
		// from here --
		void pushLUA_createSceneCB(lua_State* L);
		void pushLUA_setActiveSceneCB(lua_State* L);
		void pushLUA_SaveSceneCB(lua_State* L);
		void pushLUA_LoadSceneCB(lua_State* L);
		// till here --

		/* graphics related */
		// from here --
		void pushLUA_DebugMeshSphereEnableCB(lua_State* L);
		void pushLUA_DebugMeshAABBEnableCB(lua_State* L);

		void pushLUA_SSAOEnableCB(lua_State* L);
		void pushLUA_SSAOKernelSizeCB(lua_State* L);
		void pushLUA_SSAORadiusCB(lua_State* L);
		void pushLUA_SSAOStrengthCB(lua_State* L);

		void pushLUA_MBEnableCB(lua_State* L);
		void pushLUA_MBMaxSampleCB(lua_State* L);
		void pushLUA_MBScaleCB(lua_State* L);
		void pushLUA_getSceneResolutionCB(lua_State* L);
		void pushLUA_getShadowResolutionCB(lua_State* L);

		void pushLUA_BloomEnableCB(lua_State* L);
		void pushLUA_BloomRadiusCB(lua_State* L);
		void pushLUA_BloomSizeCB(lua_State* L);

		void pushLUA_FXAAEnableCB(lua_State* L);
		void pushLUA_FXAASizeCB(lua_State* L);

		void pushLUA_LFEnableCB(lua_State* L);
		void pushLUA_LFScaleCB(lua_State* L);
		void pushLUA_LFBiasCB(lua_State* L);
		void pushLUA_LFDistortionCB(lua_State* L);
		void pushLUA_LFGhostCB(lua_State* L);
		void pushLUA_LFGhostDispersalCB(lua_State* L);
		void pushLUA_LFHaloWidthCB(lua_State* L);

		void pushLUA_ShadowQualityCB(lua_State * L);
		void pushLUA_BlurBackgroundEnableCB(lua_State * L);
		void pushLUA_FadeCB(lua_State * L);
		void pushgetLUA_FadeCB(lua_State * L);
		// till here --

		/*transformation related*/
		// from here --
		void pushLUA_TranslateCB(lua_State* L);
		void pushLUA_RotateCB(lua_State* L);
		void pushLUA_pushRotateCB(lua_State* L);
		void pushLUA_RotateAroundCB(lua_State* L);
		void pushLUA_ScaleCB(lua_State* L);

		void pushLUA_setPositionCB(lua_State* L);
		void pushLUA_getPositionCB(lua_State* L);
		void pushLUA_setRotationCB(lua_State* L);
		void pushLUA_getRotationCB(lua_State* L);
		void pushLUA_setScaleCB(lua_State* L);
		void pushLUA_getScaleCB(lua_State* L);

		void pushLUA_setLocalPositionCB(lua_State* L);
		void pushLUA_getLocalPositionCB(lua_State* L);
		void pushLUA_setLocalRotationCB(lua_State* L);
		void pushLUA_getLocalRotationCB(lua_State* L);
		void pushLUA_setLocalScaleCB(lua_State* L);
		void pushLUA_getLocalScaleCB(lua_State* L);

		void pushLUA_LookAtCB(lua_State* L);
		void pushLUA_pushLookAtCB(lua_State* L);

		void pushLUA_setSDragRotateCB(lua_State* L);
		
		// till here --


		/*camera related*/
		// from here --
		// Set fucntions
		void pushLUA_AddCamComponent(lua_State* L);
		void pushLUA_SetCamPositionCB(lua_State* L);
		void pushLUA_SetCamTargetCB(lua_State* L);
		void pushLUA_SetCamUpCB(lua_State* L);
		void pushLUA_SetCamModeCB(lua_State* L);
		void pushLUA_SetMouseControlCB(lua_State* L);
		void pushLUA_SetLookingDirCB(lua_State* L);
		void pushLUA_SetMouseSensitivityCB(lua_State * L);
		void pushLUA_SetZoomDistanceCB(lua_State * L);
		void pushLUA_SetZoomSpeedCB(lua_State * L);
		void pushLUA_SetPitchLimitCB(lua_State * L);
		void pushLUA_SetFOVYCB(lua_State * L);
		void pushLUA_SetZNearCB(lua_State * L);
		void pushLUA_SetZFarCB(lua_State * L);

		// Get functions
		void pushLUA_GetCamPositionCB(lua_State* L);
		void pushLUA_GetCamTargetCB(lua_State* L);
		void pushLUA_GetCamUpCB(lua_State* L);
		void pushLUA_GetCamModeCB(lua_State* L);
		void pushLUA_GetMouseControlCB(lua_State* L);
		void pushLUA_GetLookingDirCB(lua_State* L);
		void pushLUA_GetMouseSensitivityCB(lua_State * L);
		void pushLUA_GetZoomDistanceCB(lua_State * L);
		void pushLUA_GetZoomSpeedCB(lua_State * L);
		void pushLUA_GetPitchLimitCB(lua_State * L);
		void pushLUA_GetFOVYCB(lua_State * L);
		void pushLUA_GetZNearCB(lua_State * L);
		void pushLUA_GetZFarCB(lua_State * L);
		// till here --

		/*---Render Component Relations---*/
		void pushLUA_AddMeshRendererComponent(lua_State* L);
		void pushLUA_SetColorCB(lua_State* L);
		void pushLUA_SetEmissiveCB(lua_State* L);
		void pushLUA_SetShininessCB(lua_State* L);
		void pushLUA_SetObjectVisibilityCB(lua_State* L);
		void pushLUA_SetMeshNameCB(lua_State* L);
		void pushLUA_GetColorCB(lua_State* L);
		void pushLUA_GetEmissiveCB(lua_State* L);
		void pushLUA_GetShininessCB(lua_State* L);
		void pushLUA_GetObjectVisibilityCB(lua_State* L);
		void pushLUA_GetMeshNameCB(lua_State* L);
		/*--------------------------------*/

		/*---Light Component Relations---*/
		void pushLUA_SetLightPosCB(lua_State* L);
		void pushLUA_SetLightColorCB(lua_State* L);
		void pushLUA_SetAmbientCB(lua_State* L);
		void pushLUA_SetDiffuseCB(lua_State* L);
		void pushLUA_SetSpecularCB(lua_State* L);
		void pushLUA_GetLightPosCB(lua_State* L);
		void pushLUA_GetLightColorCB(lua_State* L);
		void pushLUA_GetAmbientCB(lua_State* L);
		void pushLUA_GetDiffuseCB(lua_State* L);
		void pushLUA_GetSpecularCB(lua_State* L);
		/*-------------------------------*/

		/*---Directional Light Component Relations---*/
		void pushLUA_AddDirLightComponent(lua_State* L);
		void pushLUA_SetLightDirectionCB(lua_State* L);
		void pushLUA_GetLightDirectionCB(lua_State* L);
		void pushLUA_ChangeLightDirectionCB(lua_State* L);
		void pushLUA_ShadowSizeCB(lua_State* L);
		/*-------------------------------------------*/

		/* script component related */
		// from here--
		void pushLUA_AddScriptComponent(lua_State* L);
		void pushLUA_setScriptPath(lua_State* L);
		// till here--

		/* point light component related */
		// from here--
		void pushLUA_AddPointLightComponent(lua_State* L);
		void pushLUA_PointLightSetLightColorCB(lua_State* L);
		void pushLUA_PointLightSetDiffuseCB(lua_State* L);
		void pushLUA_PointLightSetSpecularCB(lua_State* L);
		// till here--

		/* AABB component related */
		// from here--
		void pushLUA_AddAABBColliderComponent(lua_State* L);
		void pushLUA_setPosCB(lua_State* L) ;
		void pushLUA_setHalfSizeCB(lua_State* L);
		void pushLUA_getMinCB(lua_State* L);
		void pushLUA_getMaxCB(lua_State* L);
		void pushLUA_getRPosCB(lua_State* L);
		void pushLUA_setAABBCollideCB(lua_State* L);
		void pushLUA_isAABBCollideCB(lua_State* L);
		void pushLUA_AABBCollideAddTagCB(lua_State* L);
		void pushLUA_checkAABBCollideCB(lua_State* L);
		void pushLUA_getAABBCollideInfoCB(lua_State* L);
		
		// till here--

		/* dino ai component related */
		// from here--
		void pushLUA_addDinoAIComponent(lua_State* L);
		void pushLUA_shareDinoAIComponent(lua_State* L);
		void pushLUA_setDinoHeadLookingDirCB(lua_State* L);
		void pushLUA_setDinoBodyLookingDirCB(lua_State* L);
		void pushLUA_setDinoTailLookingDirCB(lua_State* L);
		void pushLUA_getDinoHeadLookingDirCB(lua_State* L);
		void pushLUA_getDinoTailLookingDirCB(lua_State* L);
		void pushLUA_getDinoBodyLookingDirCB(lua_State* L);
		void pushLUA_getDinoHeadPositionCB(lua_State* L);
		void pushLUA_getDinoBodyPositionCB(lua_State* L);
		void pushLUA_getDinoTailPositionCB(lua_State* L);
		void pushLUA_getDinoHeadFSMCB(lua_State* L);
		void pushLUA_setDinoHeadFSMCB(lua_State* L);
		void pushLUA_DinoSeePlayerCB(lua_State* L);
		void pushLUA_DinoAttackPlayerCB(lua_State* L);

		// end here--

		/* trigger component related */
		// from here--
		void pushLUA_AddTriggerComponent(lua_State* L);
		void pushLUA_TriggerLock(lua_State* L);
		void pushLUA_isTriggerCB(lua_State* L);
		void pushLUA_setTriggerCB(lua_State* L);
		// till here--

		/* line mesh component related */
		// from here--
		void pushLUA_StartLineCB(lua_State* L);
		void pushLUA_EndLineCB(lua_State* L);
		// till here--

		/* ellipsoid component related */
		// from here--
		void pushLUA_AddEllipsoidColliderComponent(lua_State* L);
		void pushLUA_setEllipsoidR3GravityCB(lua_State* L);
		void pushLUA_setEllipsoidRadiusCB(lua_State* L);
		void pushLUA_setEllipsoidR3VelCB(lua_State* L);
		void pushLUA_getEllipsoidR3GravityCB(lua_State* L);
		void pushLUA_getEllipsoidRadiusCB(lua_State* L);
		void pushLUA_getEllipsoidR3VelCB(lua_State* L);
		void pushLUA_isEllipsoidCollideCB(lua_State* L);
		void pushLUA_EllipsoidCollisionCheckCB(lua_State* L);
		// till here--

		/* AABB component related */
		// from here--
		void pushLUA_AddMeshColliderComponent(lua_State* L);
		void pushLUA_setMeshColliderNameCB(lua_State* L);
		// till here--

		/* Sphere collider component related */
		// from here--
		void pushLUA_AddSphereColliderComponent(lua_State* L);
		void pushLUA_setfradiusCB(lua_State* L);
		void pushLUA_getfradiusCB(lua_State* L);
		void pushLUA_setSphereCollideCB(lua_State* L);
		void pushLUA_isSphereCollideCB(lua_State* L);
		void pushLUA_SphereCollideAddTagCB(lua_State* L);
		// till here--

		/* keyboard & mouse component related */
		// from here--
		void pushLUA_isKeyPressedCB(lua_State* L) ;
		void pushLUA_isKeyHoldCB(lua_State* L) ;
		void pushLUA_isKeyTouchedCB(lua_State* L) ;
		void pushLUA_isMouseClickCB(lua_State* L) ;
		void pushLUA_isMouseHoldCB(lua_State* L) ;
		void pushLUA_getScrollingCB(lua_State* L) ;
		// till here--

		/* entity init and fetching functions related */
		// from here --
		void pushLUA_CreateNewEntityCB(lua_State* L);
		void pushLUA_EntityAddParentCB(lua_State* L);
		void pushLUA_EntityAddCollectableCB(lua_State* L);
		void pushLUA_EntitySetActiveCB(lua_State* L);
		void pushLUA_EntityAddTagCB(lua_State* L);
		// till here --

		/* player callback functions here*/
		// from here--
		void pushLUA_getPlayerHeadPosCB(lua_State* L);
		void pushLUA_getPlayerBody1PosCB(lua_State* L);
		void pushLUA_getPlayerBody2PosCB(lua_State* L);
		void pushLUA_getPlayerTailPosCB(lua_State* L);
		void pushLUA_getPlayerTail1PosCB(lua_State* L);
		void pushLUA_getPlayerTail2PosCB(lua_State* L);
		void pushLUA_getPlayerTail3PosCB(lua_State* L);
		void pushLUA_getPlayerPosCB(lua_State* L);

		void pushLUA_setPlayerPosCB(lua_State* L);
		void pushLUA_playerDeadStateCB(lua_State* L);

		void pushLUA_EndGameCB(lua_State* L);

		void pushLUA_setPlayerVelCB(lua_State* L);
		void pushLUA_setHeadVelCB(lua_State* L);
		void pushLUA_setBody1VelCB(lua_State* L);
		void pushLUA_setBody2VelCB(lua_State* L);
		void pushLUA_setTailVelCB(lua_State* L);
		void pushLUA_getHeadVelCB(lua_State* L);
		void pushLUA_getBody1VelCB(lua_State* L);
		void pushLUA_getBody2VelCB(lua_State* L);
		void pushLUA_getTailVelCB(lua_State* L);

		void pushLUA_getAddedVelCB(lua_State * L);

		void pushLUA_setPlayerGravityVelCB(lua_State* L);

		void pushLUA_setPlayerStateCB(lua_State* L);
		void pushLUA_getPlayerStateCB(lua_State* L);

		void pushLUA_playerHeadECollisionCheckCB(lua_State* L) ;
		void pushLUA_playerBody1ECollisionCheckCB(lua_State* L) ;
		void pushLUA_playerBody2ECollisionCheckCB(lua_State* L) ;
		void pushLUA_playerTailECollisionCheckCB(lua_State* L) ;
		void pushLUA_playerECollisionCheckCB(lua_State* L);
		void pushLUA_playerAllECollisionCheckCB(lua_State* L);
		void pushLUA_getHeadCommandStateCB(lua_State* L);
		void pushLUA_getHeadAssPosCB(lua_State* L);
		void pushLUA_getOldHeadAssPosCB(lua_State* L);
		void pushLUA_setOldHeadAssPosCB(lua_State* L);
		void pushLUA_setHeadCommandStateCB(lua_State* L);
		void pushLUA_getBody1AssPosCB(lua_State* L);
		void pushLUA_getBody2AssPosCB(lua_State* L);
		void pushLUA_getTailAssPosCB(lua_State* L);
		void pushLUA_getTail1AssPosCB(lua_State* L);
		void pushLUA_getTail2AssPosCB(lua_State* L);
		void pushLUA_getTail3AssPosCB(lua_State* L);

		void pushLUA_getHeadDistCB(lua_State* L);
		void pushLUA_getBody1DistCB(lua_State* L);
		void pushLUA_getBody2DistCB(lua_State* L);
		void pushLUA_getTailDistCB(lua_State* L);
		void pushLUA_getTail1DistCB(lua_State* L);
		void pushLUA_getTail2DistCB(lua_State* L);
		void pushLUA_getTail3DistCB(lua_State* L);

		void pushLUA_getHeadDirCB(lua_State* L);
		void pushLUA_setHeadDirCB(lua_State* L);

		void pushLUA_getHeadMovingCB(lua_State* L);

		void pushLUA_getInactiveBlockCB(lua_State* L);
		// till here--

		/*UI related*/
		// from here --
		void pushLUA_SkyboxEnableCB(lua_State * L);
		void pushLUA_PlayerEnableCB(lua_State * L);
		void pushLUA_QuitGameCB(lua_State * L);

		void pushLUA_sceneRestartCB(lua_State* L);
		void pushLUA_CurrentLevelCB(lua_State* L);
		void pushLUA_PointCB(lua_State* L);
		void pushLUA_CheckpointCB(lua_State* L);

		void pushLUA_addGUIText(lua_State * L);
		void pushLUA_setTextColor(lua_State * L);
		void pushLUA_setTextString(lua_State * L);
		void pushLUA_setTextMaterial(lua_State * L);
		void pushLUA_setFontType(lua_State * L);
		void pushLUA_setMaxLine(lua_State * L);
		void pushLUA_setAlpha(lua_State * L);
		// till here --

		/* Canvas related */
		// from here --
		void pushLUA_addCanvas(lua_State * L);
		void pushLUA_setInstructionCB(lua_State * L);
		void pushLUA_getInstructionCB(lua_State * L);
		// Till here --

		// Singleton class implementation
		static inline lua_backend* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new lua_backend();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	private:
		lua_backend(void);
		~lua_backend(void);

		static lua_backend* s_instance;
	};
}
#endif

