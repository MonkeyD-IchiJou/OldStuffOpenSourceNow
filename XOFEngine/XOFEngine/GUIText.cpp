#include "GUIText.h"
#include "TextMesh.h"
#include "FontType.h"
#include "TransformationC.h"
#include "Entity.h"
#include "engine_common.h"
#include "FontShader.h"
#include "ShaderHeaven.h"
#include "CameraC.h"

namespace pp
{
	FontShader* GUIText::shader = nullptr;

	GUIText::GUIText(const string& text, FontType* font, const float& maxLineLength, const bool& centered) :
		Component(GUITEXT),
		textString(text),
		font(font),
		lineMaxSize(maxLineLength),
		centerText(centered),
		numberOfLines(0),
		fontData(nullptr),
		transform(nullptr),
		fontSize(1.f),
		length(1.f),
		mode(0),
		mainCam(nullptr),
		alpha(0.f)
	{
		color.Set(1.f, 1.f, 1.f);
		if(shader == nullptr) shader = ShaderHeaven::getInstance()->fontshader;
	}

	GUIText::GUIText(void) :
		Component(GUITEXT),
		textString("No Str"),
		font(nullptr),
		lineMaxSize(1.f),
		centerText(false),
		numberOfLines(0),
		fontData(nullptr),
		transform(nullptr),
		fontSize(1.f),
		length(1.f),
		mode(0),
		mainCam(nullptr),
		alpha(0.f)
	{
		color.Set(1.f, 1.f, 1.f);
		if (shader == nullptr) shader = ShaderHeaven::getInstance()->fontshader;
	}

	GUIText::~GUIText(void)
	{
		font = nullptr;

		if (fontData != nullptr)
		{
			delete fontData;
			fontData = nullptr;
		}
	}

	void GUIText::setCamHandle(CameraC * cam)
	{
		this->mainCam = cam;
	}

	void GUIText::update(const float & dt)
	{
		if (updatedFlag)
		{
			// get the transformC
			if (getOwner() != nullptr && transform == nullptr)
			{
				transform = getOwner()->transformC;
				fontSize = transform->scale.x;
			}

			if(fontData) updateTextString();

			updatedFlag = false;
		}

		if (getOwner()->isActive())
		{
			if (mode == 1)
			{
				transform->LookAtCamera(mainCam->getView());
			}
		}
	}

	void GUIText::loadStatic(void)
	{
		fontData = font->loadText(this);
		fontData->bindVertexAttribute(GL_STATIC_DRAW);
	}

	void GUIText::loadDynamic(void)
	{
		fontData = font->loadText(this);
		fontData->bindVertexAttribute(GL_DYNAMIC_DRAW);
	}

	void GUIText::draw(void) const
	{
		if (getOwner()->isActive())
		{
			float linel = getTextLength();
			mat4f t;
			t.SetToIdentity();
			t.SetToTranslation(-fontSize, 0, 0);

			shader->load_color(color);
			shader->load_FontMaterial(material);
			shader->load_Translation(transform->localPosition);

			shader->load_Translation(transform->getFinalMat4()); // for this is the final matrix man
			shader->load_MiddleTranslate(t);

			shader->load_Mode(mode);
			shader->load_Alpha(alpha);

			font->bindTex(FONT_TEXTURE_UNIT);
			
			fontData->Render();

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void GUIText::updateTextString(void)
	{
		if (getOwner()->isActive())
		{
			fontData->clearVertices(); // clear the previous vertices .. we are going to calculate new one every frame
			font->updateText(this, fontData);
			fontData->updateVertexAttribute(); // after get the new vertices .. update opengl
		}
	}
	
	void GUIText::setFontType(FontType * font)
	{
		this->font = font;
		updatedFlag = true;
	}

	FontType * GUIText::getFont(void) const
	{
		return font;
	}

	void GUIText::save(ofstream & myFile, const unsigned int & guid)
	{
		myFile << "Entity.addGUIText(" << guid << ") \n";

		myFile << "Entity.getGUIText.setText(" << guid << ", '" << textString << "') \n";
		myFile << "Entity.getGUIText.setFont(" << guid << ", 'FORCESQUARE') \n";
		myFile << "Entity.getGUIText.setMaxLineLength(" << guid << ", " << lineMaxSize << ") \n";
		myFile << "Entity.getGUIText.setMode(" << guid << ", " << mode << ") \n";
		myFile << "Entity.getGUIText.setCentered(" << guid << ", " << centerText << ") \n";
	}
}