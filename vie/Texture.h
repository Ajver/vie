#pragma once

#include <GL/glew.h>
#include <vector>

#include "Color.h"

namespace vie
{

	class Texture
	{
	public:
		Texture();
		explicit Texture(const std::string& texturePath);
		Texture(GLuint nid, GLuint w, GLuint h, unsigned char* npixels);
		~Texture();

		GLuint getID() const;
		GLuint getWidth() const;
		GLuint getHeight() const;
		unsigned char* getPixelsArray() const;

		Color getPixelColor(GLuint x, GLuint y) const;
		void setPixelColor(GLuint x, GLuint y, Color color);
		
		// Refresh OpenGL buffer (do it after calling setPixelColor)
		void refreshGLBuffer() const;

		Texture getSubTexture(GLuint x, GLuint y, GLuint w, GLuint h) const;

	private:
		GLuint id;
		GLuint width;
		GLuint height;
		unsigned char* pixels;
	};

}