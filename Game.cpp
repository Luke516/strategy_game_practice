/*
 * Game.cpp
 *
 *  Created on: 2014/7/30
 *      Author: LukeWu
 */

#include <cstdio>
#include "Game.h"
#include "BasicObject.h"
#include "Field.h"

Game::Game(int window_width, int window_height)
	:terminate(false),state(state_none),next_state(state_game),window(window_width,window_height),io_handler(&window)
{
}

void Game::init(){
	io_handler.init();
}

void Game::gameActive(){
	while(!terminate && !window.shouldClose()){
		if(next_state != state_none){
			changeState();
		}
		io_handler.update();
		io_handler.render();
	}
	return;
}

void Game::changeState(){
	state = next_state;
	next_state = state_none;
	initState();
}

void Game::initState(){
	switch(state){
	case state_game:
	{
		Field* np = new Field;
		io_handler.push(np);
		break;
	}
	default:
		break;
	}
	return;
}

void Game::keyActive(char c){
	io_handler.keyActive(c);
}
void Game::mouseActive(int button, double x_pos, double y_pos){
	io_handler.mouseActive(button, x_pos, y_pos);
}

void Game::windowResize(int width, int height){
	printf("resize~ %d %d\n",width,height);
	window.setWindowWidth(width);
	window.setWindowHeight(height);
	io_handler.resize();
}
