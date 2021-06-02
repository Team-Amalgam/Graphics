#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cerrno>

void count(const char*);
void createFile(const char*, const char*);

#pragma once
class Shader
{
private:
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	GLuint vertexShader;
	GLuint fragmentShader;
	std::string temp, temp2;
	std::string get_file_contents(const char*);
public:
	Shader();
	const char* getVertexShaderSource();
	const char* getFragmentShaderSource();
	void createShader();
	void errorCheck(GLuint);
	void attachShader(GLuint&);
	~Shader();
	// Reads a text file and outputs a string with everything in the text file
};

