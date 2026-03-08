#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
using namespace std;

//Prototipo de función.
void init(GLFWwindow* window) {}

//Prototipo de función de dibujado
void display(GLFWwindow* window, double currentTime) {
	glClearColor(1.0, 0.0, 0.0, 1.0); //Modifica buffer de color
	glClear(GL_COLOR_BUFFER_BIT); //
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Se crea la ventana
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", NULL, NULL);
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