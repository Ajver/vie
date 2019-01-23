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

		void init();

		GLuint getUnitformLocation(const std::string& uniformName);

		void use();
		void unuse();

	private:
		int numAttributes;

		GLuint programID;

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		void compileShaders();
		void compileShader(const std::string&, GLuint);
		void linkShaders();
		void addAtribute(const std::string& attributeName);
		std::string getVertexShader();
		std::string getFragmentShader();
	};

}