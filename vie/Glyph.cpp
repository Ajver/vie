#include "Glyph.h"

#include "Window.h"

namespace vie
{

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

}