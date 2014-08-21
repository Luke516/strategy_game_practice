/*
 * MyWindow.h
 *
 *  Created on: 2014/8/5
 *      Author: LukeWu
 */

#ifndef MYWINDOW_H_
#define MYWINDOW_H_
#include <GLFW/glfw3.h>

class MyWindow {
public:
	MyWindow(int hieght,int width);
	bool shouldClose(){return glfwWindowShouldClose(window);}
	void swapBuffer(){glfwSwapBuffers(window);}
	int getWindowHeight(){return h;}
	int getWindowWidth(){return w;}
	void setWindowHeight(int hh){h = hh;}
	void setWindowWidth(int ww){w = ww;}
	GLFWwindow* getWindow(){return window;}
private:
	GLFWwindow* window;
	int h,w;
};

#endif /* MYWINDOW_H_ */
