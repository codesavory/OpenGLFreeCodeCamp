#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>

// vertex shader
const char* vertexShaderSource = "\n"
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"     gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n"
"\0";

// fragment shader
const char* fragmentShaderSource = "\n"
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"     FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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

	//creating shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //shader context, 1 file with string, shader source
	glCompileShader(vertexShader); //compile vertex shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// wrapping shaders into shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

	// create reference container for Vertex array object
	GLuint VAO;
	glGenVertexArrays(1, &VAO); // generating the VAO
	glBindVertexArray(VAO); // make the VAO the current VAO by binding it

	GLuint VBO; //creating a vertex buffer object
	glGenBuffers(1, &VBO);
	// binding in OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind the VBO specifying it is a GL_ARRAY_BUFFER

	//-----------------READ MORE --------------//
	//store vertices to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //vertices modified once and used many times. DRAW - image modified

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // configure the vertex pointer so that OpenGL knows how to read the VBO
	glEnableVertexAttribArray(0); // enable the vertex attribute so that OpenGl knows how to use it

	// bind both the VBO and VAO to 0 so that we don't accidently modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//---------------END of READ MORE-----------//

	glClearColor(0.01f, 0.01f, 0.2f, 1.0f); // specify the background color
	glClear(GL_COLOR_BUFFER_BIT); // write to color buffer - which is in the back buffer
	//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	glfwSwapBuffers(window); // swap the front and back buffers
	
	while (!glfwWindowShouldClose(window)) // wait for the glfw window to be closed using the 'x' button
	{
		glClearColor(0.01f, 0.01f, 0.2f, 1.0f); // specify the background color
		glClear(GL_COLOR_BUFFER_BIT); // write to color buffer - which is in the back buffer
		
		glUseProgram(shaderProgram); // tell OpenGL the shader program to use
		glBindVertexArray(VAO); // bind the VAO so that OpenGL knows to use it
		glDrawArrays(GL_TRIANGLES, 0, 3); //drawing the triangle using the GL_TRIANGLES primitive

		glfwSwapBuffers(window);

		glfwPollEvents(); // poll for resize events and mouse, keyboard events
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}