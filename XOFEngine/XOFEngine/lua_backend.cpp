#include "lua_backend.h"
#include "LUACallbacks.h"
#include "lua\lua.hpp"

namespace pp
{
	static LUACallbacks* s_pCallbacks = nullptr;
	lua_backend* lua_backend::s_instance = nullptr;

	/* window related */
	// from here --
	static int LUA_setWindowSizeCB(lua_State* L) { return s_pCallbacks->LUA_setWindowSizeCB(L); };
	static int LUA_setWindowFullScreenCB(lua_State* L) { return s_pCallbacks->LUA_setWindowFullScreenCB(L); };

	static int LUA_setCursorEnableCB(lua_State* L) { return s_pCallbacks->LUA_setCursorEnableCB(L); };
	static int LUA_getCursorPositionCB(lua_State * L) { return s_pCallbacks->LUA_getCursorPositionCB(L); };
	static int LUA_CursorVsGUIAABBCB(lua_State * L) { return s_pCallbacks->LUA_CursorVsGUIAABBCB(L); };
	// till here --

	/* scene related */
	// from here --
	static int LUA_createSceneCB(lua_State* L) { return s_pCallbacks->LUA_createSceneCB(L); };
	static int LUA_setActiveSceneCB(lua_State* L) { return s_pCallbacks->LUA_setActiveSceneCB(L); };
	static int LUA_SaveSceneCB(lua_State* L) { return s_pCallbacks->LUA_SaveSceneCB(L); };
	static int LUA_LoadSceneCB(lua_State* L) { return s_pCallbacks->LUA_LoadSceneCB(L); };
	// till here --

	/* graphics related */
	// from here --
	static int LUA_DebugMeshSphereEnableCB(lua_State* L) { return s_pCallbacks->LUA_DebugMeshSphereEnableCB(L); };
	static int LUA_DebugMeshAABBEnableCB(lua_State* L) { return s_pCallbacks->LUA_DebugMeshAABBEnableCB(L); };

	static int LUA_SSAOEnableCB(lua_State* L) { return s_pCallbacks->LUA_SSAOEnableCB(L); };
	static int LUA_SSAOKernelSizeCB(lua_State* L) { return s_pCallbacks->LUA_SSAOKernelSizeCB(L); };
	static int LUA_SSAORadiusCB(lua_State* L) { return s_pCallbacks->LUA_SSAORadiusCB(L); };
	static int LUA_SSAOStrengthCB(lua_State* L) { return s_pCallbacks->LUA_SSAOStrengthCB(L); };

	static int LUA_MBEnableCB(lua_State* L) { return s_pCallbacks->LUA_MBEnableCB(L); };
	static int LUA_MBMaxSampleCB(lua_State* L) { return s_pCallbacks->LUA_MBMaxSampleCB(L); };
	static int LUA_MBScaleCB(lua_State* L) { return s_pCallbacks->LUA_MBScaleCB(L); };

	static int LUA_getSceneResolutionCB(lua_State* L) { return s_pCallbacks->LUA_getSceneResolutionCB(L); };
	static int LUA_getShadowResolutionCB(lua_State* L) { return s_pCallbacks->LUA_getShadowResolutionCB(L); };

	static int LUA_BloomEnableCB(lua_State* L) { return s_pCallbacks->LUA_BloomEnableCB(L); };
	static int LUA_BloomRadiusCB(lua_State* L) { return s_pCallbacks->LUA_BloomRadiusCB(L); };
	static int LUA_BloomSizeCB(lua_State* L) { return s_pCallbacks->LUA_BloomSizeCB(L); };

	static int LUA_FXAAEnableCB(lua_State* L) { return s_pCallbacks->LUA_FXAAEnableCB(L); };
	static int LUA_FXAASizeCB(lua_State* L) { return s_pCallbacks->LUA_FXAASizeCB(L); };

	static int LUA_LFEnableCB(lua_State* L) { return s_pCallbacks->LUA_LFEnableCB(L); };
	static int LUA_LFScaleCB(lua_State* L) { return s_pCallbacks->LUA_LFScaleCB(L); };
	static int LUA_LFBiasCB(lua_State* L) { return s_pCallbacks->LUA_LFBiasCB(L); };
	static int LUA_LFDistortionCB(lua_State* L) { return s_pCallbacks->LUA_LFDistortionCB(L); };
	static int LUA_LFGhostCB(lua_State* L) { return s_pCallbacks->LUA_LFGhostCB(L); };
	static int LUA_LFGhostDispersalCB(lua_State* L) { return s_pCallbacks->LUA_LFGhostDispersalCB(L); };
	static int LUA_LFHaloWidthCB(lua_State* L) { return s_pCallbacks->LUA_LFHaloWidthCB(L); };

	static int LUA_ShadowQualityCB(lua_State * L) { return s_pCallbacks->LUA_ShadowQualityCB(L); };
	static int LUA_ShadowSizeCB(lua_State * L) { return s_pCallbacks->LUA_ShadowSizeCB(L); };
	static int LUA_BlurBackgroundEnableCB(lua_State * L) { return s_pCallbacks->LUA_BlurBackgroundEnableCB(L); };
	static int LUA_FadeCB(lua_State * L) { return s_pCallbacks->LUA_FadeCB(L); };
	static int getLUA_FadeCB(lua_State * L) { return s_pCallbacks->getLUA_FadeCB(L); };
	// till here --

	/*transform component related*/
	// from here --
	static int LUA_TranslateCB(lua_State* L) { return s_pCallbacks->LUA_TranslateCB(L); };
	static int LUA_RotateCB(lua_State* L) { return s_pCallbacks->LUA_RotateCB(L); };
	static int LUA_pushRotateCB(lua_State* L) { return s_pCallbacks->LUA_RotateCB(L); };
	static int LUA_RotateAroundCB(lua_State* L) { return s_pCallbacks->LUA_RotateAroundCB(L); };
	static int LUA_ScaleCB(lua_State* L) { return s_pCallbacks->LUA_ScaleCB(L); };

	static int LUA_setPositionCB(lua_State* L) { return s_pCallbacks->LUA_setPositionCB(L); };
	static int LUA_getPositionCB(lua_State* L) { return s_pCallbacks->LUA_getPositionCB(L); };
	static int LUA_setRotationCB(lua_State* L) { return s_pCallbacks->LUA_setRotationCB(L); };
	static int LUA_getRotationCB(lua_State* L) { return s_pCallbacks->LUA_getRotationCB(L); };
	static int LUA_setScaleCB(lua_State* L) { return s_pCallbacks->LUA_setScaleCB(L); };
	static int LUA_getScaleCB(lua_State* L) { return s_pCallbacks->LUA_getScaleCB(L); };

	static int LUA_setLocalPositionCB(lua_State* L) { return s_pCallbacks->LUA_setLocalPositionCB(L); };
	static int LUA_getLocalPositionCB(lua_State* L) { return s_pCallbacks->LUA_getLocalPositionCB(L); };
	static int LUA_setLocalRotationCB(lua_State* L) { return s_pCallbacks->LUA_setLocalRotationCB(L); };
	static int LUA_getLocalRotationCB(lua_State* L) { return s_pCallbacks->LUA_getLocalRotationCB(L); };
	static int LUA_setLocalScaleCB(lua_State* L) { return s_pCallbacks->LUA_setLocalScaleCB(L); };
	static int LUA_getLocalScaleCB(lua_State* L) { return s_pCallbacks->LUA_getLocalScaleCB(L); };

