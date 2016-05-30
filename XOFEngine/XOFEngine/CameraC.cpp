#include "CameraC.h"
#include "Mouse.h"
#include "keys.h"
#include "quat4.h"

namespace pp
{
	CameraC::CameraC(void) :
		MOUSE_SENSITIVITY(300.f),
		ZOOM_DISTANCE(16.5f),
		ZOOM_SPEED(20.f),
		PITCH_LIMIT(85.000f),
		pitch(0.f),
		yaw(0.f),
		turningAngle(0.f),
		tiltingAngle(0.f),
		Component(CAMERA),
		renderActive(true),
		mode(FPS),
		mouseControl(true),
		frustum(nullptr)
	{
		frustum = new CFrustum();
	}

	CameraC::~CameraC(void)
	{
		if (frustum)
		{
			delete frustum;
			frustum = nullptr;
		}
	}

	void CameraC::Init(void)
	{
		this->position = vec3f(5, 0, 0);
		this->lookingDir = vec3f(0, 0, 1.f);
		this->up = vec3f(0.f, 1.f, 0.f);

		// by default is fps mode
		FPSTargetUpdate();
		updateView();
	}

	void CameraC::update(const float & dt)
	{
		if (updatedFlag)
		{
			updateProjection();
			updatedFlag = false;
		}

		// need to control by mouse mah
		if (mouseControl) MouseControl(dt);

		// check what mode is this
		mode == FPS ? FPSTargetUpdate() : TPSPositionUpdate();

		// finally update my damn view
		updateView();

		frustum->setVP(getVP());
	}

	void CameraC::MouseControl(const float& dt)
	{
		float l_yaw = Mouse::getInstance()->getYaw();
		float l_pitch = Mouse::getInstance()->getPitch();

		// for left and right // no need to set limitation
		if (l_yaw != 0.000f)
		{
			yaw = l_yaw * -MOUSE_SENSITIVITY;
			TurnLeftAndRight(yaw);
			turningAngle += yaw;

			if (turningAngle < 0.0000f)
			{
				turningAngle += 360.f;
			}

			if (turningAngle > 360.0000f)
			{
				turningAngle -= 360.f;
			}
		}

		// for up looking with limit
		if (l_pitch > 0.000f)
		{
			pitch = l_pitch * MOUSE_SENSITIVITY;
			float oldAngle = tiltingAngle;
			tiltingAngle += pitch;

			// if reach the limits
			if (tiltingAngle > PITCH_LIMIT)
			{
				LookUpAndDown((PITCH_LIMIT - oldAngle));
				tiltingAngle = PITCH_LIMIT;
			}

			else
			{
				LookUpAndDown(pitch);
			}
		}

		// for down looking with limit
		if (l_pitch < 0.000f)
		{
			pitch = l_pitch * MOUSE_SENSITIVITY;
			float oldAngle = tiltingAngle;
			tiltingAngle += pitch;

			// if reach the limits 
			if (tiltingAngle < -PITCH_LIMIT)
			{
				LookUpAndDown((-PITCH_LIMIT - oldAngle));
				tiltingAngle = -PITCH_LIMIT;
			}

			else
			{
				LookUpAndDown(pitch);
			}
		}

		//ZOOM_DISTANCE += dt * Mouse::getInstance()->getScrolling() * ZOOM_SPEED;
	}

	mat4f CameraC::getView(void) const
	{
		return this->View;
	}

	void CameraC::updateView(void)
	{
		this->View.SetToIdentity();
		this->View.SetToLookAt(position, target, up);
	}

	void CameraC::updateProjection(void)
	{
		if (projection.projectionMode == PERSPECTIVE)
		{
			this->Projection.SetToIdentity();
			Projection.SetToPerspective(projection.fovy, projection.aspect, projection.zNear, projection.zFar);
		}

		else
		{
			// orthographic
		}
	}

	mat4f CameraC::getProjection(void) const
	{
		return this->Projection;
	}

	mat4f CameraC::getVP(void) const
	{
		return this->Projection * View;
	}

	void CameraC::LookUpAndDown(const float& a)
	{
		vec3f right = up.cross(lookingDir);
		right.y = 0;
		right.normalize();
		Quaternion q(a, right);
		lookingDir = q * lookingDir;
	}

	void CameraC::TurnLeftAndRight(const float& a)
	{
		Quaternion q(a, vec3f(0, 1.f, 0));
		lookingDir = q * lookingDir;
	}

	void CameraC::save(ofstream & myFile, const unsigned int& guid)
	{
		myFile << "Entity.addCamera(" << guid << ") \n";

		myFile << "Entity.getCamera.setLookingDir(" << guid << ", " << lookingDir << ") \n";
		myFile << "Entity.getCamera.setUp(" << guid << ", " << up << ") \n";
		myFile << "Entity.getCamera.setTarget(" << guid << ", " << target << ") \n";
		myFile << "Entity.getCamera.setRenderActive(" << guid << ", " << renderActive << ") \n";
		myFile << "Entity.getCamera.setFovy(" << guid << ", " << projection.fovy << ") \n";
		myFile << "Entity.getCamera.setZNear(" << guid << ", " << projection.zNear << ") \n";
		myFile << "Entity.getCamera.setZFar(" << guid << ", " << projection.zFar << ") \n";
		myFile << "Entity.getCamera.setProjectionMode(" << guid << ", " << projection.projectionMode << ") \n";
	}
}
