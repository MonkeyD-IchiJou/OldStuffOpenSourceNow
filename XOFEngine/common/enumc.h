#ifndef ENUMC_H
#define ENUMC_H

#include <string>
using std::string;

static const int MAX_ENTITY = 1000;

static std::string btos(bool b)
{
	if (b)
	{
		return "true";
	}

	return "false";
}

enum ROLES
{
	COMMANDER = 1,
	DEFENDER = 2,
	SHOOTER = 3,
	HEALER = 4,
	LASTROLE
};
enum FILE_ID
{
	TRANSFORM = 0,
	MESHRENDERER,
	ENTITY,
	GRASSRENDERER,
	DIRLIGHT,
	POINTLIGHT,
	CAMERA_ID,
	SCRIPT_ID,
	INVALID_ID
};

enum COMPONENT_TYPE
{
	TRANSFORMATION = 0,
	RENDERER,
	LIGHT,
	GUITEXT,
	CAMERA,
	SCRIPT,
	COLLIDER,
	BULLET,
	TRIGGER,
	AI,
	CANVAS,
	NONE
};

enum PROJECTION_MODE
{
	PERSPECTIVE = 0,
	ORTHOGRAPHIC,
	INVALID_PROJ
};

enum CAMERA_MODE
{
	FPS = 0,
	TPS,
	FREE
};

enum PLAYER_CONTROL_STATE
{
	HEAD = 0,
	BODY1 ,
	BODY2,
	TAIL,
	TAIL1,
	TAIL2,
	TAIL3,
	FULLBODY,
};

enum DRAGON_CHILDBODY_PARTS
{
	TEETH = 0,
	HEADHORN,
	POWERCUBE,
	BODY1HORN,
	BODY2HORN,
	TAILHORN,
	TAIL1HORN,
	TAIL2HORN,
	TAIL3HORN,
	LASTDRAGONCHILD,
};

enum LEADER_HEAD_COMMAND
{
	FOLLOWME = 0,
	STACKPLS,
	ONYOUROWN,
	WINPOSE,
};

enum CANVAS_INSTRUCTION
{
	LEVEL_SELECTION = 0,	// 0
	OPTIONS,				// 1
	LEVEL_SELECTION_BACK,	// 2
	OPTIONS_BACK,			// 3
	CONTINUE,				// 4
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	AT_EASE,
};

enum DINOHEAD_FSM
{
	WALK = 0,
	CHASE,
	SWINGATTACK,
	DINODIE,
	DINOJUMP,
	DINOIDLE,
};

#endif
