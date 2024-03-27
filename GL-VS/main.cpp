

#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include "VAO.h"
#include "VBO.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//#include "Texture.h"
#include "Shader.h"



//FLOAT = 4 byte
//INT = 4 byte



void processInput(GLFWwindow* window);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


int main(int argc, char* argv[])
{

	if (argc >= 2) {
		std::cout << argv[1] << std::endl;
	}
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_TEXTURE_2D);

	stbi_set_flip_vertically_on_load(true);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("I:/Library/proj/GL-VS/GL-VS/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "[ERROR] LOADING TEXTURE!\n";
	};
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width2, height2, nrChannels2;
	unsigned char* data2 = stbi_load("I:/Library/proj/GL-VS/GL-VS/fun.jpg", &width2, &height2, &nrChannels2, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "[ERROR] LOADING TEXTURE!\n";
	};
	stbi_image_free(data2);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	Shader shader0("I:/Library/proj/GL-VS/GL-VS/vertex.vert", "I:/Library/proj/GL-VS/GL-VS/fragment.frag");
	shader0.bind();
	shader0.SetInt("texture0", 0);
	shader0.SetInt("texture1", 1);
	
	VAO vao;
	VBO vbo;
	
	vao.bind();
	vbo.buffer();
	vao.setAttrib();
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	
		


	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");


	float fov = 80.0f;
	ImGuiWindowFlags mainWindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	glm::vec3 cubePositions[] = {
		glm::vec3(900.0f,0.0f,0.0f),
		
	};
	int cubeNumber = 0;

	bool CameraEditorMenu = true;
	bool CubeCreationMenu = true;
	bool MapLoaderMenu = true;
	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();
		ImGui::Begin("Main Menu",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(ImVec2(200, 300));
		ImGui::SetWindowPos(ImVec2(0, 0));
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Editors"))
			{
				if (ImGui::MenuItem("Camera Editor"))
				{
					CameraEditorMenu = true;
				};
				if (ImGui::MenuItem("Cube Creation Editor"))
				{
					CubeCreationMenu = true;
					

				};
				if (ImGui::MenuItem("Map Editor"))
				{
					MapLoaderMenu = true;
				};
				ImGui::EndMenu();
				
			};
			ImGui::EndMenuBar();

			

		};
		ImGui::End();


		
		if (CameraEditorMenu)
		{
			ImGui::Begin("Camera Editor", &CameraEditorMenu);
			ImGui::SetWindowSize(ImVec2(300, 300));
			ImGui::SliderFloat("FOV", &fov, 10.0f, 130.0f);



			ImGui::End();
		}

		if (CubeCreationMenu)
		{
			ImGui::Begin("Box Creation Editor", &CubeCreationMenu);
			ImGui::SetWindowSize(ImVec2(300, 300));


			if (ImGui::Button("New")) {
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			};
			ImGui::SliderFloat("X", &x, -10.0f, 10.0f);
			ImGui::SliderFloat("Y", &y, -10.0f, 10.0f);
			ImGui::SliderFloat("Z", &z, -10.0f, 10.0f);
			if (ImGui::Button("Build")) {
				cubePositions[cubeNumber] = glm::vec3(x, y, z);
			};
		


			ImGui::End();
		}
		if (MapLoaderMenu)
		{
			ImGui::Begin("Map Editor", &MapLoaderMenu);
			ImGui::SetWindowSize(ImVec2(300, 300));





			ImGui::End();
		}
		
		


	

		




		




		
		processInput(window);


		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));


		

		glm::mat4 view = glm::mat4(1.0f);
		/*
		view = glm::translate(view, glm::vec3(x, y, z)); */
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(fov), 1920.0f / 1080.0f, 0.1f, 100.f);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		


		shader0.bind();
		

		/*
		int vertexColorLoc = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLoc, 0.0f, 1.0f, 0.0f, 1.0f); */

		shader0.SetMat4("view", view);
		shader0.SetMat4("projection", projection);
		shader0.SetMat4("transform", transform);
		
		
		

		for (int i = 0; i <= (sizeof(cubePositions) /3 /4); i++)
		{
			vao.bind();

			model = glm::translate(model, cubePositions[i]);

			shader0.SetMat4("model", model);


			

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}; 


		//glBindVertexArray(array);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();





	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwTerminate();


	const float cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;



}