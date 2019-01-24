#pragma once

#include <GL/glew.h>

namespace vie
{
	class Color
	{
	public: 
		Color()
		{
			setColor(255, 255, 255, 255);
		}

		Color(GLubyte nr, GLubyte ng, GLubyte nb, GLubyte na = 255) :
			r(nr), g(ng), b(nb), a(na) {}

		void setColor(GLubyte nr, GLubyte ng, GLubyte nb, GLubyte na = 255)
		{
			r = nr;
			g = ng;
			b = nb;
			a = na;
		}

		bool operator == (const Color& other) const
		{
			return
				r == other.r &&
				g == other.g &&
				b == other.b &&
				a == other.a;
		}

		bool operator != (const Color& other) const
		{
			return !(operator == (other));
		}

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	namespace COLOR
	{
		const Color RED(255, 0, 0);
		const Color GREEN(0, 255, 0);
		const Color BLUE(0, 0, 255);
		const Color YELLOW(255, 255, 0);
		const Color WHITE(255, 255, 255);
		const Color BLACK(0, 0, 0);
		const Color TRANSPARENT(0, 0, 0, 0);
		const Color ORANGE(255, 128, 0);
		const Color PURPLE(255, 0, 255);
		const Color PINK(255, 128, 128);
		const Color GRAY(128, 128, 128);
		const Color LIGHT_GRAY(192, 192, 192);
		const Color DARK_GRAY(64, 64, 64);
	};

}