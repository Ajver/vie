#include "Texture.h"

namespace vie
{

	Texture::Texture() :
		id(0),
		width(0),
		height(0),
		pixels(nullptr)
	{
	}

	Texture::Texture(GLuint nid, GLuint w, GLuint h, unsigned char* npixels) :
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

	unsigned char* Texture::getPixelsArray() const
	{
		return pixels;
	}

	Color Texture::getPixelColor(GLuint x, GLuint y) const
	{
		y *= 4;
		x *= 4;

		GLuint idx = y * width + x;
		Color color;
		color.r = pixels[idx++];
		color.g = pixels[idx++];
		color.b = pixels[idx++];
		color.a = pixels[idx];

		return color;
	}

	void Texture::setPixelColor(GLuint x, GLuint y, Color color)
	{
		y *= 4;
		x *= 4;

		GLuint idx = y * width + x;

		pixels[idx++] = color.r;
		pixels[idx++] = color.g;
		pixels[idx++] = color.b;
		pixels[idx] = color.a;
	}

	void Texture::refreshGLBuffer() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture Texture::getSubTexture(GLuint x, GLuint y, GLuint w, GLuint h) const
	{
		unsigned char* subTexturePixels = new unsigned char[w * h * 4];

		GLuint textureID;
		glGenTextures(1, &textureID);
		Texture subTexture(textureID, w, h, subTexturePixels);
		
		//GLuint counter = 0;
		//for (int yy = y; yy < y + h; yy++)
		//	for (int xx = x; xx < x + w; xx++)
		//	{
		//		GLuint idx = 4 * (yy * w + xx);
		//		subTexturePixels[counter++] = pixels[idx++];
		//		subTexturePixels[counter++] = pixels[idx++];
		//		subTexturePixels[counter++] = pixels[idx++];
		//		subTexturePixels[counter++] = pixels[idx];
		//	}

		GLuint counter = 0;
		for (int yy = y; yy < y + h; yy++)
			for (int xx = x; xx < x + w; xx++)
			{
				subTexture.setPixelColor(xx-x, yy-y, getPixelColor(xx, yy));
			}

		subTexture.refreshGLBuffer();

		return subTexture;
	}

}