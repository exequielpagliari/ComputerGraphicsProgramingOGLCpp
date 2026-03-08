#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
using namespace std;

#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];




GLuint createShaderProgram() {
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;
	const char* vshaderSource =
		"#version 430 \n"
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
	const char* fshaderSource =
		"#version 430 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ if (gl_FragCoord.x < 200) color = vec4(1.0, 0.0, 0.0, 1.0); else color = vec4(0.0, 0.0, 1.0, 1.0);}";
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
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
	glPointSize(30.0f);
	glDrawArrays(GL_POINTS, 0, 1);

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