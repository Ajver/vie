#pragma once

#include <string>
#include <GL/glew.h>

namespace vie
{

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string&, const std::string&);

		void linkShaders();

		void addAtribute(const std::string&);

		GLuint getUnitformLocation(const std::string &);

		void use();
		void unuse();

	private:
		int numAttributes;

		GLuint programID;

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		void compileShader(const std::string&, GLuint);
	};

}