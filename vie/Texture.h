#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#include "Color.h"

namespace vie
{

	class Texture
	{
	public:
		Texture();
		explicit Texture(const std::string& texturePath);
		Texture(GLuint nid, float w, float h, unsigned char* npixels);
		~Texture();

		GLuint getID() const;
		glm::vec2 getSize() const;
		unsigned char* getPixelsArray() const;

		Color getPixelColor(GLuint x, GLuint y) const;
		void setPixelColor(GLuint x, GLuint y, Color color);
		
		// Refresh OpenGL buffer (do it after calling setPixelColor)
		void refreshGLBuffer() const;

		Texture getSubTexture(GLuint x, GLuint y, GLuint w, GLuint h) const;

	private:
		GLuint id;
		glm::vec2 size;
		unsigned char* pixels;
	};

}