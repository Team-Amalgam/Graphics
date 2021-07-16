#include"Shader.h"
#pragma once
class Program
{
private:
	GLuint program;
	int success;
public:
	Program();
	GLuint getProgram();
	void makeShaders();
	void errorCheck();
	void activate();
	~Program();
};

