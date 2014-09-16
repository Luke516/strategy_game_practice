/*
 * Order.cpp
 *
 *  Created on: 2014/9/11
 *      Author: LukeWu
 */

#include "Order.h"
#include "PathFinder.h"

Order::~Order(){

}

MoveOrder::MoveOrder(PathNode &node){
	x = node.getCoordinate().getX();
	y = node.getCoordinate().getY();
}

void MoveOrder::active(Ship *ship){
	//ship -> move(x,y);
}

void AttackOrder::active(Ship *ship){

}

void PatrolOrder::active(Ship *ship){

}