	static int LUA_LookAtCB(lua_State* L) { return s_pCallbacks->LUA_LookAtCB(L); };
	static int LUA_pushLookAtCB(lua_State* L) { return s_pCallbacks->LUA_LookAtCB(L); };

	static int LUA_setSDragRotateCB(lua_State* L) { return s_pCallbacks->LUA_setSDragRotateCB(L); };
	

	// till here --

	/*camera component related*/
	// from here --
	static int LUA_AddCamComponent(lua_State* L) { return s_pCallbacks->LUA_AddCamComponent(L); };

	// Set fucntions
	static int LUA_SetCamPositionCB(lua_State* L) { return s_pCallbacks->LUA_SetCamPositionCB(L); };
	static int LUA_SetCamTargetCB(lua_State* L) { return s_pCallbacks->LUA_SetCamTargetCB(L); };
	static int LUA_SetCamUpCB(lua_State* L) { return s_pCallbacks->LUA_SetCamUpCB(L); };
	static int LUA_SetCamModeCB(lua_State* L) { return s_pCallbacks->LUA_SetCamModeCB(L); };
	static int LUA_SetMouseControlCB(lua_State* L) { return s_pCallbacks->LUA_SetMouseControlCB(L); };
	static int LUA_SetLookingDirCB(lua_State* L) { return s_pCallbacks->LUA_SetLookingDirCB(L); };
	static int LUA_SetMouseSensitivityCB(lua_State * L) { return s_pCallbacks->LUA_SetMouseSensitivityCB(L); };
	static int LUA_SetZoomDistanceCB(lua_State * L) { return s_pCallbacks->LUA_SetZoomDistanceCB(L); };
	static int LUA_SetZoomSpeedCB(lua_State * L) { return s_pCallbacks->LUA_SetZoomSpeedCB(L); };
	static int LUA_SetPitchLimitCB(lua_State * L) { return s_pCallbacks->LUA_SetPitchLimitCB(L); };
	static int LUA_SetFOVYCB(lua_State * L) { return s_pCallbacks->LUA_SetFOVYCB(L); };
	static int LUA_SetZNearCB(lua_State * L) { return s_pCallbacks->LUA_SetZNearCB(L); };
	static int LUA_SetZFarCB(lua_State * L) { return s_pCallbacks->LUA_SetZFarCB(L); };

	// Get functions
	static int LUA_GetCamPositionCB(lua_State* L) { return s_pCallbacks->LUA_GetCamPositionCB(L); };
	static int LUA_GetCamTargetCB(lua_State* L) { return s_pCallbacks->LUA_GetCamTargetCB(L); };
	static int LUA_GetCamUpCB(lua_State* L) { return s_pCallbacks->LUA_GetCamUpCB(L); };
	static int LUA_GetCamModeCB(lua_State* L) { return s_pCallbacks->LUA_GetCamModeCB(L); };
	static int LUA_GetMouseControlCB(lua_State* L) { return s_pCallbacks->LUA_GetMouseControlCB(L); };
	static int LUA_GetLookingDirCB(lua_State* L) { return s_pCallbacks->LUA_GetLookingDirCB(L); };
	static int LUA_GetMouseSensitivityCB(lua_State * L) { return s_pCallbacks->LUA_GetMouseSensitivityCB(L); };
	static int LUA_GetZoomDistanceCB(lua_State * L) { return s_pCallbacks->LUA_GetZoomDistanceCB(L); };
	static int LUA_GetZoomSpeedCB(lua_State * L) { return s_pCallbacks->LUA_GetZoomSpeedCB(L); };
	static int LUA_GetPitchLimitCB(lua_State * L) { return s_pCallbacks->LUA_GetPitchLimitCB(L); };
	static int LUA_GetFOVYCB(lua_State * L) { return s_pCallbacks->LUA_GetFOVYCB(L); };
	static int LUA_GetZNearCB(lua_State * L) { return s_pCallbacks->LUA_GetZNearCB(L); };
	static int LUA_GetZFarCB(lua_State * L) { return s_pCallbacks->LUA_GetZFarCB(L); };
	// till here --

	/*---Render Component Relations---*/
	// From here --
	static int LUA_AddMeshRendererComponent(lua_State* L) { return s_pCallbacks->LUA_AddMeshRendererComponent(L); };
	static int LUA_SetColorCB(lua_State* L) { return s_pCallbacks->LUA_SetColorCB(L); };
	static int LUA_SetEmissiveCB(lua_State* L) { return s_pCallbacks->LUA_SetEmissiveCB(L); };
	static int LUA_SetShininessCB(lua_State* L) { return s_pCallbacks->LUA_SetShininessCB(L); };
	static int LUA_SetObjectVisibilityCB(lua_State* L) { return s_pCallbacks->LUA_SetObjectVisibilityCB(L); };
	static int LUA_SetMeshNameCB(lua_State* L) { return s_pCallbacks->LUA_SetMeshNameCB(L); };
	static int LUA_GetColorCB(lua_State* L) { return s_pCallbacks->LUA_GetColorCB(L); };
	static int LUA_GetEmissiveCB(lua_State* L) { return s_pCallbacks->LUA_GetEmissiveCB(L); };
	static int LUA_GetShininessCB(lua_State* L) { return s_pCallbacks->LUA_GetShininessCB(L); };
	static int LUA_GetObjectVisibilityCB(lua_State* L) { return s_pCallbacks->LUA_GetObjectVisibilityCB(L); };
	static int LUA_GetMeshNameCB(lua_State* L) { return s_pCallbacks->LUA_GetMeshNameCB(L); };
	// Till here --
	/*--------------------------------*/

	/*---Light Component Relations---*/
	// From here--
	static int LUA_SetLightPosCB(lua_State* L) { return s_pCallbacks->LUA_SetLightPosCB(L); };
	static int LUA_SetLightColorCB(lua_State* L) { return s_pCallbacks->LUA_SetLightColorCB(L); };
	static int LUA_SetAmbientCB(lua_State* L) { return s_pCallbacks->LUA_SetAmbientCB(L); };
	static int LUA_SetDiffuseCB(lua_State* L) { return s_pCallbacks->LUA_SetDiffuseCB(L); };
	static int LUA_SetSpecularCB(lua_State* L) { return s_pCallbacks->LUA_SetSpecularCB(L); };
	static int LUA_GetLightPosCB(lua_State* L) { return s_pCallbacks->LUA_GetLightPosCB(L); };
	static int LUA_GetLightColorCB(lua_State* L) { return s_pCallbacks->LUA_GetLightColorCB(L); };
	static int LUA_GetAmbientCB(lua_State* L) { return s_pCallbacks->LUA_GetAmbientCB(L); };
	static int LUA_GetDiffuseCB(lua_State* L) { return s_pCallbacks->LUA_GetDiffuseCB(L); };
	static int LUA_GetSpecularCB(lua_State* L) { return s_pCallbacks->LUA_GetSpecularCB(L); };
	// Till here--
	/*--------------------------------*/

