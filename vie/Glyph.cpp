#include "Glyph.h"

#include "Window.h"

namespace vie
{

	Glyph::Glyph()
	{
	}

	Glyph::Glyph(const Glyph& other) :
		topLeft(other.topLeft),
		topRight(other.topRight),
		bottomLeft(other.bottomLeft),
		bottomRight(other.bottomRight),
		textureID(other.textureID),
		depth(other.depth)
	{
	}

	void Glyph::rotateByAngle(float angle)
	{
		topLeft.rotate(angle);
		topRight.rotate(angle);
		bottomLeft.rotate(angle);
		bottomRight.rotate(angle);
	}

	void Glyph::translateByVec2(const glm::vec2& vec)
	{
		topLeft.translate(vec.x, vec.y);
		topRight.translate(vec.x, vec.y);
		bottomLeft.translate(vec.x, vec.y);
		bottomRight.translate(vec.x, vec.y);
	}

	void Glyph::invertInYAxis(float screenHeight)
	{
		topLeft.position.y = screenHeight - topLeft.position.y;
		topRight.position.y = screenHeight - topRight.position.y;
		bottomLeft.position.y = screenHeight - bottomLeft.position.y;
		bottomRight.position.y = screenHeight - bottomRight.position.y;
	}

	void Glyph::setUV(const glm::vec4& uvRect)
	{
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		bottomLeft.setUV(uvRect.x, uvRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
	}

	void Glyph::setColor(const Color& color)
	{
		topLeft.setColor(color);
		topRight.setColor(color);
		bottomLeft.setColor(color);
		bottomRight.setColor(color);
	}
	
}