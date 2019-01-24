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

		void setPosition(float x, float y);
		void setColor(const Color& ncolor);
		void setUV(float u, float v);
		void rotate(float angle);
		void translate(float x, float y);
	};

}