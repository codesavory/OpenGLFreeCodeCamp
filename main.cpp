#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 	// using OpenGL v3.3

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // using core profile

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL FreeCodeCamp", NULL, NULL); // telling GLFW to create a window of 800x800 with name OpenGL FreeCodeCamp
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window); // make the created windows the current context
	gladLoadGL(); // load GLAD so it configure OpenGL
	
	glViewport(0, 0, 800, 800); // specify the viewport of OpenGL in the windows

	glClearColor(0.01f, 0.01f, 0.2f, 1.0f); // specify the background color
	glClear(GL_COLOR_BUFFER_BIT); // write to color buffer - which is in the back buffer
	//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	glfwSwapBuffers(window); // swap the front and back buffers
	
	while (!glfwWindowShouldClose(window)) // wait for the glfw window to be closed using the 'x' button
	{
		glfwPollEvents(); // poll for resize events and mouse, keyboard events
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}