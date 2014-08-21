/*
 * Game.h
 *
 *  Created on: 2014/7/30
 *      Author: LukeWu
 */

#ifndef GAME_H_
#define GAME_H_
#include <GLFW/glfw3.h>
#include "IOhandler.h"
#include "MyWindow.h"

enum enum_state{
	state_none,state_menu,state_game,state_setting,state_end
};

class Game {
public:
	Game(int window_width=640, int window_height=480);
	void init();
	void changeNextState(enum_state next);
	void changeState();
	void gameActive();
	void initState();
	void keyActive(char c);
	void mouseActive(int button, double x_pos, double y_pos);
	void windowResize(int width, int height);
	GLFWwindow* getWindow(){return window.getWindow();}
private:
	bool terminate;
	enum_state state;
	enum_state next_state;
	MyWindow window;
	IOhandler io_handler;
	std::vector<BasicObject *>object_list;
};

#endif /* GAME_H_ */