	/*---Directional Light Component Relations---*/
	// From here--
	static int LUA_AddDirLightComponent(lua_State* L) { return s_pCallbacks->LUA_AddDirLightComponent(L); };
	static int LUA_SetLightDirectionCB(lua_State* L) { return s_pCallbacks->LUA_SetLightDirectionCB(L); };
	static int LUA_GetLightDirectionCB(lua_State* L) { return s_pCallbacks->LUA_GetLightDirectionCB(L); };
	static int LUA_ChangeLightDirectionCB(lua_State* L) { return s_pCallbacks->LUA_ChangeLightDirectionCB(L); };
	// Till here--
	/*--------------------------------*/

	/* ellipsoid component related */
	// from here--
	static int LUA_AddEllipsoidColliderComponent(lua_State* L) { return s_pCallbacks->LUA_AddEllipsoidColliderComponent(L); };
	static int LUA_setEllipsoidR3GravityCB(lua_State* L) { return s_pCallbacks->LUA_setEllipsoidR3GravityCB(L); };
	static int LUA_setEllipsoidRadiusCB(lua_State* L) { return s_pCallbacks->LUA_setEllipsoidRadiusCB(L); };
	static int LUA_setEllipsoidR3VelCB(lua_State* L) { return s_pCallbacks->LUA_setEllipsoidR3VelCB(L); };
	static int LUA_getEllipsoidR3GravityCB(lua_State* L) { return s_pCallbacks->LUA_getEllipsoidR3GravityCB(L); };
	static int LUA_getEllipsoidRadiusCB(lua_State* L) { return s_pCallbacks->LUA_getEllipsoidRadiusCB(L); };
	static int LUA_getEllipsoidR3VelCB(lua_State* L) { return s_pCallbacks->LUA_getEllipsoidR3VelCB(L); };
	static int LUA_isEllipsoidCollideCB(lua_State* L) { return s_pCallbacks->LUA_isEllipsoidCollideCB(L); };
	static int LUA_EllipsoidCollisionCheckCB(lua_State* L) { return s_pCallbacks->LUA_EllipsoidCollisionCheckCB(L); };
	// till here--

	/* AABB component related */
	// from here--
	static int LUA_AddAABBColliderComponent(lua_State* L) { return s_pCallbacks->LUA_AddAABBColliderComponent(L); };
	static int LUA_setPosCB(lua_State* L) { return s_pCallbacks->LUA_setPosCB(L); };
	static int LUA_setHalfSizeCB(lua_State* L) { return s_pCallbacks->LUA_setHalfSizeCB(L); };
	static int LUA_getMinCB(lua_State* L) { return s_pCallbacks->LUA_getMinCB(L); };
	static int LUA_getMaxCB(lua_State* L) { return s_pCallbacks->LUA_getMaxCB(L); };
	static int LUA_getRPosCB(lua_State* L) { return s_pCallbacks->LUA_getRPosCB(L); };
	static int LUA_setAABBCollideCB(lua_State* L) { return s_pCallbacks->LUA_setAABBCollideCB(L); };
	static int LUA_isAABBCollideCB(lua_State* L) { return s_pCallbacks->LUA_isAABBCollideCB(L); };
	static int LUA_AABBCollideAddTagCB(lua_State* L) { return s_pCallbacks->LUA_AABBCollideAddTagCB(L); };
	static int LUA_checkAABBCollideCB(lua_State* L) { return s_pCallbacks->LUA_checkAABBCollideCB(L); };
	static int LUA_getAABBCollideInfoCB(lua_State* L) { return s_pCallbacks->LUA_getAABBCollideInfoCB(L); };
	// till here--

	/* Sphere collider component related */
	// from here--
	static int LUA_AddSphereColliderComponent(lua_State* L) { return s_pCallbacks->LUA_AddSphereColliderComponent(L); };
	static int LUA_setfradiusCB(lua_State* L) { return s_pCallbacks->LUA_setfradiusCB(L); };
	static int LUA_getfradiusCB(lua_State* L) { return s_pCallbacks->LUA_getfradiusCB(L); };
	static int LUA_setSphereCollideCB(lua_State* L) { return s_pCallbacks->LUA_setSphereCollideCB(L); };
	static int LUA_isSphereCollideCB(lua_State* L) { return s_pCallbacks->LUA_isSphereCollideCB(L); };
	static int LUA_SphereCollideAddTagCB(lua_State* L) { return s_pCallbacks->LUA_SphereCollideAddTagCB(L); };
	// till here--

	/* keyboard & mouse component related */
	// from here--
	static int LUA_isKeyPressedCB(lua_State* L)  { return s_pCallbacks->LUA_isKeyPressedCB(L); };
	static int LUA_isKeyHoldCB(lua_State* L)  { return s_pCallbacks->LUA_isKeyHoldCB(L); };
	static int LUA_isKeyTouchedCB(lua_State* L)  { return s_pCallbacks->LUA_isKeyTouchedCB(L); };
	static int LUA_isMouseClickCB(lua_State* L) { return s_pCallbacks->LUA_isMouseClickCB(L); };
	static int LUA_isMouseHoldCB(lua_State* L)  { return s_pCallbacks->LUA_isMouseHoldCB(L); };
	static int LUA_getScrollingCB(lua_State* L) { return s_pCallbacks->LUA_getScrollingCB(L); };
	// till here--

	/* entity init and fetching functions related */
	// from here --
	static int LUA_CreateNewEntityCB(lua_State * L){ return s_pCallbacks->LUA_CreateNewEntityCB(L); }
	static int LUA_EntityAddParentCB(lua_State * L){ return s_pCallbacks->LUA_EntityAddParentCB(L); }
	static int LUA_EntitySetActiveCB(lua_State * L){ return s_pCallbacks->LUA_EntitySetActiveCB(L); }
	static int LUA_EntityAddTagCB(lua_State * L){ return s_pCallbacks->LUA_EntityAddTagCB(L); }
	// till here--

	/* script component related */
	// from here--
	static int LUA_AddScriptComponent(lua_State* L) { return s_pCallbacks->LUA_AddScriptComponent(L); };
	static int LUA_setScriptPath(lua_State* L) { return s_pCallbacks->LUA_setScriptPath(L); };
	// till here--

	/* point light component related */
	// from here--
	static int LUA_AddPointLightComponent(lua_State* L) { return s_pCallbacks->LUA_AddPointLightComponent(L); };
	static int LUA_PointLightSetLightColorCB(lua_State* L) { return s_pCallbacks->LUA_PointLightSetLightColorCB(L); };
	static int LUA_PointLightSetDiffuseCB(lua_State* L) { return s_pCallbacks->LUA_PointLightSetDiffuseCB(L); };
	static int LUA_PointLightSetSpecularCB(lua_State* L) { return s_pCallbacks->LUA_PointLightSetSpecularCB(L); };
	// till here--

	/* mesh collider component related */
	// from here--
	static int LUA_AddMeshColliderComponent(lua_State* L) { return s_pCallbacks->LUA_AddMeshColliderComponent(L); };
	static int LUA_setMeshColliderNameCB(lua_State* L) { return s_pCallbacks->LUA_setMeshColliderNameCB(L); };
	// till here--

