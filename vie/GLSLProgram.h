#pragma once

#include <GL/glew.h>
#include <string>

namespace vie
{

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders();

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
		std::string getVertexShader();
		std::string getFragmentShader();
	};

}