#include "VBO.h"

VBO::VBO(GLfloat* positions)
{
	glGenBuffers(1, &ID);
	//bind();
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::remove()
{
	glDeleteBuffers(1, &ID);
}
