#include "Texture.h"

namespace vie
{

	Texture::Texture() :
		id(0),
		width(0),
		height(0),
		pixels(NULL)
	{
	}

	Texture::Texture(GLuint nid, unsigned int w, unsigned int h, std::vector<unsigned char>& npixels) :
		id(nid),
		width(w),
		height(h),
		pixels(npixels)
	{
	}

	Texture::~Texture()
	{
	}

	GLuint Texture::getID() const
	{
		return id;
	}

	unsigned int Texture::getWidth() const
	{
		return width;
	}
	unsigned int Texture::getHeight() const
	{
		return height;
	}

	Color Texture::getPixelColor(int x, int y) const
	{
		y *= 4;
		x *= 4;

		Color color;
		color.r = pixels[y*width + x];
		color.g = pixels[y*width + x + 1];
		color.b = pixels[y*width + x + 2];
		color.a = pixels[y*width + x + 3];

		return color;
	}

	void Texture::setPixelColor(int x, int y, Color color)
	{
		y *= 4;
		x *= 4;

		pixels[y * width + x] = color.r;
		pixels[y * width + x + 1] = color.g;
		pixels[y * width + x + 2] = color.b;
		pixels[y * width + x + 3] = color.a;
	}

	void Texture::refreshGLBuffer() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(pixels[0]));
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}