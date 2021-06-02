#include "Shader.h"
Shader::Shader() {
	temp = get_file_contents("Shaders/Shader.vert");
	vertexShaderSource = temp.c_str();

	temp2 = get_file_contents("Shaders/Shader.frag");
	fragmentShaderSource = temp2.c_str();
		
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}
const char* Shader::getVertexShaderSource() {
	return vertexShaderSource;
}
const char* Shader::getFragmentShaderSource()
{
	return vertexShaderSource;
}
void Shader::createShader()
{
	//vertex shader	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	errorCheck(vertexShader);

	//fragment shader	
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	errorCheck(fragmentShader);
}

void Shader::errorCheck(GLuint shader)
{
	//check for errors
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << message << std::endl;
	}
}

void Shader::attachShader(GLuint& program)
{
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
}

Shader::~Shader()
 {
		//deleting shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
}

std::string Shader::get_file_contents(const char* filename)
{
	std::ifstream in(filename);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
void count(const char* someString) {
	char curr = 'a'; int i = 0;
	while (curr != '\0') {
		curr = *someString;
		std::cout << i << ". " << curr << std::endl;
		i++; someString++;
	}
	std::cout << "Length: " << i << std::endl;
}

void createFile(const char* filename, const char* stringToPrint) {
	std::ofstream file(filename, std::ios::out);
	char curr = *stringToPrint;
	while (curr != '\0') {
		file << curr;
		stringToPrint++;
		curr = *stringToPrint;
	}
	file.close();
}
