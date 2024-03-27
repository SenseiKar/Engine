#pragma once
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void bind();
	void SetMat4(const char* name, glm::mat4 value);
	void SetVec3(const char* name, glm::vec3 value);
	void SetInt(const char* name, int value);
	void SetTex(unsigned int tex0, unsigned int tex1);


private:
	unsigned int id;
};

