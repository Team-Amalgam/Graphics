#pragma once
#include<glad/glad.h>
class VBO
{
private:
public:
	GLuint ID;
	VBO(GLfloat*);
	void bind();
	void unbind();
	void remove();
};

