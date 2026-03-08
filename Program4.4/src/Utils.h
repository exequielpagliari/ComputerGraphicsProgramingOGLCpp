#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Utils
{

public:
	static string readShaderSource(const char* filePath);
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static bool checkOpenGLError();
	static GLuint createShaderProgram(const char* vp, const char* fp);

};