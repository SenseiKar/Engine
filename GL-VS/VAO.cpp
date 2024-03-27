#include "VAO.h"




VAO::VAO()
{
	glGenVertexArrays(1, &id);
	
}

void VAO::setAttrib()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
	glBindVertexArray(0);

}

void VAO::bind()
{
	glBindVertexArray(id);
};