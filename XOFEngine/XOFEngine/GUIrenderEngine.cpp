#include "GUIrenderEngine.h"
#include "FontType.h"
#include "GUIText.h"
#include "Entity.h"

#include "TransformationC.h"
#include "FontsLibrary.h"

#include "ShaderHeaven.h"
#include "FontShader.h"
#include "engine_common.h"
#include "World.h"

#include "GLFW_Window.h"
namespace pp
{
	GUIrenderEngine* GUIrenderEngine::s_instance = nullptr;

	void GUIrenderEngine::setUp(void)
	{
		font->bindTex(FONT_TEXTURE_UNIT);

		fontshader = ShaderHeaven::getInstance()->fontshader;
		fontshader->Start();
		fontshader->load_TextureUnit(FONT_TEXTURE_UNIT_INDEX);
		fontshader->Stop();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GUIrenderEngine::Update(const float & dt)
	{
	}

	void GUIrenderEngine::renderGUI(const World& world) const
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		// blending enable and setting
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		fontshader->Start();
		world.renderAllText();
		fontshader->Stop();

		glDisable(GL_BLEND);
	}

	void GUIrenderEngine::render(Entity & entity) const
	{
		GUIText* g = entity.findComponentT<GUIText>();
		g->draw();
	}

	GUIrenderEngine::GUIrenderEngine(void) : 
		fontshader(nullptr), 
		windowHandle(nullptr), 
		font(nullptr), 
		typestr("Bravely Dragon"), 
		polygon(nullptr), 
		forcesquare(nullptr)
	{
		windowHandle = GLFW_Window::getInstance();
		font = FontsLibrary::getInstance()->FontTypes["PRISMFONT"];
		polygon = FontsLibrary::getInstance()->FontTypes["POLYGONFONT"];
		forcesquare = FontsLibrary::getInstance()->FontTypes["FORCESQUARE"];
	}

	GUIrenderEngine::~GUIrenderEngine(void)
	{
	}
}