#pragma once
#include <glad/glad.h>
#include <iostream>



class VAO
{
public:
	VAO();
	void setAttrib();
	void bind();


private:
	unsigned int id;


};