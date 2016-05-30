#ifndef DINOAIC_H
#define DINOAIC_H

#include "Component.h"
#include "MathsHeader.h"
#include "enumc.h"


namespace pp {

	class TransformationC;
	class PlayerManager;
	class GLFW_Window;

	struct DinoValues
	{
		DinoValues() : distance(0.f), Yoffset(0.f), followSpeed(0.f)
		{

		};

		float distance;
		float Yoffset;
		float followSpeed;
		TransformationC* TailT;
	};

	class DinoAIC : public Component
	{
	public:
		DinoAIC(void);
		virtual ~DinoAIC(void);
		
		void update(const float &dt) override;

		void save(ofstream& myFile, const unsigned int& guid) override;

		vec3f dinoHeadLookingDir;
		vec3f dinoBodyLookingDir;

		vec3f dinoTailLookingDir;
		
		vec3f* HeadPosition;
		vec3f* BodyPosition;
		
		DinoValues Tail[4];
		
		DINOHEAD_FSM dinoHeadFSM;

		mat4f getVP(void);
		bool seePlayer[4];

		PlayerManager* player;
		GLFW_Window* w;

		bool attackPlayer;
	};
}
#endif