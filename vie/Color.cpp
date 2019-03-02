#include "Color.h"


namespace vie
{

	GLubyte fixRangeTop(int n)
	{
		if (n > 255)
			return 255;
		return n;
	}

	GLubyte fixRangeBottom(int n)
	{
		if (n < 0)
			return 0;
		return n;
	}

	GLubyte fixRange(int n)
	{
		if (n < 0)
			return 0;
		if (n > 255)
			return 255;
		return n;
	}

	Color::Color()
	{
		setColor(255, 255, 255, 255);
	}

	Color::Color(GLubyte nr, GLubyte ng, GLubyte nb, GLubyte na) :
		r(nr), g(ng), b(nb), a(na) {}

	void Color::setColor(GLubyte nr, GLubyte ng, GLubyte nb, GLubyte na)
	{
		r = nr;
		g = ng;
		b = nb;
		a = na;
	}

	bool Color::operator == (const Color& other) const
	{
		return
			r == other.r &&
			g == other.g &&
			b == other.b &&
			a == other.a;
	}

	bool Color::operator != (const Color& other) const
	{
		return !(operator == (other));
	}

	Color Color::operator * (const Color& other) const
	{
		return Color(
			r * other.r / 255, 
			g * other.g / 255, 
			b * other.b / 255, 
			a * other.a / 255);
	}

	Color Color::operator *= (const Color& other) 
	{
		r = r * other.r / 255;
		g = g * other.g / 255;
		b = b * other.b / 255;
		a = a * other.a / 255;
		return *this;
	}

	Color Color::operator + (const Color& other) const
	{
		return Color(
			fixRangeTop(r + other.r),
			fixRangeTop(g + other.g),
			fixRangeTop(b + other.b),
			fixRangeTop(a + other.a));
	}

	Color Color::operator += (const Color& other)
	{
		r = fixRangeTop(r + other.r);
		g = fixRangeTop(g + other.g);
		b = fixRangeTop(b + other.b);
		a = fixRangeTop(a + other.a);
		return *this;
	}

	Color Color::operator - (const Color& other) const
	{
		return Color(
			fixRangeBottom(r - other.r),
			fixRangeBottom(g - other.g),
			fixRangeBottom(b - other.b),
			fixRangeBottom(a - other.a));
	}

	Color Color::operator -= (const Color& other)
	{
		r = fixRangeBottom(r - other.r);
		g = fixRangeBottom(g - other.g);
		b = fixRangeBottom(b - other.b);
		a = fixRangeBottom(a - other.a);
		return *this;
	}

}
