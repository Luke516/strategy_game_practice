/*
 * main.cpp
 *
 *  Created on: 2014/7/29
 *      Author: LukeWu
 */

#define GLM_FORCE_RADIANS

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <cstdio>
#include <cmath>
#include <vector>
#include "MyWindow.h"
#include "MyShader.h"
#include "MyObjLoader.h"
#include "MyTextureLoader.h"
#include "Renderer.h"
#include "KeyBoard.h"
#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Game* game_ptr;

void  myKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key == 'A' and action == GLFW_PRESS)
    printf("A was pressed");
}

void myCourserPositionCallback(GLFWwindow *window, double x, double y){
	game_ptr->mouseActive(0,x,y);
}

int main() {

	if (!glfwInit()) {
		printf("ERROR: could not start GLFW3\n");
		return 1;
	}

	Game game;
	game_ptr = &game;

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	////////////////////////////////////////////////////////////////////////////////////////////

	glfwSetKeyCallback(game.getWindow(),myKeyCallback);
	glfwSetCursorPosCallback(game.getWindow(),myCourserPositionCallback);

	game.init();
	game.gameActive();


	glfwTerminate();
	return 0;
}





