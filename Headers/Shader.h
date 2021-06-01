#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#pragma once
class Shader
{
private:
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	GLuint vertexShader;
	GLuint fragmentShader;
public:
	Shader();
	const char* getVertexShaderSource();
	const char* getFragmentShaderSource();
	void createShader();
	void errorCheck(GLuint);
	void attachShader(GLuint&);
	~Shader();
};