	/* trigger component related */
	// from here--
	static int LUA_AddTriggerComponent(lua_State* L) { return s_pCallbacks->LUA_AddTriggerComponent(L); };
	static int LUA_TriggerLock(lua_State* L) { return s_pCallbacks->LUA_TriggerLock(L); };
	static int LUA_isTriggerCB(lua_State* L) { return s_pCallbacks->LUA_isTriggerCB(L); };
	static int LUA_setTriggerCB(lua_State* L) { return s_pCallbacks->LUA_setTriggerCB(L); };
	// till here--

	/* player callback functions here*/
	// from here--
	static int LUA_getPlayerHeadPosCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerHeadPosCB(L); };
	static int LUA_getPlayerBody1PosCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerBody1PosCB(L); };
	static int LUA_getPlayerBody2PosCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerBody2PosCB(L); };
	static int LUA_getPlayerTailPosCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerTailPosCB(L); };
	static int LUA_getPlayerTail1PosCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerTail1PosCB(L); };
	static int LUA_getPlayerTail2PosCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerTail2PosCB(L); };
	static int LUA_getPlayerTail3PosCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerTail3PosCB(L); };
	static int LUA_getPlayerPosCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerPosCB(L); };

	static int LUA_setPlayerPosCB(lua_State* L) { return s_pCallbacks->LUA_setPlayerPosCB(L); };
	static int LUA_playerDeadStateCB(lua_State* L) { return s_pCallbacks->LUA_playerDeadStateCB(L); };

	static int LUA_EndGameCB(lua_State* L) { return s_pCallbacks->LUA_EndGameCB(L); };
	static int LUA_setPlayerVelCB(lua_State* L) { return s_pCallbacks->LUA_setPlayerVelCB(L); };
	static int LUA_setHeadVelCB(lua_State* L) { return s_pCallbacks->LUA_setHeadVelCB(L); };
	static int LUA_setBody1VelCB(lua_State* L) { return s_pCallbacks->LUA_setBody1VelCB(L); };
	static int LUA_setBody2VelCB(lua_State* L) { return s_pCallbacks->LUA_setBody2VelCB(L); };
	static int LUA_setTailVelCB(lua_State* L) { return s_pCallbacks->LUA_setTailVelCB(L); };

	static int LUA_getHeadVelCB(lua_State* L) { return s_pCallbacks->LUA_getHeadVelCB(L); };
	static int LUA_getBody1VelCB(lua_State* L) { return s_pCallbacks->LUA_getBody1VelCB(L); };
	static int LUA_getBody2VelCB(lua_State* L) { return s_pCallbacks->LUA_getBody2VelCB(L); };
	static int LUA_getTailVelCB(lua_State* L) { return s_pCallbacks->LUA_getTailVelCB(L); };

	static int LUA_getAddedVelCB(lua_State* L) { return s_pCallbacks->LUA_getAddedVelCB(L); };

	static int LUA_setPlayerGravityVelCB(lua_State* L) { return s_pCallbacks->LUA_setPlayerGravityVelCB(L); };

	static int LUA_setPlayerStateCB(lua_State* L) { return s_pCallbacks->LUA_setPlayerStateCB(L); };
	static int LUA_getPlayerStateCB(lua_State* L) { return s_pCallbacks->LUA_getPlayerStateCB(L); };

	static int LUA_playerHeadECollisionCheckCB(lua_State* L) { return s_pCallbacks->LUA_playerHeadECollisionCheckCB(L); };
	static int LUA_playerBody1ECollisionCheckCB(lua_State* L) { return s_pCallbacks->LUA_playerBody1ECollisionCheckCB(L); };
	static int LUA_playerBody2ECollisionCheckCB(lua_State* L) { return s_pCallbacks->LUA_playerBody2ECollisionCheckCB(L); };
	static int LUA_playerTailECollisionCheckCB(lua_State* L) { return s_pCallbacks->LUA_playerTailECollisionCheckCB(L); };
	static int LUA_playerECollisionCheckCB(lua_State* L) { return s_pCallbacks->LUA_playerECollisionCheckCB(L); };
	static int LUA_playerAllECollisionCheckCB(lua_State* L) { return s_pCallbacks->LUA_playerAllECollisionCheckCB(L); };

	static int LUA_getHeadCommandStateCB(lua_State* L) { return s_pCallbacks->LUA_getHeadCommandStateCB(L); };
	static int LUA_getHeadAssPosCB(lua_State* L) { return s_pCallbacks->LUA_getHeadAssPosCB(L); };
	static int LUA_getOldHeadAssPosCB(lua_State* L) { return s_pCallbacks->LUA_getOldHeadAssPosCB(L); };
	static int LUA_setOldHeadAssPosCB(lua_State* L) { return s_pCallbacks->LUA_setOldHeadAssPosCB(L); };

	static int LUA_setHeadCommandStateCB(lua_State* L) { return s_pCallbacks->LUA_setHeadCommandStateCB(L); };
	static int LUA_getBody1AssPosCB(lua_State* L) { return s_pCallbacks->LUA_getBody1AssPosCB(L); };
	static int LUA_getBody2AssPosCB(lua_State* L) { return s_pCallbacks->LUA_getBody2AssPosCB(L); };
	static int LUA_getTailAssPosCB(lua_State* L) { return s_pCallbacks->LUA_getTailAssPosCB(L); };
	static int LUA_getTail1AssPosCB(lua_State* L) { return s_pCallbacks->LUA_getTail1AssPosCB(L); };
	static int LUA_getTail2AssPosCB(lua_State* L) { return s_pCallbacks->LUA_getTail2AssPosCB(L); };
	static int LUA_getTail3AssPosCB(lua_State* L) { return s_pCallbacks->LUA_getTail3AssPosCB(L); };

	static int LUA_getHeadDistCB(lua_State* L) { return s_pCallbacks->LUA_getHeadDistCB(L); };
	static int LUA_getBody1DistCB(lua_State* L) { return s_pCallbacks->LUA_getBody1DistCB(L); };
	static int LUA_getBody2DistCB(lua_State* L) { return s_pCallbacks->LUA_getBody2DistCB(L); };
	static int LUA_getTailDistCB(lua_State* L) { return s_pCallbacks->LUA_getTailDistCB(L); };
	static int LUA_getTail1DistCB(lua_State* L) { return s_pCallbacks->LUA_getTail1DistCB(L); };
	static int LUA_getTail2DistCB(lua_State* L) { return s_pCallbacks->LUA_getTail2DistCB(L); };
	static int LUA_getTail3DistCB(lua_State* L) { return s_pCallbacks->LUA_getTail3DistCB(L); };

	static int LUA_getHeadDirCB(lua_State* L) { return s_pCallbacks->LUA_getHeadDirCB(L); };
	static int LUA_setHeadDirCB(lua_State* L) { return s_pCallbacks->LUA_setHeadDirCB(L); };

	static int LUA_getHeadMovingCB(lua_State* L) { return s_pCallbacks->LUA_getHeadMovingCB(L); };
	
	static int LUA_getInactiveBlockCB(lua_State* L) { return s_pCallbacks->LUA_getInactiveBlockCB(L); };

	static int LUA_EntityAddCollectableCB(lua_State* L) { return s_pCallbacks->LUA_EntityAddCollectableCB(L); };
	// till here--

	static int LUA_StartLineCB(lua_State * L) { return s_pCallbacks->LUA_StartLineCB(L); };
	static int LUA_EndLineCB(lua_State * L) { return s_pCallbacks->LUA_EndLineCB(L); };

	// Dino AI
	// from here--
	static int LUA_addDinoAIComponent(lua_State* L) { return s_pCallbacks->LUA_addDinoAIComponent(L); };
	static int LUA_shareDinoAIComponent(lua_State* L) { return s_pCallbacks->LUA_shareDinoAIComponent(L); };
	static int LUA_setDinoHeadLookingDirCB(lua_State* L) { return s_pCallbacks->LUA_setDinoHeadLookingDirCB(L); };
	static int LUA_setDinoBodyLookingDirCB(lua_State* L) { return s_pCallbacks->LUA_setDinoBodyLookingDirCB(L); };
	static int LUA_setDinoTailLookingDirCB(lua_State* L) { return s_pCallbacks->LUA_setDinoTailLookingDirCB(L); };
	static int LUA_getDinoHeadLookingDirCB(lua_State* L) { return s_pCallbacks->LUA_getDinoHeadLookingDirCB(L); };
	static int LUA_getDinoBodyLookingDirCB(lua_State* L) { return s_pCallbacks->LUA_getDinoBodyLookingDirCB(L); };
	static int LUA_getDinoTailLookingDirCB(lua_State* L) { return s_pCallbacks->LUA_getDinoTailLookingDirCB(L); };
	static int LUA_getDinoHeadPositionCB(lua_State* L) { return s_pCallbacks->LUA_getDinoHeadPositionCB(L); };
	static int LUA_getDinoBodyPositionCB(lua_State* L) { return s_pCallbacks->LUA_getDinoBodyPositionCB(L); };
	static int LUA_getDinoTailPositionCB(lua_State* L) { return s_pCallbacks->LUA_getDinoTailPositionCB(L); };
	static int LUA_getDinoHeadFSMCB(lua_State* L) { return s_pCallbacks->LUA_getDinoHeadFSMCB(L); };
	static int LUA_setDinoHeadFSMCB(lua_State* L) { return s_pCallbacks->LUA_setDinoHeadFSMCB(L); };
	static int LUA_DinoSeePlayerCB(lua_State* L) { return s_pCallbacks->LUA_DinoSeePlayerCB(L); };
	static int LUA_DinoAttackPlayerCB(lua_State* L) { return s_pCallbacks->LUA_DinoAttackPlayerCB(L); };
	// till here--

	// UI related
	// from here --
	static int LUA_SkyboxEnableCB(lua_State * L) { return s_pCallbacks->LUA_SkyboxEnableCB(L); };
	static int LUA_PlayerEnableCB(lua_State * L) { return s_pCallbacks->LUA_PlayerEnableCB(L); };
	static int LUA_QuitGameCB(lua_State * L) { return s_pCallbacks->LUA_QuitGameCB(L); };
	static int LUA_sceneRestartCB(lua_State * L) { return s_pCallbacks->LUA_sceneRestartCB(L); };
	static int LUA_CurrentLevelCB(lua_State * L) { return s_pCallbacks->LUA_CurrentLevelCB(L); };
	static int LUA_PointCB(lua_State * L) { return s_pCallbacks->LUA_PointCB(L); };
	static int LUA_CheckpointCB(lua_State * L) { return s_pCallbacks->LUA_CheckpointCB(L); };

	static int LUA_addGUIText(lua_State * L) { return s_pCallbacks->LUA_addGUIText(L); };
	static int LUA_setTextString(lua_State * L) { return s_pCallbacks->LUA_setTextString(L); };
	static int LUA_setTextColor(lua_State * L) { return s_pCallbacks->LUA_setTextColor(L); };
	static int LUA_setTextMaterial(lua_State * L) { return s_pCallbacks->LUA_setTextMaterial(L); };
	static int LUA_setFontType(lua_State * L) { return s_pCallbacks->LUA_setFontType(L); };
	static int LUA_setMaxLine(lua_State * L) { return s_pCallbacks->LUA_setMaxLine(L); };
	static int LUA_setAlpha(lua_State * L) { return s_pCallbacks->LUA_setAlpha(L); };
	// till here --

	// Canvas related
	// From here --
	static int LUA_addCanvas(lua_State * L) { return s_pCallbacks->LUA_addCanvas(L); };
	static int LUA_setInstructionCB(lua_State * L) { return s_pCallbacks->LUA_setInstructionCB(L); };
	static int LUA_getInstructionCB(lua_State * L) { return s_pCallbacks->LUA_getInstructionCB(L); };
	// Till here --

	lua_backend::lua_backend(void)
	{
	}

	lua_backend::~lua_backend(void)
	{
	}

	void lua_backend::setCallBack(LUACallbacks * pCallbacks)
	{
		if (!pCallbacks)
		{
			printf("inapropriate scenes input callbacks, CB \n");
			throw 0;
		}

		// important one
		s_pCallbacks = pCallbacks;
	}

	void lua_backend::pushLUA_setWindowSizeCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setWindowSizeCB);
	}

	void lua_backend::pushLUA_setWindowFullScreenCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setWindowFullScreenCB);
	}

	void lua_backend::pushLUA_setCursorEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setCursorEnableCB);
	}

	void lua_backend::pushLUA_getCursorPositionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getCursorPositionCB);
	}

	void lua_backend::pushLUA_CursorVsGUIAABBCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_CursorVsGUIAABBCB);
	}

	void lua_backend::pushLUA_createSceneCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_createSceneCB);
	}

	void lua_backend::pushLUA_setActiveSceneCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setActiveSceneCB);
	}

	void lua_backend::pushLUA_SaveSceneCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SaveSceneCB);
	}

	void lua_backend::pushLUA_LoadSceneCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LoadSceneCB);
	}

	void lua_backend::pushLUA_DebugMeshSphereEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_DebugMeshSphereEnableCB);
	}

	void lua_backend::pushLUA_DebugMeshAABBEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_DebugMeshAABBEnableCB);
	}

	void lua_backend::pushLUA_SSAOEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SSAOEnableCB);
	}

	void lua_backend::pushLUA_SSAOKernelSizeCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SSAOKernelSizeCB);
	}

	void lua_backend::pushLUA_SSAORadiusCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SSAORadiusCB);
	}

	void lua_backend::pushLUA_SSAOStrengthCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SSAOStrengthCB);
	}

	void lua_backend::pushLUA_MBEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_MBEnableCB);
	}

	void lua_backend::pushLUA_MBMaxSampleCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_MBMaxSampleCB);
	}

	void lua_backend::pushLUA_MBScaleCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_MBScaleCB);
	}
	void lua_backend::pushLUA_getSceneResolutionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getSceneResolutionCB);
	}
	void lua_backend::pushLUA_getShadowResolutionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getShadowResolutionCB);
	}

	void lua_backend::pushLUA_BloomEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_BloomEnableCB);
	}

	void lua_backend::pushLUA_BloomRadiusCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_BloomRadiusCB);
	}

	void lua_backend::pushLUA_BloomSizeCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_BloomSizeCB);
	}

	void lua_backend::pushLUA_FXAAEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_FXAAEnableCB);
	}

	void lua_backend::pushLUA_FXAASizeCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_FXAASizeCB);
	}

	void lua_backend::pushLUA_LFEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LFEnableCB);
	}

	void lua_backend::pushLUA_LFScaleCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LFScaleCB);
	}

	void lua_backend::pushLUA_LFBiasCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LFBiasCB);
	}

	void lua_backend::pushLUA_LFDistortionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LFDistortionCB);
	}

	void lua_backend::pushLUA_LFGhostCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LFGhostCB);
	}

	void lua_backend::pushLUA_LFGhostDispersalCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LFGhostDispersalCB);
	}

	void lua_backend::pushLUA_LFHaloWidthCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LFHaloWidthCB);
	}

	void lua_backend::pushLUA_ShadowQualityCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_ShadowQualityCB);
	}

	void lua_backend::pushLUA_BlurBackgroundEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_BlurBackgroundEnableCB);
	}

	void lua_backend::pushLUA_FadeCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_FadeCB);
	}

	void lua_backend::pushgetLUA_FadeCB(lua_State * L)
	{
		lua_pushcfunction(L, getLUA_FadeCB);
	}

	void lua_backend::pushLUA_AddCamComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddCamComponent);
	}

	void lua_backend::pushLUA_SetCamPositionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetCamPositionCB);
	}

	void lua_backend::pushLUA_SetCamTargetCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetCamTargetCB);
	}

	void lua_backend::pushLUA_SetCamUpCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetCamUpCB);
	}

	void lua_backend::pushLUA_SetCamModeCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetCamModeCB);
	}

	void lua_backend::pushLUA_SetMouseControlCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetMouseControlCB);
	}

	void lua_backend::pushLUA_SetLookingDirCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetLookingDirCB);
	}

	void lua_backend::pushLUA_SetMouseSensitivityCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetMouseSensitivityCB);
	}

	void lua_backend::pushLUA_SetZoomDistanceCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetZoomDistanceCB);
	}

	void lua_backend::pushLUA_SetZoomSpeedCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetZoomSpeedCB);
	}

	void lua_backend::pushLUA_SetPitchLimitCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetPitchLimitCB);
	}

	void lua_backend::pushLUA_SetFOVYCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetFOVYCB);
	}

	void lua_backend::pushLUA_SetZNearCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetZNearCB);
	}

	void lua_backend::pushLUA_SetZFarCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetZFarCB);
	}

	void lua_backend::pushLUA_GetCamPositionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetCamPositionCB);
	}

	void lua_backend::pushLUA_GetCamTargetCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetCamTargetCB);
	}

	void lua_backend::pushLUA_GetCamUpCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetCamUpCB);
	}

	void lua_backend::pushLUA_GetCamModeCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetCamModeCB);
	}

	void lua_backend::pushLUA_GetMouseControlCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetMouseControlCB);
	}

	void lua_backend::pushLUA_GetLookingDirCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetLookingDirCB);
	}

	void lua_backend::pushLUA_GetMouseSensitivityCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetMouseSensitivityCB);
	}

	void lua_backend::pushLUA_GetZoomDistanceCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetZoomDistanceCB);
	}

	void lua_backend::pushLUA_GetZoomSpeedCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetZoomSpeedCB);
	}

	void lua_backend::pushLUA_GetPitchLimitCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetPitchLimitCB);
	}

	void lua_backend::pushLUA_GetFOVYCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetFOVYCB);
	}

	void lua_backend::pushLUA_GetZNearCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetZNearCB);
	}

	void lua_backend::pushLUA_GetZFarCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetZFarCB);
	}
	
	void lua_backend::pushLUA_AddMeshRendererComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddMeshRendererComponent);
	}

	void lua_backend::pushLUA_SetColorCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetColorCB);
	}

	void lua_backend::pushLUA_SetEmissiveCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetEmissiveCB);
	}

	void lua_backend::pushLUA_SetShininessCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetShininessCB);
	}

	void lua_backend::pushLUA_SetObjectVisibilityCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetObjectVisibilityCB);
	}

	void lua_backend::pushLUA_SetMeshNameCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SetMeshNameCB);
	}

	void lua_backend::pushLUA_GetColorCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetColorCB);
	}

	void lua_backend::pushLUA_GetEmissiveCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetEmissiveCB);
	}

	void lua_backend::pushLUA_GetShininessCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetShininessCB);
	}

	void lua_backend::pushLUA_GetObjectVisibilityCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetObjectVisibilityCB);
	}

	void lua_backend::pushLUA_GetMeshNameCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_GetMeshNameCB);
	}

	void lua_backend::pushLUA_SetLightPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_SetLightPosCB);
	}

	void lua_backend::pushLUA_SetLightColorCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_SetLightColorCB);
	}

	void lua_backend::pushLUA_SetAmbientCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_SetAmbientCB);
	}

	void lua_backend::pushLUA_SetDiffuseCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_SetDiffuseCB);
	}

	void lua_backend::pushLUA_SetSpecularCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_SetSpecularCB);
	}

	void lua_backend::pushLUA_GetLightPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_GetLightPosCB);
	}

	void lua_backend::pushLUA_GetLightColorCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_GetLightColorCB);
	}

	void lua_backend::pushLUA_GetAmbientCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_GetAmbientCB);
	}

	void lua_backend::pushLUA_GetDiffuseCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_GetDiffuseCB);
	}

	void lua_backend::pushLUA_GetSpecularCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_GetSpecularCB);
	}

	void lua_backend::pushLUA_AddDirLightComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddDirLightComponent);
	}

	void lua_backend::pushLUA_SetLightDirectionCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_SetLightDirectionCB);
	}

	void lua_backend::pushLUA_GetLightDirectionCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_GetLightDirectionCB);
	}

	void lua_backend::pushLUA_ChangeLightDirectionCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_ChangeLightDirectionCB);
	}

	void lua_backend::pushLUA_ShadowSizeCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_ShadowSizeCB);
	}

	void lua_backend::pushLUA_AddScriptComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddScriptComponent);
	}

	void lua_backend::pushLUA_setScriptPath(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setScriptPath);
	}

	void lua_backend::pushLUA_AddPointLightComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddPointLightComponent);
	}

	void lua_backend::pushLUA_PointLightSetLightColorCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_PointLightSetLightColorCB);
	}

	void lua_backend::pushLUA_PointLightSetDiffuseCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_PointLightSetDiffuseCB);
	}

	void lua_backend::pushLUA_PointLightSetSpecularCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_PointLightSetSpecularCB);
	}
	
	void lua_backend::pushLUA_TranslateCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_TranslateCB);
	}
	void lua_backend::pushLUA_RotateCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_RotateCB);
	}
	void lua_backend::pushLUA_pushRotateCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_pushRotateCB);
	}
	void lua_backend::pushLUA_RotateAroundCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_RotateAroundCB);
	}
	void lua_backend::pushLUA_ScaleCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_ScaleCB);
	}

	void lua_backend::pushLUA_setPositionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setPositionCB);
	}
	void lua_backend::pushLUA_getPositionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getPositionCB);
	}
	void lua_backend::pushLUA_setRotationCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setRotationCB);
	}
	void lua_backend::pushLUA_getRotationCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getRotationCB);
	}
	void lua_backend::pushLUA_setScaleCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setScaleCB);
	}
	void lua_backend::pushLUA_getScaleCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getScaleCB);
	}

	void lua_backend::pushLUA_setLocalPositionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setLocalPositionCB);
	}
	void lua_backend::pushLUA_getLocalPositionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getLocalPositionCB);
	}
	void lua_backend::pushLUA_setLocalRotationCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setLocalRotationCB);
	}
	void lua_backend::pushLUA_getLocalRotationCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getLocalRotationCB);
	}
	void lua_backend::pushLUA_setLocalScaleCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setLocalScaleCB);
	}
	void lua_backend::pushLUA_getLocalScaleCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getLocalScaleCB);
	}

	void lua_backend::pushLUA_LookAtCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_LookAtCB);
	}
	void lua_backend::pushLUA_pushLookAtCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_pushLookAtCB);
	}
	void lua_backend::pushLUA_setSDragRotateCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setSDragRotateCB);
	}

	

	void lua_backend::pushLUA_AddAABBColliderComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddAABBColliderComponent);
	}

	void lua_backend::pushLUA_AddMeshColliderComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddMeshColliderComponent);
	}

	void lua_backend::pushLUA_setMeshColliderNameCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setMeshColliderNameCB);
	}

	void lua_backend::pushLUA_setPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setPosCB);
	}

	void lua_backend::pushLUA_isTriggerCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_isTriggerCB);
	}

	void lua_backend::pushLUA_setTriggerCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setTriggerCB);

	}

	void lua_backend::pushLUA_StartLineCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_StartLineCB);
	}

	void lua_backend::pushLUA_EndLineCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_EndLineCB);
	}

	void lua_backend::pushLUA_setHalfSizeCB(lua_State* L) 
	{
		lua_pushcfunction(L, LUA_setHalfSizeCB);
	}
	void lua_backend::pushLUA_getMinCB(lua_State* L) 
	{
		lua_pushcfunction(L, LUA_getMinCB);
	}
	void lua_backend::pushLUA_getMaxCB(lua_State* L) 
	{
		lua_pushcfunction(L, LUA_getMaxCB);
	}
	void lua_backend::pushLUA_getRPosCB(lua_State* L) 
	{
		lua_pushcfunction(L, LUA_getRPosCB);
	}
	void lua_backend::pushLUA_setAABBCollideCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setAABBCollideCB);
	}
	void lua_backend::pushLUA_isAABBCollideCB(lua_State* L) 
	{
		lua_pushcfunction(L, LUA_isAABBCollideCB);
	}
	void lua_backend::pushLUA_checkAABBCollideCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_checkAABBCollideCB);
	}
	void lua_backend::pushLUA_getAABBCollideInfoCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getAABBCollideInfoCB);
	}

	void lua_backend::pushLUA_AddTriggerComponent(lua_State* L)
	{
		lua_pushcfunction(L, LUA_AddTriggerComponent);
	}
	void lua_backend::pushLUA_TriggerLock(lua_State* L)
	{
		lua_pushcfunction(L, LUA_TriggerLock);
	}

	void lua_backend::pushLUA_addDinoAIComponent(lua_State* L)
	{
		lua_pushcfunction(L, LUA_addDinoAIComponent);
	}

	void lua_backend::pushLUA_shareDinoAIComponent(lua_State* L)
	{
		lua_pushcfunction(L, LUA_shareDinoAIComponent);
	}

	void lua_backend::pushLUA_setDinoHeadLookingDirCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setDinoHeadLookingDirCB);
	}

	void lua_backend::pushLUA_setDinoBodyLookingDirCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setDinoBodyLookingDirCB);
	}

	void lua_backend::pushLUA_setDinoTailLookingDirCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setDinoTailLookingDirCB);
	}

	void lua_backend::pushLUA_getDinoHeadLookingDirCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getDinoHeadLookingDirCB);
	}

	void lua_backend::pushLUA_getDinoBodyLookingDirCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getDinoBodyLookingDirCB);
	}

	void lua_backend::pushLUA_getDinoTailLookingDirCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getDinoTailLookingDirCB);
	}

	void lua_backend::pushLUA_getDinoBodyPositionCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getDinoBodyPositionCB);
	}

	void lua_backend::pushLUA_getDinoHeadPositionCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getDinoHeadPositionCB);
	}

	void lua_backend::pushLUA_getDinoTailPositionCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getDinoTailPositionCB);
	}

	void lua_backend::pushLUA_getDinoHeadFSMCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getDinoHeadFSMCB);
	}

	void lua_backend::pushLUA_setDinoHeadFSMCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setDinoHeadFSMCB);
	}

	void lua_backend::pushLUA_DinoSeePlayerCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_DinoSeePlayerCB);
	}

	void lua_backend::pushLUA_DinoAttackPlayerCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_DinoAttackPlayerCB);
	}

	void lua_backend::pushLUA_AddEllipsoidColliderComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddEllipsoidColliderComponent);
	}
	void lua_backend::pushLUA_setEllipsoidR3GravityCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setEllipsoidR3GravityCB);
	}
	void lua_backend::pushLUA_setEllipsoidRadiusCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setEllipsoidRadiusCB);
	}
	void lua_backend::pushLUA_setEllipsoidR3VelCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setEllipsoidR3VelCB);
	}
	void lua_backend::pushLUA_getEllipsoidR3GravityCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getEllipsoidR3GravityCB);
	}
	void lua_backend::pushLUA_getEllipsoidRadiusCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getEllipsoidRadiusCB);
	}
	void lua_backend::pushLUA_getEllipsoidR3VelCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getEllipsoidR3VelCB);
	}
	void lua_backend::pushLUA_isEllipsoidCollideCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_isEllipsoidCollideCB);
	}
	void lua_backend::pushLUA_EllipsoidCollisionCheckCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_EllipsoidCollisionCheckCB);
	}
	void lua_backend::pushLUA_AABBCollideAddTagCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_AABBCollideAddTagCB);
	}

	void lua_backend::pushLUA_AddSphereColliderComponent(lua_State * L)
	{
		lua_pushcfunction(L, LUA_AddSphereColliderComponent);
	}

	void lua_backend::pushLUA_setfradiusCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setfradiusCB);
	}
	void lua_backend::pushLUA_getfradiusCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getfradiusCB);
	}
	void lua_backend::pushLUA_setSphereCollideCB(lua_State* L) 
	{
		lua_pushcfunction(L, LUA_setSphereCollideCB);
	}
	void lua_backend::pushLUA_isSphereCollideCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_isSphereCollideCB);
	}

	void lua_backend::pushLUA_SphereCollideAddTagCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_SphereCollideAddTagCB);
	}

	void lua_backend::pushLUA_isKeyPressedCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_isKeyPressedCB);
	}
	void lua_backend::pushLUA_isKeyHoldCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_isKeyHoldCB);
	}
	void lua_backend::pushLUA_isKeyTouchedCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_isKeyTouchedCB);
	}
	void lua_backend::pushLUA_isMouseClickCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_isMouseClickCB);
	}
	void lua_backend::pushLUA_isMouseHoldCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_isMouseHoldCB);
	}
	void lua_backend::pushLUA_getScrollingCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getScrollingCB);
	}

	void lua_backend::pushLUA_CreateNewEntityCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_CreateNewEntityCB);
	}

	void lua_backend::pushLUA_EntityAddParentCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_EntityAddParentCB);
	}

	void lua_backend::pushLUA_EntityAddCollectableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_EntityAddCollectableCB);
	}

	void lua_backend::pushLUA_EntitySetActiveCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_EntitySetActiveCB);
	}

	void lua_backend::pushLUA_EntityAddTagCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_EntityAddTagCB);
	}
	
	void lua_backend::pushLUA_getPlayerHeadPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerHeadPosCB);
	}

	void lua_backend::pushLUA_setPlayerPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setPlayerPosCB);
	}

	void lua_backend::pushLUA_playerDeadStateCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_playerDeadStateCB);
	}

	void lua_backend::pushLUA_EndGameCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_EndGameCB);
	}

	void lua_backend::pushLUA_getPlayerBody1PosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerBody1PosCB);
	}
	void lua_backend::pushLUA_getPlayerBody2PosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerBody2PosCB);
	}
	void lua_backend::pushLUA_getPlayerTailPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerTailPosCB);
	}
	void lua_backend::pushLUA_getPlayerTail1PosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerTail1PosCB);
	}
	void lua_backend::pushLUA_getPlayerTail2PosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerTail2PosCB);
	}
	void lua_backend::pushLUA_getPlayerTail3PosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerTail3PosCB);
	}
	void lua_backend::pushLUA_getPlayerPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerPosCB);
	}

	void lua_backend::pushLUA_setPlayerVelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setPlayerVelCB);
	}
	void lua_backend::pushLUA_setHeadVelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setHeadVelCB);
	}
	void lua_backend::pushLUA_setBody1VelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setBody1VelCB);
	}
	void lua_backend::pushLUA_setBody2VelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setBody2VelCB);
	}
	void lua_backend::pushLUA_setTailVelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setTailVelCB);
	}

	void lua_backend::pushLUA_getHeadVelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getHeadVelCB);
	}
	void lua_backend::pushLUA_getBody1VelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getBody1VelCB);
	}
	void lua_backend::pushLUA_getBody2VelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getBody2VelCB);
	}
	void lua_backend::pushLUA_getTailVelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTailVelCB);
	}

	void lua_backend::pushLUA_getAddedVelCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getAddedVelCB);
	}

	void lua_backend::pushLUA_setPlayerGravityVelCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setPlayerGravityVelCB);
	}

	void lua_backend::pushLUA_setPlayerStateCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setPlayerStateCB);
	}
	void lua_backend::pushLUA_getPlayerStateCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getPlayerStateCB);
	}


	void lua_backend::pushLUA_playerHeadECollisionCheckCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_playerHeadECollisionCheckCB);
	}
	void lua_backend::pushLUA_playerBody1ECollisionCheckCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_playerBody1ECollisionCheckCB);
	}
	void lua_backend::pushLUA_playerBody2ECollisionCheckCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_playerBody2ECollisionCheckCB);
	}
	void lua_backend::pushLUA_playerTailECollisionCheckCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_playerTailECollisionCheckCB);
	}
	void lua_backend::pushLUA_playerECollisionCheckCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_playerECollisionCheckCB);
	}
	void lua_backend::pushLUA_playerAllECollisionCheckCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_playerAllECollisionCheckCB);
	}
	void lua_backend::pushLUA_getHeadCommandStateCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getHeadCommandStateCB);
	}
	void lua_backend::pushLUA_getHeadAssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getHeadAssPosCB);
	}
	void lua_backend::pushLUA_getOldHeadAssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getOldHeadAssPosCB);
	}
	void lua_backend::pushLUA_setOldHeadAssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setOldHeadAssPosCB);
	}

	void lua_backend::pushLUA_setHeadCommandStateCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setHeadCommandStateCB);
	}
	void lua_backend::pushLUA_getBody1AssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getBody1AssPosCB);
	}
	void lua_backend::pushLUA_getBody2AssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getBody2AssPosCB);
	}
	void lua_backend::pushLUA_getTailAssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTailAssPosCB);
	}
	void lua_backend::pushLUA_getTail1AssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTail1AssPosCB);
	}
	void lua_backend::pushLUA_getTail2AssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTail2AssPosCB);
	}
	void lua_backend::pushLUA_getTail3AssPosCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTail3AssPosCB);
	}

	void lua_backend::pushLUA_getHeadDistCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getHeadDistCB);
	}
	void lua_backend::pushLUA_getBody1DistCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getBody1DistCB);
	}
	void lua_backend::pushLUA_getBody2DistCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getBody2DistCB);
	}
	void lua_backend::pushLUA_getTailDistCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTailDistCB);
	}
	void lua_backend::pushLUA_getTail1DistCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTail1DistCB);
	}
	void lua_backend::pushLUA_getTail2DistCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTail2DistCB);
	}
	void lua_backend::pushLUA_getTail3DistCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getTail3DistCB);
	}





	void lua_backend::pushLUA_addGUIText(lua_State * L)
	{
		lua_pushcfunction(L, LUA_addGUIText);
	}
	void lua_backend::pushLUA_setTextColor(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setTextColor);
	}
	void lua_backend::pushLUA_setTextString(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setTextString);
	}
	void lua_backend::pushLUA_setTextMaterial(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setTextMaterial);
	}
	void lua_backend::pushLUA_setFontType(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setFontType);
	}
	void lua_backend::pushLUA_setMaxLine(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setMaxLine);
	}
	void lua_backend::pushLUA_setAlpha(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setAlpha);
	}
	
	void lua_backend::pushLUA_SkyboxEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_SkyboxEnableCB);
	}
	void lua_backend::pushLUA_PlayerEnableCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_PlayerEnableCB);
	}

	void lua_backend::pushLUA_QuitGameCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_QuitGameCB);
	}

	void lua_backend::pushLUA_sceneRestartCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_sceneRestartCB);
	}
	
	void lua_backend::pushLUA_CurrentLevelCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_CurrentLevelCB);
	}

	void lua_backend::pushLUA_PointCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_PointCB);
	}
	void lua_backend::pushLUA_CheckpointCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_CheckpointCB);
	}

	void lua_backend::pushLUA_getHeadDirCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getHeadDirCB);
	}
	void lua_backend::pushLUA_setHeadDirCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_setHeadDirCB);
	}

	void lua_backend::pushLUA_getHeadMovingCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getHeadMovingCB);
	}


	void lua_backend::pushLUA_addCanvas(lua_State * L)
	{
		lua_pushcfunction(L, LUA_addCanvas);
	}
	void lua_backend::pushLUA_setInstructionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_setInstructionCB);
	}
	void lua_backend::pushLUA_getInstructionCB(lua_State * L)
	{
		lua_pushcfunction(L, LUA_getInstructionCB);
	}

	void lua_backend::pushLUA_getInactiveBlockCB(lua_State* L)
	{
		lua_pushcfunction(L, LUA_getInactiveBlockCB);
	}

}


