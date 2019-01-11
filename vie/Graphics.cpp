#include "Graphics.h"

#include <fstream>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include "Errors.h"
#include "Window.h"

namespace vie
{

	Graphics::Graphics() :
		vbo(0),
		vao(0),
		sortType(GlyphSortType::TEXTURE)
	{
	}

	Graphics::~Graphics()
	{
	}

	void Graphics::init()
	{
		// Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		colorProgram.compileShaders();
		colorProgram.addAtribute("vertexPosition");
		colorProgram.addAtribute("vertexColor");
		colorProgram.addAtribute("vertexUV");
		colorProgram.linkShaders();

		camera.init();

		createVertexArray();
	}

	void Graphics::begin(GlyphSortType st)
	{
		glClearDepth(1.0);

		// Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Enable the shader
		colorProgram.use();

		GLint textureLocation = colorProgram.getUnitformLocation("mySampler");
		glUniform1i(textureLocation, 0);

		// Set camera matrix
		camera.update();
		GLint pLocation = colorProgram.getUnitformLocation("P");
		glm::mat4 cameraMatrix = camera.getCameraMatrix();

		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		sortType = st;

		// Free the memory
		renderBatches.clear();

		for (int i = 0; i < glyphs.size(); i++)
		{
			delete glyphs[i];
		}
		glyphs.clear();
	}

	void Graphics::end()
	{
		sortGlyphs();
		createRenderBatches();
	}

	void Graphics::setBackgroundColor(const Color& color)
	{
		glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	}

