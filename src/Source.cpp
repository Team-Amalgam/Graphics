#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"
"void main(){\n"
"gl_Position=vec4(aPos,1.0f);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 inColor;\n"
"void main(){\n"
"color=inColor;\n"
"}\0";

const int width = 800;
const int height = 800;

void processInput(GLFWwindow* window);

int main()
{
	//initilaize window
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Window not created";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	//creating a traingle
	float positions[] = {
		-0.5f,-0.5f,0.0f,//bottom left
		0.5f,-0.5f,0.0f,//bottom right
		-0.5f,0.5f,0.0f,//top left
		0.5f,0.5f,0.0f,//top right
	};
	GLuint indices[] = {
		0,1,2,
		2,3,1
	};
	//shaders program

	//vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//check for errors
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length*sizeof(char));
		glGetShaderInfoLog(vertexShader, length, &length, message);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << message << std::endl;
	}

	//fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//check for errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(fragmentShader, length, &length, message);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << message << std::endl;
	}

	//creating Program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	//checking for errors
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << message << std::endl;
	}

	//deleting shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Objects
	GLuint VBO,VAO,EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)(0));
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(program,"inColor");

		glUseProgram(program);

		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(program);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}