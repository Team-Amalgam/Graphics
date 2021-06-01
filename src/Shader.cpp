#include "Shader.h"
Shader::Shader() {
	vertexShaderSource ="#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"
"void main(){\n"
"gl_Position=vec4(aPos,1.0f);\n"
"}\0";

	fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"uniform vec4 inColor;\n"
		"void main(){\n"
		"color=inColor;\n"
		"}\0";
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}
const char* Shader::getVertexShaderSource() {
	return vertexShaderSource;
}
const char* Shader::getFragmentShaderSource()
{
	return vertexShaderSource;
}
void Shader::createShader()
{
	//vertex shader	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	errorCheck(vertexShader);

	//fragment shader	
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	errorCheck(fragmentShader);
}

void Shader::errorCheck(GLuint shader)
{
	//check for errors
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << message << std::endl;
	}
}

void Shader::attachShader(GLuint& program)
{
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
}

Shader::~Shader()
 {
		//deleting shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}