	void Graphics::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, const Color& color)
	{
		Glyph *newGlyph = new Glyph();
		newGlyph->textureID = textureID;
		newGlyph->depth = depth;

		newGlyph->topLeft.setColor(color.r, color.g, color.b, color.a);
		newGlyph->topRight.setColor(color.r, color.g, color.b, color.a);
		newGlyph->bottomLeft.setColor(color.r, color.g, color.b, color.a);
		newGlyph->bottomRight.setColor(color.r, color.g, color.b, color.a);

		newGlyph->topLeft.setPosition(destRect.x, Window::getScreenHeight() - destRect.y);
		newGlyph->topRight.setPosition(destRect.x + destRect.z, Window::getScreenHeight() - destRect.y);
		newGlyph->bottomLeft.setPosition(destRect.x, Window::getScreenHeight() - (destRect.y + destRect.w));
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, Window::getScreenHeight() - (destRect.y + destRect.w));

		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		glyphs.push_back(newGlyph);
	}

	void Graphics::drawTexture(const Texture& texture, float x, float y, const Color& color)
	{
		drawTexture(texture, x, y, texture.width, texture.height, color);
	}

	void Graphics::drawTexture(const Texture& texture, float x, float y, float w, float h, const Color& color)
	{
		draw(glm::vec4(x, y, w, h), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 1.0f, color);
	}
	
	void Graphics::drawTexture(const Texture& texture, glm::vec2& position, const Color& color)
	{
		draw(glm::vec4(position.x, position.y, texture.width, texture.height), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 1.0f, color);
	}

	void Graphics::drawTexture(const Texture& texture, glm::vec2& position, glm::vec2& size, const Color& color)
	{
		draw(glm::vec4(position.x, position.y, size.x, size.y), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 1.0f, color);
	}	

	void Graphics::renderBatch()
	{
		glBindVertexArray(vao);

		for (int i = 0; i < renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, renderBatches[i].textureID);
			glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
		}

		glBindVertexArray(0);

		// Disable all textures
		glBindTexture(GL_TEXTURE_2D, 0);

		// Disable the shader
		colorProgram.unuse();
	}

	void Graphics::createVertexArray()
	{
		if (vao == 0)
			glGenVertexArrays(1, &vao);
		
		glBindVertexArray(vao);

		if (vbo == 0)
			glGenBuffers(1, &vbo);
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Position			  
		// index, How many vars, type, normalize?, size, pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
		// Color 
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
		// UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));

		// Disable all 
		glBindVertexArray(0);
	}

	void Graphics::createRenderBatches()
	{
		if (glyphs.empty())
			return;

		std::vector<Vertex> vertices;
		vertices.resize(glyphs.size() * 6);

		int offset = 0;

		// Current Vertex
		int cv = 0;

		// Create and push new element with specyfic attributes
		renderBatches.emplace_back(0, 6, glyphs[0]->textureID);
		vertices[cv++] = glyphs[0]->topLeft;
		vertices[cv++] = glyphs[0]->bottomLeft;
		vertices[cv++] = glyphs[0]->bottomRight;
		vertices[cv++] = glyphs[0]->bottomRight;
		vertices[cv++] = glyphs[0]->topRight;
		vertices[cv++] = glyphs[0]->topLeft;

		offset += 6;

		// Current Glyph
		int cg = 1;

		for (int cg = 1; cg < glyphs.size(); cg++)
		{
			if (glyphs[cg]->textureID != glyphs[cg - 1]->textureID)
				renderBatches.emplace_back(offset, 6, glyphs[cg]->textureID);
			else
				renderBatches.back().numVertices += 6;

			vertices[cv++] = glyphs[cg]->topLeft;
			vertices[cv++] = glyphs[cg]->bottomLeft;
			vertices[cv++] = glyphs[cg]->bottomRight;
			vertices[cv++] = glyphs[cg]->bottomRight;
			vertices[cv++] = glyphs[cg]->topRight;
			vertices[cv++] = glyphs[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Graphics::sortGlyphs()
	{
		switch (sortType)
		{
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareTexture);
			break;
		}
	}

	bool Graphics::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}
	bool Graphics::compareBackToFront(Glyph* a, Glyph* b)
	{
		return a->depth > b->depth;
	}
	bool Graphics::compareTexture(Glyph* a, Glyph* b)
	{
		// Sorted by texture id
		return a->textureID < b->textureID;
	}

	Graphics::Camera2D::Camera2D() :
		position(0.0f, 0.0f),
		cameraMatrix(1.0f),
		scale(1.0f),
		needsMatrixUpdate(true),
		orthoMatrix(1.0f)
	{
	}

	Graphics::Camera2D::~Camera2D()
	{
	}

	void Graphics::Camera2D::init()
	{
		orthoMatrix = glm::ortho(0.0f, (float)Window::getScreenWidth(), 0.0f, (float)Window::getScreenHeight());
	}

	void Graphics::Camera2D::update()
	{
		if (needsMatrixUpdate)
		{
			init();

			// Camera translation
			glm::vec3 translateVec(-position.x, -position.y, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translateVec);

			// Camera scale
			glm::vec3 scaleVec(scale, scale, 0.0f);
			cameraMatrix = glm::scale(glm::mat4(1.0f), scaleVec) * cameraMatrix;

			needsMatrixUpdate = false;
		}
	}

	glm::vec2 Graphics::Camera2D::screenToWorldPos(glm::vec2 screenPosition)
	{
		screenPosition -= glm::vec2(Window::getScreenWidth() * 0.5f, Window::getScreenHeight() * 0.5f);
		screenPosition /= scale;
		screenPosition += position;

		return screenPosition;
	}

	void Graphics::Camera2D::setPosition(glm::vec2 npos)
	{
		position = npos;
		needsMatrixUpdate = true;
	}

	void Graphics::Camera2D::setScale(float nscale)
	{
		scale = nscale;
		needsMatrixUpdate = true;
	}

	glm::vec2 Graphics::Camera2D::getPosition()
	{
		return position;
	}

	float Graphics::Camera2D::getScale()
	{
		return scale;
	}

	glm::mat4 Graphics::Camera2D::getCameraMatrix()
	{
		return cameraMatrix;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////

	Graphics::GLSLProgram::GLSLProgram() :
		programID(0),
		vertexShaderID(0),
		fragmentShaderID(0),
		numAttributes(0)
	{
	}

	Graphics::GLSLProgram::~GLSLProgram()
	{

	}

	void Graphics::GLSLProgram::compileShaders()
	{
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		programID = glCreateProgram();

		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		if (vertexShaderID == 0)
			fatalError("Vertex shader failed to be created!");

		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		if (fragmentShaderID == 0)
			fatalError("Fragment shader failed to be created!");

		std::string vertexShader = getVertexShader();
		const char *contentsPtr = vertexShader.c_str();

		glShaderSource(vertexShaderID, 1, &contentsPtr, nullptr);

		glCompileShader(vertexShaderID);

		GLint success = 0;
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(vertexShaderID, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(vertexShaderID);


			std::printf("%s\n", &errorLog[0]);
			fatalError("Vertex shader failed to compile!");
		}

		compileShader(getVertexShader(), vertexShaderID);
		compileShader(getFragmentShader(), fragmentShaderID);

	}

	std::string Graphics::GLSLProgram::getVertexShader()
	{
		std::string shaderText = "";

		shaderText += "in vec2 vertexPosition;";
		shaderText += "in vec4 vertexColor;";
		shaderText += "in vec2 vertexUV;";
		shaderText += "out vec2 fragmentPosition;";
		shaderText += "out vec4 fragmentColor;";
		shaderText += "out vec2 fragmentUV;";
		shaderText += "uniform mat4 P;";
		shaderText += "void main() {";
		shaderText += "	gl_Position.xy = (P * vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0)).xy;";
		shaderText += "	gl_Position.z = 0.0;";
		shaderText += "	gl_Position.w = 1.0;";
		shaderText += "	fragmentPosition = vertexPosition;";
		shaderText += "	fragmentColor = vertexColor;";
		shaderText += "	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);";
		shaderText += "}";

		return shaderText;
	}

	std::string Graphics::GLSLProgram::getFragmentShader()
	{
		std::string shaderText = "";

		shaderText += "in vec2 fragmentPosition;";
		shaderText += "in vec4 fragmentColor;";
		shaderText += "in vec2 fragmentUV;";
		shaderText += "out vec4 color;";
		shaderText += "uniform sampler2D mySampler;";
		shaderText += "void main() {";
		shaderText += "vec4 textureColor = texture(mySampler, fragmentUV);";
		shaderText += "color = textureColor * fragmentColor;";
		shaderText += "}";

		return shaderText;
	}

	void Graphics::GLSLProgram::compileShader(const std::string& shaderText, GLuint id)
	{
		const char *contentsPtr = shaderText.c_str();

		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(id);

			std::printf("%s\n", &errorLog[0]);
			fatalError("Shader " + shaderText + "failed to compile!");
		}
	}

	void Graphics::GLSLProgram::linkShaders()
	{
		// Attach our shaders to our program
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);

		// Link our program
		glLinkProgram(programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(programID);
			// Don't leak shaders either.
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);


			// In this simple program, we'll just leave
			std::printf("%s\n", &errorLog[0]);
			fatalError("Shader failed to link!");
		}

		// Always detach shaders after a successful link.
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}


	void Graphics::GLSLProgram::addAtribute(const std::string &attributeName)
	{
		glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
	}

	GLuint Graphics::GLSLProgram::getUnitformLocation(const std::string & uniformName)
	{
		GLuint location = glGetUniformLocation(programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform " + uniformName + " not found in shader!");
		}

		return location;
	}

	void Graphics::GLSLProgram::use()
	{
		glUseProgram(programID);

		for (int i = 0; i < numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void Graphics::GLSLProgram::unuse()
	{
		glUseProgram(0);

		for (int i = 0; i < numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}
}