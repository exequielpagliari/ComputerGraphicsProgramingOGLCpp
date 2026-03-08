#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];

string readShaderSource(const char* filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}
void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}
bool checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}


GLuint createShaderProgram() {
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;
	string vertShaderStr = readShaderSource("vertShader.glsl");
	string fragShaderStr = readShaderSource("fragShader.glsl");
	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);
	glCompileShader(vShader);
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		cout << "vertex compilation failed" << endl;
		printShaderLog(vShader);
	}
	glCompileShader(fShader);
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		cout << "fragment compilation failed" << endl;
		printShaderLog(fShader);
	}
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	checkOpenGLError();
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		cout << "linking failed" << endl;
		printProgramLog(vfProgram);
	}
	return vfProgram;
}

//Prototipo de función.
void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

//Prototipo de función de dibujado
void display(GLFWwindow* window, double currentTime) {
	glUseProgram(renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}


int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Se crea la ventana
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program2", NULL, NULL);
	//Se da contexto de glfw a la ventana.
	glfwMakeContextCurrent(window);
	//Se inicia Glew
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	//Se genera un intervalo de tiempo en la ventana.
	glfwSwapInterval(1);
	//Se llama a la función init creada anteriormente
	init(window);
	//Bucle de renderizado
	while (!glfwWindowShouldClose(window)) {
		//Función de renderizado
		display(window, glfwGetTime());
		//Intercamcion de buffers 
		glfwSwapBuffers(window);
		//Detección de eventos
		glfwPollEvents();
	}
	//Destrucción de ventana
	glfwDestroyWindow(window);
	//Se destruye la ejeccuón de glfw
	glfwTerminate();
	//Se termina la ejecución de la aplicación
	exit(EXIT_SUCCESS);
}