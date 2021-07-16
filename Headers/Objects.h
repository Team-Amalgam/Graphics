#pragma once
#include<iostream>
#include "VAO.h"
#include "EBO.h"
class Objects
{
private:
	GLuint* indices;
	float* positions;
public:
	GLuint VAO, VBO, EBO;
	Objects();
	Objects(GLuint*,float*,size_t,size_t);
	~Objects();
};

