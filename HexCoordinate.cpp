/*
 * HexCoordinate.cpp
 *
 *  Created on: 2014/9/12
 *      Author: LukeWu
 */

#include <cstdlib>
#include "HexCoordinate.h"

HexCoordinate::HexCoordinate(int xx,int yy) :x(xx),y(yy)
{
}


int HexCoordinate::getDis(HexCoordinate target){
	int x2 = target.getX();
	int y2 = target.getY();
	int z = -(x+y);
	int z2 = -(x2+y2);
	return (abs(x - x2) + abs(y - y2) + abs(z - z2)) / 2;
}

bool HexCoordinate::operator == (const HexCoordinate &a)const{
	if(a.getX()==x && a.getY()==y)return true;
	return false;
}

HexCoordinate HexCoordinate::operator +(HexCoordinate a){
	return HexCoordinate(x+a.getX(), y+a.getY());
}
