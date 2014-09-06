/*
 * HexMap.cpp
 *
 *  Created on: 2014/8/22
 *      Author: LukeWu
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "HexMap.h"

HexMap::HexMap(int w, int h, float len):selected(-1),touched(-1),
		width(w),height(h),unit_len(len)
{
	int x,y,offset;
	for(int i=0;i<width;i++){
		offset = i/2;
		for(int j=0;j<height;j++){
			//x = i - (w+1)/2;
			//y = j + ((h-1)/2) - (h-j-1)/2;
			x = i;
			y = j + offset;
			map_unit_list.push_back(HexMapUnit(x,y,unit_len));
			//map_unit_list.push_back(HexMapUnit(i,j,unit_len));
			//map_unit_list.push_back(HexMapUnit(i-(w+1)/2,j-(h+1)/2,unit_len));
		}
	}
}

void HexMap::render(Renderer *renderer){
	for(unsigned int i=0;i<width*height;i++){
		map_unit_list[i].render(renderer);
	}
}

float HexMap::mouseActive(int button, glm::vec3 pos, glm::vec3 dir){
	float t = (0 - pos.y)/dir.y;
	float x = pos.x + dir.x * t;
	float z = pos.z + dir.z * t;
	int touched_x;
	int touched_y;

	float i = x/(unit_len/2);
	float h = unit_len*1.73205/2;
	float j = z/h;
	int ii(i);
	int jj(j);

	if (ii % 3 != 1) {
		touched_x = ii / 3 + (ii % 3) / 2;
		jj += touched_x;
		touched_y = jj / 2 + jj % 2;

		int no_x =  touched_x ;
		int no_y= 	touched_y - no_x/2;
		unsigned int no = no_x * height + no_y;

		if(no_x < 0 || no_x >= width)return -1;
		else if(no_y<0 || no_y>=height)return -1;
		else{
			touched = no;
			map_unit_list[no].setMode(1);
		}

		if(ii>-10 && ii<10 &&jj>-10 && jj<10){
			printf("t=%f x=%f z=%f\n",t,x,z);
			printf("i=%f ii=%d\nj=%f jj=%d\n",i,ii,j,jj);
			printf("touched_x=%d touched_y=%d\n",touched_x,touched_y);
			printf("no_x=%d no_y=%d\n",no_x,no_y);
		}

	}
	return t;
}

void HexMap::setMode(int next_mode){
	if(next_mode == -1){
		if(selected >= 0)map_unit_list[selected].setMode(0);
	}
	else if(next_mode == 0){
		if(touched >= 0 && touched != selected)map_unit_list[touched].setMode(0);
	}
	else if(next_mode == 1){

	}
	else if(next_mode == 2){
		selected = touched;
		if(touched >= 0)map_unit_list[touched].setMode(2);
	}
}
