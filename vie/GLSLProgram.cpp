#include "GLSLProgram.h"

#include <fstream>
#include <vector>

#include "Errors.h"

namespace vie
{

	GLSLProgram::GLSLProgram() :
		programID(0),
		vertexShaderID(0),
		fragmentShaderID(0),
		numAttributes(0)
	{
	}

	GLSLProgram::~GLSLProgram()
	{

	}

	void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
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

		std::ifstream vertexFile(vertexShaderFilePath);

		if (vertexFile.fail()) {
			perror(vertexShaderFilePath.c_str());
			fatalError("Failed to open " + vertexShaderFilePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}

		vertexFile.close();

		const char *contentsPtr = fileContents.c_str();

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

		compileShader(vertexShaderFilePath, vertexShaderID);
		compileShader(fragmentShaderFilePath, fragmentShaderID);

	}

	void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
	{
		std::ifstream vertexFile(filePath);

		if (vertexFile.fail()) {
			perror(filePath.c_str());
			fatalError("Failed to open " + filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}

		vertexFile.close();

		const char *contentsPtr = fileContents.c_str();

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
			fatalError("Shader " + filePath + "failed to compile!");
		}
	}

	void GLSLProgram::linkShaders()
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


	void GLSLProgram::addAtribute(const std::string &attributeName)
	{
		glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
	}

	GLuint GLSLProgram::getUnitformLocation(const std::string & uniformName)
	{
		GLuint location = glGetUniformLocation(programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform " + uniformName + " not found in shader!");
		}

		return location;
	}

	void GLSLProgram::use()
	{
		glUseProgram(programID);

		for (int i = 0; i < numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse()
	{
		glUseProgram(0);

		for (int i = 0; i < numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

}