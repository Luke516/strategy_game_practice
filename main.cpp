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
#include "HexCoordinate.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Game* game_ptr;
bool mouse_right_button_pressed = false;
bool mouse_middle_button_pressed = false;
bool mouse_left_button_pressed = false;

void  myKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
 {
	game_ptr->keyActive(key, action);

}

void myCourserPositionCallback(GLFWwindow *window, double x, double y){
	game_ptr->mouseActive(0,x,y);
}

void myMouseButtonCallback(GLFWwindow *window, int button, int action, int mods){
	if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS){
		mouse_left_button_pressed = true;
		game_ptr->mouseActive(1,0,0);
	}
	else if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE){
		mouse_left_button_pressed = false;
		//game_ptr->mouseActive(-1,0,0);
	}
	else if(button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS){
		mouse_left_button_pressed = true;
		game_ptr->mouseActive(2,0,0);
	}
	else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_RELEASE) {
		mouse_left_button_pressed = false;
	}
}

void myScrollCallback(GLFWwindow *window, double xoffset, double yoffset){
	printf("scroll-- x:%lf y:%lf\n",xoffset,yoffset);
	if(yoffset > 0){
		game_ptr->mouseActive(4,0,0);
	}
	else if(yoffset < 0){
		game_ptr->mouseActive(-4,0,0);
	}
}

void myWindowResizeCallback(GLFWwindow *window, int width, int hieght){

	if(width<640 || hieght<480){
		width=640; hieght=480;
		glfwSetWindowSize(window, width, hieght);
	}
	game_ptr -> windowResize(width, hieght);
}



int main() {
	/* test
	HexCoordinate a(1,2),b(5,9),c,d;
	c = a+b;
	d = a+c;
	if(a.getX()+b.getX()==c.getX() && a.getY()+b.getY()==c.getY())printf("WOWOWOWOW!!!\n");
	*/

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
	glfwSetMouseButtonCallback(game.getWindow(),myMouseButtonCallback);
	glfwSetWindowSizeCallback(game.getWindow(), myWindowResizeCallback);
	glfwSetScrollCallback(game.getWindow(), myScrollCallback);

	game.init();
	game.gameActive();


	glfwTerminate();
	return 0;
}


/*
mouseActive:button:
0->no button
1->left button pressed       -1->left button released
2->right button pressed		 -2->right button released
3->middle button pressed     -3->middle button released
4->scroll up
5->scroll down
*/


