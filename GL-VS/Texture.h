#pragma once
#include <glad/glad.h>



#include <iostream>


class Texture
{
public:
	Texture(const char* path);
	void bind();
	unsigned int ReturnTex();

private:
	unsigned int id;
};