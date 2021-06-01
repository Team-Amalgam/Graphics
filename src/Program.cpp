#include "Program.h"

Program::Program()
{
	program = glCreateProgram();
	makeShaders();
}

GLuint Program::getProgram()
{
	return program;
}

void Program::makeShaders()
{
	Shader shader;
	shader.createShader();
	shader.attachShader(program);
	glLinkProgram(program);
	errorCheck();
}

Program::~Program()
{
	glDeleteProgram(program);
}

void Program::errorCheck()
{
	//checking for errors
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << message << std::endl;
	}
}
