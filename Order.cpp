/*
 * Order.cpp
 *
 *  Created on: 2014/9/11
 *      Author: LukeWu
 */

#include <cstdio>
#include "Order.h"
#include "PathFinder.h"

Order::~Order(){

}

MoveOrder::MoveOrder(PathNode &node){
	setApCost(1);
	x = node.getCoordinate().getX();
	y = node.getCoordinate().getY();
}

bool MoveOrder::active(Ship *ship){
	if(ship -> getAP() < getApCost() ) return false;
	printf("move to : %d %d\n",x,y);
	ship -> move(x,y);
	return true;
}

bool AttackOrder::active(Ship *ship){
	return false;
}

bool PatrolOrder::active(Ship *ship){
	return false;
}
