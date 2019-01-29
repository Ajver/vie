#include "GLSLProgram.h"

#include "Errors.h"
#include <vector>

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

	void GLSLProgram::init()
	{
		compileShaders();
		addAtribute("vertexPosition");
		addAtribute("vertexColor");
		addAtribute("vertexUV");
		linkShaders();
	}

	void GLSLProgram::compileShaders()
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

	std::string GLSLProgram::getVertexShader()
	{
		std::string shaderText = "";

		shaderText += "#version 130 \n";
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

	std::string GLSLProgram::getFragmentShader()
	{
		std::string shaderText = "";

		shaderText += "#version 130 \n";
		shaderText += "in vec2 fragmentPosition;";
		shaderText += "in vec4 fragmentColor;";
		shaderText += "in vec2 fragmentUV;";
		shaderText += "out vec4 color;";
		shaderText += "uniform sampler2D sampler;";
		shaderText += "void main() {";
		shaderText += "vec4 textureColor = texture(sampler, fragmentUV);";
		shaderText += "color = textureColor * fragmentColor;";
		shaderText += "}";

		return shaderText;
	}

	void GLSLProgram::compileShader(const std::string& shaderText, GLuint id)
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


	void GLSLProgram::addAtribute(const std::string& attributeName)
	{
		glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
	}

	GLuint GLSLProgram::getUnitformLocation(const std::string& uniformName)
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
