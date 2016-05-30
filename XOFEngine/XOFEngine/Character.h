#ifndef CHARACTER_H
#define CHARACTER_H


namespace pp
{

	// simple data structure class holding information about a certan glyph in the font texture atlas

	class Character
	{
	public:
		Character(const int& id, const float & xTextureCoord, const float & yTextureCoord, const float & xTexSize, const float & yTexSize,
			const float & xOffset, const float & yOffset, const float & sizeX, const float & sizeY, const float & xAdvance);
		~Character(void);

		// get and setter

		int getId(void) const;

		float getxTextureCoord(void) const;

		float getyTextureCoord(void) const;

		float getXMaxTextureCoord(void) const;

		float getYMaxTextureCoord(void) const;

		float getxOffset(void) const;

		float getyOffset(void) const;

		float getSizeX(void) const;

		float getSizeY(void) const;

		float getxAdvance(void) const;

	private:
		// char id
		int id;

		// x position in Pixels in the texture (texcoord)
		float xTextureCoord;

		// y position in Pixels in the texture (texcoord)
		float yTextureCoord;
		
		// width of the char in Pixels(size)
		float sizeX;

		// height of the char in Pixels(size)
		float sizeY;

		//the x distance from the curser to the left edge of the character's quad
		float xoffset;

		//the y distance from the curser to the left edge of the character's quad
		float yoffset;

		// how far in pixels the cursor should advance after adding this character
		float xAdvance;

		float xMaxTextureCoord;
		float yMaxTextureCoord;
	};
}

#endif