#pragma once
#include<glad/glad.h>
class EBO
{
private:
public:
	GLuint ID;
	EBO(GLuint*);
	void bind();
	void unbind();
	void remove();
};

