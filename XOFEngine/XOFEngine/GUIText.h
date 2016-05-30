#ifndef GUITEXT_H
#define GUITEXT_H

#include "Component.h"
#include <string>
#include "mat4.h"
using std::string;

#include "vec3.h"
using namespace Math;

namespace pp
{
	struct FontMaterial
	{
		FontMaterial(void)
		{
			width = 0.45f;
			edge = 0.1f;
			borderwidth = 0.6f;
			borderedge = 0.1f;
			offsetx = -0.005f;
			offsety = 0.005f;

			coloroutline = vec3f(0.f, 0.f, 0.f);
		}

		float width, edge, borderwidth, borderedge, offsetx, offsety;
		vec3f coloroutline;
	};

	class FontType;
	class TextMesh;
	class FontShader;

	class TransformationC;
	class CameraC;

	class GUIText : public Component
	{
	public:

		// Creates a new text, loads the text's quads into a VAO, and adds the text
		// to the screen.
		GUIText(const string& text, FontType* font, const float& maxLineLength, const bool& centered);
		GUIText(void);

		// every components got its very own update methods
		void update(const float& dt) override;

		// update the string every frame
		void updateTextString(void);

		// load the final vertex and texcoord into opengl ( set up vao )

		void loadStatic(void);

		// load dynamically .. means can change in the future
		void loadDynamic(void);

		// draw this text on the screen
		void draw(void) const;

		// set the font type (when window recreate)
		void setFontType(FontType* font);

		// return the font used by this text
		FontType* getFont(void) const;

		void save(ofstream& myFile, const unsigned int & guid) override;

		inline void setColor(const float& r, const float& g, const float& b) { color.Set(r, g, b); }
		inline vec3f getColor(void) const { return color; }
		inline int getNumberOfLines(void) const { return numberOfLines; }
		inline float getFontSize(void) const { return fontSize; }
		inline void setNumberofLines(const int& number) { this->numberOfLines = number; }
		inline void setCentered(const bool & centered) { this->centerText = centered; }
		inline bool isCentered(void) const { return this->centerText; }
		inline void setMaxLineSize(const float & l) { this->lineMaxSize = l; updatedFlag = true; }
		inline float getMaxLineSize(void) const { return lineMaxSize; }
		inline void setFontSize(const float& s) { this->fontSize = s; updatedFlag = true; }
		inline void setTextString(const string& s) { this->textString = s; updatedFlag = true; }
		inline string &getTextString(void) { return this->textString; }
		inline void setTextLength(const float & l) { this->length = l; }
		inline float getTextLength(void) const { return length; }
		inline void setNoEffects(void) { material.borderwidth = 0.f;  material.offsetx = 0.f; material.offsety = 0.f; }
		inline void setRenderMode(const int & i) { this->mode = i; }
		inline void setAlpha(const float &f) { this->alpha = f; }
		virtual ~GUIText(void);

		// the material of this gui text
		FontMaterial material;

		void setCamHandle(CameraC* cam);

	private:
		string textString;
		vec3f color;
		float lineMaxSize;
		int numberOfLines;
		bool centerText;
		float fontSize;
		float length;
		int mode;
		float alpha;

		FontType* font;
		TextMesh* fontData;  // vertices and texcoord

		TransformationC* transform;
		CameraC* mainCam;

		static FontShader* shader;
	};
}

#endif

