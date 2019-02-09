#pragma once

#ifndef SPRITE_FONT_H_
#define SPRITE_FONT_H_

#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "Vertex.h"
#include "TextJustification.h"

namespace vie 
{

	class Texture;
	class Graphics;

	struct CharGlyph 
	{
		char character;
		glm::vec4 uvRect;
		glm::vec2 size;
	};

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

	class SpriteFont
	{
	public:
		SpriteFont(const char* font, int size, char cs, char ce);
		SpriteFont(const char* font, int size)
			: SpriteFont(font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR) {}

		void dispose();
		glm::vec2 measure(const char* s);
		void draw(Graphics* g, const char* s, glm::vec2 position, glm::vec2 scaling, float depth, const Color& tint, TextJustification just = TextJustification::LEFT);

		// getters
		int getFontHeight() const {
			return _fontHeight;
		}
	private:
		static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);
		int _regStart;
		int _regLength;
		CharGlyph* _glyphs;
		int _fontHeight;

		unsigned int _texID;
	};

}

#endif // SPRITE_FONT_H_﻿