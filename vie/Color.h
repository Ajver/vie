#pragma once

#include <GL/glew.h>

namespace vie
{
	class Color
	{
	public: 
		Color()
		{
			setColor(0, 0, 0, 255);
		}

		Color(GLubyte nr, GLubyte ng, GLubyte nb, GLubyte na) :
			r(nr), g(ng), b(nb), a(na) {}

		void setColor(GLubyte nr, GLubyte ng, GLubyte nb, GLubyte na)
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
}