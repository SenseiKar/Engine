#include "Shader.h"



Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::string vertexSource;
	std::string fragmentSource;
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	std::stringstream VertexStream, FragmentStream;

	VertexStream << vertexFile.rdbuf();
	FragmentStream << fragmentFile.rdbuf();





	vertexFile.close();
	fragmentFile.close();

	vertexSource = VertexStream.str();
	fragmentSource = FragmentStream.str();


	const char* vShaderCode = vertexSource.c_str();
	const char* fShaderCode = fragmentSource.c_str();
	if (!vShaderCode) {
		std::cout << "[ERROR] LOADING VERTEX SHADER CODE!\n";
	};
	if (!fShaderCode) {
		std::cout << "[ERROR] LOADING FRAGMENT SHADER CODE!\n";
	};

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glUseProgram(id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(0);





};


void Shader::SetTex(unsigned int tex0, unsigned int tex1)
{
	glUseProgram(id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);
};

void Shader::bind()
{
	glUseProgram(id);
};

void Shader::SetMat4(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::SetInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(id, name), value);
}