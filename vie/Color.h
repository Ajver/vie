#pragma once

#include <GL/glew.h>

namespace vie
{
	class Color
	{
	public: 
		Color()
		{
			setColor(255, 255, 255);
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

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	
	const Color RED(255, 0, 0);
	const Color GREEN(0, 255, 0);
	const Color BLUE(0, 0, 255);
	const Color YELLOW(255, 255, 0);
	const Color WHITE(255, 255, 255);
	const Color BLACK(0, 0, 0);
	const Color TRANSPARENT(0, 0, 0, 0);
	const Color ORANGE(255, 192, 0);
	const Color PURPLE(255, 0, 255);
	const Color PINK(255, 0, 128);

}