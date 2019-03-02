#pragma once

#include <GL/glew.h>

namespace vie
{
	class Color
	{
	public: 
		Color();
		Color(GLubyte nr, GLubyte ng, GLubyte nb, GLubyte na = 255);

		void setColor(GLubyte nr, GLubyte ng, GLubyte nb, GLubyte na = 255);
		bool operator == (const Color& other) const;
		bool operator != (const Color& other) const;
		Color operator * (const Color& other) const;
		Color operator *= (const Color& other);
		Color operator + (const Color& other) const;
		Color operator += (const Color& other);
		Color operator - (const Color& other) const;
		Color operator -= (const Color& other);

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