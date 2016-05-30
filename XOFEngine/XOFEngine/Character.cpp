#include "Character.h"

namespace pp
{
	Character::Character(const int& id, const float & xTextureCoord, const float & yTextureCoord, const float & xTexSize, const float & yTexSize,
		const float & xOffset, const float & yOffset, const float & sizeX, const float & sizeY, const float & xAdvance)
	{
		this->id = id;
		this->xTextureCoord = xTextureCoord;
		this->yTextureCoord = yTextureCoord;
		this->xoffset = xOffset;
		this->yoffset = yOffset;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->xMaxTextureCoord = xTexSize + xTextureCoord;
		this->yMaxTextureCoord = yTexSize + yTextureCoord;
		this->xAdvance = xAdvance;
	}


	Character::~Character(void)
	{
	}

	int Character::getId(void) const
	{
		return id;
	}

	float Character::getxTextureCoord(void) const
	{
		return xTextureCoord;
	}
	 
	float Character::getyTextureCoord(void) const
	{
		return yTextureCoord;
	}

	float Character::getXMaxTextureCoord(void) const
	{
		return xMaxTextureCoord;
	}

	float Character::getYMaxTextureCoord(void) const
	{
		return yMaxTextureCoord;
	}

	float Character::getxOffset(void) const
	{
		return xoffset;
	}

	float Character::getyOffset(void) const
	{
		return yoffset;
	}

	float Character::getSizeX(void) const
	{
		return sizeX;
	}

	float Character::getSizeY(void) const
	{
		return sizeY;
	}

	float Character::getxAdvance(void) const
	{
		return xAdvance;
	}
}