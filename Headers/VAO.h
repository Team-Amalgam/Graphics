#pragma once
#include "VBO.h"
class VAO
{
private:
public:
	GLuint ID;
	VAO();
	void linkVBO(VBO&, GLuint);
	void bind();
	void unbind();
	void remove();
};

