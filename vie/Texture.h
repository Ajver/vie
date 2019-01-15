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
		Texture(GLuint nid, unsigned int w, unsigned int h, std::vector<unsigned char>& npixels);
		~Texture();

		GLuint getID() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		Color getPixelColor(int x, int y) const;
		void setPixelColor(int x, int y, Color color);
		
		// Refresh OpenGL buffer (do it after calling setPixelColor)
		void refreshGLBuffer() const;

	private:
		GLuint id;
		unsigned int width;
		unsigned int height;
		std::vector<unsigned char> pixels;
	};

}