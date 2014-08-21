/*
 * MyWindow.cpp
 *
 *  Created on: 2014/8/5
 *      Author: LukeWu
 */

#include <cstdio>
#include "MyWindow.h"

MyWindow::MyWindow(int width, int hieght):w(width),h(hieght)
{
	window = glfwCreateWindow(width, hieght, "space ship war", NULL,NULL);
	if (!window) {
		printf("ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
}

