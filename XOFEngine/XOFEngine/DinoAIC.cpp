#include "DinoAIC.h"

#include "TransformationC.h"
#include "utils.h"

#include "GLFW_Window.h"

#include "PlayerManager.h"


namespace pp {

	DinoAIC::DinoAIC(void) : Component(AI), HeadPosition(nullptr), BodyPosition(nullptr), dinoHeadFSM(WALK), player(nullptr), attackPlayer(false)
	{
		dinoBodyLookingDir.Set(0, 0, 1);
		dinoTailLookingDir = dinoBodyLookingDir;

		ZERO_MEM(Tail);

		// First tail's values
		Tail[0].distance = 2.8f;
		Tail[0].Yoffset = 2.3f;
		Tail[0].followSpeed = 30.f;

		// Second tail's values
		Tail[1].distance = 2.6f;
		Tail[1].Yoffset = 0.f;
		Tail[1].followSpeed = 30.f;

		// Third tail's values
		Tail[2].distance = 1.0f;
		Tail[2].Yoffset = 0.f;
		Tail[2].followSpeed = 30.f;

		// Last tail's values
		Tail[3].distance = 0.9f;
		Tail[3].Yoffset = 0.55f;
		Tail[3].followSpeed = 30.f;

		player = PlayerManager::getInstance();
		w = GLFW_Window::getInstance();

		for (int i = 0; i < TAIL; ++i)
			seePlayer[i] = false;
	}

	DinoAIC::~DinoAIC(void)
	{
		HeadPosition = nullptr;
		player = nullptr;
	}

	mat4f DinoAIC::getVP(void)
	{
		mat4f view, projection;
		view.SetToLookAt(*HeadPosition, *HeadPosition + dinoHeadLookingDir, vec3f(0, 1, 0));
		
		projection.SetToPerspective(45.0, w->getWindowWidth() / w->getWindowHeight(), 0.1, 25.0);

		return projection * view;
	}

	void DinoAIC::update(const float& dt)
	{
		vec3f target;
		vec3f direction;

		if (dinoHeadFSM != SWINGATTACK)
		{
			// First tail's values
			Tail[0].distance = 2.8f;
			Tail[0].Yoffset = 2.3f;
			Tail[0].followSpeed = 30.f;

			// Second tail's values
			Tail[1].distance = 2.6f;
			Tail[1].Yoffset = 0.f;
			Tail[1].followSpeed = 30.f;

			// Third tail's values
			Tail[2].distance = 1.0f;
			Tail[2].Yoffset = 0.f;
			Tail[2].followSpeed = 30.f;

			// Last tail's values
			Tail[3].distance = 0.9f;
			Tail[3].Yoffset = 0.55f;
			Tail[3].followSpeed = 30.f;
		}

		else
		{
			// First tail's values
			Tail[0].distance = 2.8f;
			Tail[0].Yoffset = 2.3f;
			Tail[0].followSpeed = 30.f;

			// Second tail's values
			Tail[1].distance = 2.6f;
			Tail[1].Yoffset = 0.f;
			Tail[1].followSpeed = 30.f;

			// Third tail's values
			Tail[2].distance = 2.0f;
			Tail[2].Yoffset = 0.f;
			Tail[2].followSpeed = 30.f;

			// Last tail's values
			Tail[3].distance = 2.9f;
			Tail[3].Yoffset = 0.55f;
			Tail[3].followSpeed = 30.f;
		}

		for (int i = 0; i < 4; ++i)
		{
			if (i == 0) // If its the big tail, follow the body
			{
				target = *BodyPosition;
				direction = dinoBodyLookingDir.normalized();
			}

			else
			{
				target = Tail[i - 1].TailT->position;
				direction = Tail[i - 1].TailT->lookingDir;
			}

			// Set to 0 so that the tail will not sink when it looks up
			direction.y = 0;

			// First tail following the body's ass
			vec3f BodyAssPos = target - direction * Tail[i].distance;
			BodyAssPos.y -= Tail[i].Yoffset;
			vec3f movingDir = BodyAssPos - Tail[i].TailT->position;

			Tail[i].TailT->Translate(movingDir * dt * Tail[i].followSpeed);
			// Tail Rotation
			Tail[i].TailT->LookAt(target);
		}

		player->DinoSeePlayer(getVP(), seePlayer);

		if (attackPlayer)
			player->attackImpulse(*HeadPosition);
	}

	void DinoAIC::save(ofstream& myFile, const unsigned int& guid)
	{

	}

}