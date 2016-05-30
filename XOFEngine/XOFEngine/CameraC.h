#ifndef CAMERA_H
#define CAMERA_H

#include "MathsHeader.h"

#include "Component.h"
#include "enumc.h"
#include "Frustum.h"

namespace pp
{
	struct ProjectionProp
	{
		ProjectionProp(void) :
		fovy(45.0),
		aspect(0.0),
		zNear(0.1),
		zFar(500.0),
		projectionMode(PERSPECTIVE)
		{
		}

		double fovy, aspect, zNear, zFar;
		PROJECTION_MODE projectionMode;
	};

	class CameraC : public Component
	{
	public:
		CameraC(void);
		virtual ~CameraC(void);

		// initialisation
		virtual void Init(void);

		void update(const float & dt) override;
		void save(ofstream& myFile, const unsigned int& guid) override;

		// get the projection matrix
		// world projection setting
		inline void setProjection(const double& fovy, const double& aspect, const double& zNear, const double& zFar) { projection.fovy = fovy; projection.aspect = aspect; projection.zNear = zNear; projection.zFar = zFar; updatedFlag = true; }
		inline void setProjection(const double& left, const double& right, const double& bottom, const double& top, const double& nearVal, const double& farVal) { updatedFlag = true; }
		inline void setProjectionMode(const PROJECTION_MODE & mode) { projection.projectionMode = mode; updatedFlag = true; }
		inline void setFOV(const double& set) { projection.fovy = set; updatedFlag = true; }
		inline void setAspect(const double& set) { projection.aspect = set; updatedFlag = true; }
		inline void setzNear(const double& set) { projection.zNear = set; updatedFlag = true; }
		inline void setzFar(const double& set) { projection.zFar = set; updatedFlag = true; }
		inline double getFOV(void) { return projection.fovy; };
		inline double getZNear(void) { return projection.zNear; };
		inline double getZFar(void) { return projection.zFar; };
		void updateProjection(void); // perspective or ortho
		virtual mat4f getProjection(void) const;

		// get the view matrix
		mat4f getView(void) const;

		// view is always updating every frame
		void updateView(void);

		// return Projection * View mat4f .. for frustum culling calc
		virtual mat4f getVP(void) const;

		// return the left and right angle 
		inline float getTurningAngle(void) const { return turningAngle; }

		// return the up and down angle
		inline float getTiltingAngle(void) const { return tiltingAngle; }

		inline void setTiltingAngle(const float & t) { tiltingAngle = t; }
	public:
		// all the setting and datas
		vec3f position, target, up, lookingDir;

		float MOUSE_SENSITIVITY, ZOOM_DISTANCE, ZOOM_SPEED, PITCH_LIMIT;

		CAMERA_MODE mode;

		bool renderActive, mouseControl;

		CFrustum* frustum;

	protected:

		// update the position and target based on pitch and yaw
		void MouseControl(const float& dt);

		// final view
		mat4f View;

		// final projection
		mat4f Projection;

		float pitch, yaw;
		float turningAngle, tiltingAngle;

		ProjectionProp projection;

	private:
		// helper to look up and down
		void LookUpAndDown(const float& a);
		void TurnLeftAndRight(const float& a);

		inline void FPSTargetUpdate(void) { target = position + lookingDir; }
		inline void TPSPositionUpdate(void) { vec3f zoom = lookingDir * ZOOM_DISTANCE; position = target - zoom; }
	};
}

#endif

