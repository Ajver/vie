#include "Texture.h"

#include "FileManager.h"

namespace vie
{

	Texture::Texture() :
		id(0),
		size(0, 0),
		pixels(nullptr)
	{
	}

	Texture::Texture(const std::string& texturePath)
	{
		*this = FileManager::getTexture(texturePath);
	}

	Texture::Texture(GLuint nid, float w, float h, unsigned char* npixels) :
		id(nid),
		size(w, h),
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

	glm::vec2 Texture::getSize() const
	{
		return size;
	}

	unsigned char* Texture::getPixelsArray() const
	{
		return pixels;
	}

	Color Texture::getPixelColor(GLuint x, GLuint y) const
	{
		y *= 4;
		x *= 4;

		GLuint idx = y * size.x + x;
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

		GLuint idx = y * size.x + x;

		pixels[idx++] = color.r;
		pixels[idx++] = color.g;
		pixels[idx++] = color.b;
		pixels[idx] = color.a;
	}

	void Texture::refreshGLBuffer() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture Texture::getSubTexture(GLuint x, GLuint y, GLuint w, GLuint h) const
	{
		unsigned char* subTexturePixels = new unsigned char[w * h * 4];

		GLuint textureID;
		glGenTextures(1, &textureID);
		Texture subTexture(textureID, w, h, subTexturePixels);

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