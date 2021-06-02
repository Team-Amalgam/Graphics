#pragma once
#include<iostream>
#include "VAO.h"
#include "EBO.h"
class Objects
{
private:
	float positions[12] = {
		-0.5f,-0.5f,0.0f,//bottom left
		0.5f,-0.5f,0.0f,//bottom right
		-0.5f,0.5f,0.0f,//top left
		0.5f,0.5f,0.0f,//top right
	};
	GLuint indices[6] = {
		0,1,2,
		2,3,1
	};
public:
	GLuint VAO, VBO, EBO;
	Objects();
	~Objects();
};

