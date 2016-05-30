#include "ModelLibrary.h"
#include "BasicMesh.h"
#include "AxisLineMesh.h"
#include "GrassMesh.h"
#include "DebugMesh.h"
#include "LineMesh.h"

namespace pp
{
	ModelLibrary* ModelLibrary::s_instance = nullptr;

	void ModelLibrary::init(void)
	{
		initALLMesh();
	}

	void ModelLibrary::cleanUP(void)
	{
		if (models.size() != 0)
		{
			for (map<string, Mesh*>::iterator it = models.begin(); it != models.end(); ++it)
			{
				delete it->second;
			}
			models.clear();
		}
	}


	void ModelLibrary::initALLMesh(void)
	{
		// prevent memory leak
		cleanUP();

		// two most basic mesh will load first
		models["LINE"] = new LineMesh();
		models["LINE"]->LoadMesh();

		models["SPHEREDEBUG"] = new DebugMesh();
		models["SPHEREDEBUG"]->LoadMesh("Content//meshes//Entity//common//sphere.obj");

		models["CUBEDEBUG"] = new DebugMesh();
		models["CUBEDEBUG"]->LoadMesh("Content//meshes//Entity//common//cube.obj");

		models["QUAD"] = new BasicMesh();
		models["QUAD"]->LoadMesh("Content//meshes//Entity//common//quad.obj");

		models["SPHERE"] = new BasicMesh();
		models["SPHERE"]->LoadMesh("Content//meshes//Entity//common//sphere.obj");

		models["LIGHTVOLUME"] = new BasicMesh();
		models["LIGHTVOLUME"]->LoadMesh("Content//meshes//Entity//common//cube.obj");

		models["CUBE"] = new BasicMesh();
		models["CUBE"]->LoadMesh("Content//meshes//Entity//common//cube.obj");

		models["CUBEIN"] = new BasicMesh();
		models["CUBEIN"]->LoadMesh("Content//meshes//Entity//common//cubein.obj");

		models["GRASSSharp"] = new BasicMesh();
		models["GRASSSharp"]->LoadMesh("Content//meshes//Entity//common//grass.obj");

		models["SHEEP1"] = new BasicMesh();
		models["SHEEP1"]->LoadMesh("Content//meshes//Entity//common//sheep1.obj");

		models["SHEEP2"] = new BasicMesh();
		models["SHEEP2"]->LoadMesh("Content//meshes//Entity//common//sheep2.obj");

		models["CNMHEAD"] = new BasicMesh();
		models["CNMHEAD"]->LoadMesh("Content//meshes//Entity//common//cnmHead2.obj");

		models["CNMBODY"] = new BasicMesh();
		models["CNMBODY"]->LoadMesh("Content//meshes//Entity//common//cnmBody2.obj");

		models["DRAGONHEAD"] = new BasicMesh();
		models["DRAGONHEAD"]->LoadMesh("Content//meshes//Entity//common//dragonHead.obj");

		models["DRAGONHEADC"] = new BasicMesh();
		models["DRAGONHEADC"]->LoadMesh("Content//meshes//Entity//common//dragonHeadCollider.obj");

		models["DRAGONBODY"] = new BasicMesh();
		models["DRAGONBODY"]->LoadMesh("Content//meshes//Entity//common//dragonBody.obj");

		models["DRAGONBODY2"] = new BasicMesh();
		models["DRAGONBODY2"]->LoadMesh("Content//meshes//Entity//common//dragonBody2.obj");

		models["DRAGONTAIL"] = new BasicMesh();
		models["DRAGONTAIL"]->LoadMesh("Content//meshes//Entity//common//dragonTail.obj");

		models["DRAGONTEETH"] = new BasicMesh();
		models["DRAGONTEETH"]->LoadMesh("Content//meshes//Entity//common//dragonTeeth.obj");

		models["DRAGONTEETHUP"] = new BasicMesh();
		models["DRAGONTEETHUP"]->LoadMesh("Content//meshes//Entity//common//dragonTeethUP.obj");

		models["DRAGONTEETHDOWN"] = new BasicMesh();
		models["DRAGONTEETHDOWN"]->LoadMesh("Content//meshes//Entity//common//dragonTeethDOWN.obj");

		models["DRAGONTEETHUPC"] = new BasicMesh();
		models["DRAGONTEETHUPC"]->LoadMesh("Content//meshes//Entity//common//dragonTeethUPC.obj");

		models["DRAGONTEETHDOWNC"] = new BasicMesh();
		models["DRAGONTEETHDOWNC"]->LoadMesh("Content//meshes//Entity//common//dragonTeethDOWNC.obj");

		models["DRAGONHEADHORN"] = new BasicMesh();
		models["DRAGONHEADHORN"]->LoadMesh("Content//meshes//Entity//common//dragonHeadHorns.obj");

		models["DRAGONPOWERCUBE"] = new BasicMesh();
		models["DRAGONPOWERCUBE"]->LoadMesh("Content//meshes//Entity//common//dragonPowerCube.obj");

		models["DRAGONBODY1HORN"] = new BasicMesh();
		models["DRAGONBODY1HORN"]->LoadMesh("Content//meshes//Entity//common//dragonBody1Horn.obj");

		models["DRAGONBODY2HORN"] = new BasicMesh();
		models["DRAGONBODY2HORN"]->LoadMesh("Content//meshes//Entity//common//dragonBody2Horn.obj");

		models["DRAGONTAILHORN"] = new BasicMesh();
		models["DRAGONTAILHORN"]->LoadMesh("Content//meshes//Entity//common//dragonTailHorn.obj");

		models["DRAGONTAIL1"] = new BasicMesh();
		models["DRAGONTAIL1"]->LoadMesh("Content//meshes//Entity//common//dragonTail1.obj");
		models["DRAGONTAIL2"] = new BasicMesh();
		models["DRAGONTAIL2"]->LoadMesh("Content//meshes//Entity//common//dragonTail2.obj");
		models["DRAGONTAIL3"] = new BasicMesh();
		models["DRAGONTAIL3"]->LoadMesh("Content//meshes//Entity//common//dragonTail3.obj");

		models["DRAGONTAIL1HORN"] = new BasicMesh();
		models["DRAGONTAIL1HORN"]->LoadMesh("Content//meshes//Entity//common//dragonTail1Horn.obj");
		models["DRAGONTAIL2HORN"] = new BasicMesh();
		models["DRAGONTAIL2HORN"]->LoadMesh("Content//meshes//Entity//common//dragonTail2Horn.obj");
		models["DRAGONTAIL3HORN"] = new BasicMesh();
		models["DRAGONTAIL3HORN"]->LoadMesh("Content//meshes//Entity//common//dragonTail3Horn.obj");

		models["DINOHEAD"] = new BasicMesh();
		models["DINOHEAD"]->LoadMesh("Content//meshes//Entity//common//dinoHead.obj");
		models["DINOHEADCOLLISION"] = new BasicMesh();
		models["DINOHEADCOLLISION"]->LoadMesh("Content//meshes//Entity//common//dinoHeadCollision.obj");
		models["DINOBODY"] = new BasicMesh();
		models["DINOBODY"]->LoadMesh("Content//meshes//Entity//common//dinoBody.obj");
		models["DINOLEFTHAND"] = new BasicMesh();
		models["DINOLEFTHAND"]->LoadMesh("Content//meshes//Entity//common//dinoLeftHand.obj");
		models["DINORIGHTHAND"] = new BasicMesh();
		models["DINORIGHTHAND"]->LoadMesh("Content//meshes//Entity//common//dinoRightHand.obj");
		models["DINOLEFTLEG"] = new BasicMesh();
		models["DINOLEFTLEG"]->LoadMesh("Content//meshes//Entity//common//dinoLeftLeg.obj");
		models["DINORIGHTLEG"] = new BasicMesh();
		models["DINORIGHTLEG"]->LoadMesh("Content//meshes//Entity//common//dinoRightLeg.obj");
		models["DINOGLOW"] = new BasicMesh();
		models["DINOGLOW"]->LoadMesh("Content//meshes//Entity//common//dinoGlow.obj");
		models["DINOTEETH"] = new BasicMesh();
		models["DINOTEETH"]->LoadMesh("Content//meshes//Entity//common//dinoTeeth.obj");
		models["DINOHORN"] = new BasicMesh();
		models["DINOHORN"]->LoadMesh("Content//meshes//Entity//common//dinoHorns.obj");
		models["DINOTAILBIG"] = new BasicMesh();
		models["DINOTAILBIG"]->LoadMesh("Content//meshes//Entity//common//dinoTailBig.obj");
		models["DINOTAILMED"] = new BasicMesh();
		models["DINOTAILMED"]->LoadMesh("Content//meshes//Entity//common//dinoTailMed.obj");
		models["DINOTAILS"] = new BasicMesh();
		models["DINOTAILS"]->LoadMesh("Content//meshes//Entity//common//dinoTailSmall.obj");
		models["DINOTAILXS"] = new BasicMesh();
		models["DINOTAILXS"]->LoadMesh("Content//meshes//Entity//common//dinoTailSmallSmall.obj");

		models["DINOTAILHORNBIG"] = new BasicMesh();
		models["DINOTAILHORNBIG"]->LoadMesh("Content//meshes//Entity//common//dinoTailHornL.obj");
		models["DINOTAILHORNMED"] = new BasicMesh();
		models["DINOTAILHORNMED"]->LoadMesh("Content//meshes//Entity//common//dinoTailHornM.obj");
		models["DINOTAILHORNS"] = new BasicMesh();
		models["DINOTAILHORNS"]->LoadMesh("Content//meshes//Entity//common//dinoTailHornS.obj");
		models["DINOTAILHORNXS"] = new BasicMesh();
		models["DINOTAILHORNXS"]->LoadMesh("Content//meshes//Entity//common//dinoTailHornXS.obj");


		models["LEVELROUND"] = new BasicMesh();
		models["LEVELROUND"]->LoadMesh("Content//meshes//Entity//common//levelRound.obj");

		models["LEVELROUNDC"] = new BasicMesh();
		models["LEVELROUNDC"]->LoadMesh("Content//meshes//Entity//common//levelRoundC.obj");

		models["DRAGONBALL"] = new DebugMesh();
		models["DRAGONBALL"]->LoadMesh("Content//meshes//Entity//common//dragonball.obj");
	}

	ModelLibrary::ModelLibrary(void) 
	{
	}


	ModelLibrary::~ModelLibrary(void) 
	{
		cleanUP();
	}
}
