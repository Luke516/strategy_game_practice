/*
 * Field.cpp
 *
 *  Created on: 2014/7/30
 *      Author: LukeWu
 */

#include <cstdio>
#include "Field.h"


Field::Field(){
	Ship new_ship(0,0,0),new_ship2(-7,0,0),new_ship3(7,0,0);
	ship_list.push_back(new_ship);
	ship_list.push_back(new_ship2);
	ship_list.push_back(new_ship3);
}

Field::~Field(){
	ship_list.clear();
}

void Field::render(Renderer *renderer){
	for(unsigned int i=0; i<ship_list.size(); i++){
		ship_list[i].render(renderer);
	}
	return;

}

void Field::update(){
	return;
}

void Field::keyActive(char c){
	return;
}

void Field::mouseActive(int button, glm::vec3 pos, glm::vec3 dir){
	if (button != 0) {
		for (unsigned int i = 0; i < selected_list.size(); i++) {
			ship_list[selected_list[i]].setMode(0);
			selected_list.clear();
		}
		for (unsigned int i = 0; i < touched_list.size(); i++) {
			ship_list[touched_list[i]].setMode(2);
			selected_list.push_back(touched_list[i]);
		}
		return;
	}
	touched_list.clear();
	float t,tmin(-1.0);
	unsigned int selected_ship = 0;
	if(dir[0]==0)dir[0]=0.00001;
	if(dir[1]==0)dir[1]=0.00001;
	if(dir[2]==0)dir[2]=0.00001;
	for(unsigned int i=0; i<ship_list.size(); i++){
		if(ship_list[i].getMode() == 1)ship_list[i].setMode(0);
		t = ship_list[i].mouseActive(button, pos, dir);
		if((tmin<0 || t<tmin) && t>0)selected_ship = i+1;
	}
	if(selected_ship>0){
		if(ship_list[selected_ship-1].getMode() == 0){
			ship_list[selected_ship-1].setMode(1);
			touched_list.push_back(selected_ship-1);
		}
	}
	return;
}
