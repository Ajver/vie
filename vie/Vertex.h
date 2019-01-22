#pragma once

#include "Color.h"

namespace vie
{

	struct Vertex
	{
		struct Position
		{
			float x, y;
		};

		//-----------------------------------------------

		struct UV
		{
			float u;
			float v;
		};

		//-----------------------------------------------

		Position position;
		Color color;
		UV uv;

		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void setColor(const Color& ncolor)
		{
			color = ncolor;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};

}