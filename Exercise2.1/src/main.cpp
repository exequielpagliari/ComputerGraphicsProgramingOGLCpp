#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>
using namespace std;

constexpr int               numVAOs = 1;
GLuint                      renderingProgram;
std::array<GLuint, numVAOs> vao;
constexpr int               MAX_POINT_SIZE = 40;
constexpr int               MIN_POINT_SIZE = 1;
constexpr float             INC            = 0.5F;
struct PointData {
    float sizePoint = 0.0F;  // Tamaño de Punto
    float inc       = INC;   // Offset de incremento
};

constexpr int HEIGTH = 600;
constexpr int WIDTH  = 600;

auto createShaderProgram() -> GLuint {
    GLint       vertCompiled;
    GLint       fragCompiled;
    GLint       linked;
    const char* vshaderSource =
            "#version 430 \n"
            "void main(void) \n"
            "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
    const char* fshaderSource =
            "#version 430 \n"
            "out vec4 color; \n"
            "void main(void) \n"
            "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vShader, 1, &vshaderSource, nullptr);
    glShaderSource(fShader, 1, &fshaderSource, nullptr);
    glCompileShader(vShader);
    glCompileShader(fShader);
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    return vfProgram;
}

// Prototipo de función.
void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao.data());
    glBindVertexArray(vao[0]);
}

// Prototipo de función de dibujado
void display(GLFWwindow* window, double currentTime, PointData& pointData) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);  // clear the background to black, each time
    glUseProgram(renderingProgram);
    pointData.sizePoint += pointData.inc;
    if (pointData.sizePoint > MAX_POINT_SIZE) {
        pointData.inc = -INC;
    }
    if (pointData.sizePoint < MIN_POINT_SIZE) {
        pointData.inc = INC;
    }
    glDrawArrays(GL_POINTS, 0, 1);
    glPointSize(pointData.sizePoint);
}

auto main() -> int {
    PointData pointData;
    if (glfwInit() == 0) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Se crea la ventana
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGTH, "Chapter2 - exercise1", nullptr, nullptr);
    // Se da contexto de glfw a la ventana.
    glfwMakeContextCurrent(window);
    // Se inicia Glew
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }
    // Se genera un intervalo de tiempo en la ventana.
    glfwSwapInterval(1);
    // Se llama a la función init creada anteriormente
    init(window);
    // Bucle de renderizado
    while (glfwWindowShouldClose(window) == 0) {
        // Función de renderizado
        display(window, glfwGetTime(), pointData);
        // Intercamcion de buffers
        glfwSwapBuffers(window);
        // Detección de eventos
        glfwPollEvents();
    }
    // Destrucción de ventana
    glfwDestroyWindow(window);
    // Se destruye la ejeccuón de glfw
    glfwTerminate();
    // Se termina la ejecución de la aplicación
    exit(EXIT_SUCCESS);
}
