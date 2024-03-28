#pragma once
#include <glad/glad.h>



#include <iostream>


class Texture
{
public:
	Texture(const char* path);
	void bind();
	

private:
	unsigned int id;
};