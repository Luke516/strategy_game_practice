/*
 * Field.cpp
 *
 *  Created on: 2014/7/30
 *      Author: LukeWu
 */

#include <cstdio>
#include "Field.h"
#include "HexCoordinate.h"


Field::Field():map(),turn_counter(ship_list),path_finder(&map)
{
	Ship new_ship(5,0,map.getUnitLen());
	ship_list.push_back(new_ship);
}

Field::~Field(){
	ship_list.clear();
}

void Field::render(Renderer *renderer){
	turn_counter.render(renderer);
	map.render(renderer);
	for(unsigned int i=0; i<ship_list.size(); i++){
		ship_list[i].render(renderer);
	}
	return;

}

void Field::update(){
	for (unsigned int i = 0; i < ship_list.size(); i++) {
		ship_list[i].update();
	}
	return;
}

void Field::keyActive(int key, int action){
	return;
}

void Field::mouseActive(int button, glm::vec3 pos, glm::vec3 dir){

	if (button == 1) {//click an object
		for (unsigned int i = 0; i < selected_list.size(); i++) {
			ship_list[selected_list[i]].setMode(0);//clear previous selected
			selected_list.clear();
		}
		map.setMode(-1);
		for (unsigned int i = 0; i < touched_list.size(); i++) {
			ship_list[touched_list[i]].setMode(2);//select object cursor touched
			selected_list.push_back(touched_list[i]);
		}
		map.setMode(2);
		return;
	}
	else if(button ==2){
		printf("Button : 2!!!\n");
		unsigned int no;
		HexCoordinate start(0,0),end(0,0);
		end = map.getTouchedCoordinate();
		for(unsigned int i=0; i<selected_list.size(); i++){
			no = selected_list[i];
			start = ship_list[no].getCoordinate();
			path_finder.findPath(start,end,ship_list[no]);
		}
		return;
	}


	for(unsigned int i=0; i<touched_list.size(); i++){
		if(ship_list[touched_list[i]].getMode() == 1)
			ship_list[touched_list[i]].setMode(0);
	}
	touched_list.clear();
	map.setMode(0);

	float t,tmin(-1.0);
	unsigned int selected_ship = 0;

	if(dir[0]==0)dir[0]=0.00001;
	if(dir[1]==0)dir[1]=0.00001;
	if(dir[2]==0)dir[2]=0.00001;

	for(unsigned int i=0; i<ship_list.size(); i++){
		t = ship_list[i].mouseActive(button, pos, dir);
		if((tmin<0 || t<tmin) && t>0)selected_ship = i+1;
	}
	if(tmin < 0)t = map.mouseActive(button, pos, dir);
	//else map.setMode(0);

	if(selected_ship>0){
		if(ship_list[selected_ship-1].getMode() == 0){
			ship_list[selected_ship-1].setMode(1);
			touched_list.push_back(selected_ship-1);
		}
	}
	return;
}
