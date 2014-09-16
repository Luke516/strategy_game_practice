/*
 * PathFinder.h
 *
 *  Created on: 2014/9/13
 *      Author: LukeWu
 */

#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <vector>
#include "HexCoordinate.h"
#include "HexMap.h"
#include "Ship.h"

class PathNode{
public:
	PathNode(HexCoordinate coord = HexCoordinate(0,0), int dis=0, int cost=0, int p=0);
	const int getScore()const {return distance_to_target + current_cost;}
	const int getCost()const {return current_cost;}
	const int getParent()const {return parent;}
	const HexCoordinate getCoordinate()const {return coordinate;}
	bool operator == (const PathNode &a)const;
private:
	int distance_to_target;
	int current_cost;
	HexCoordinate coordinate;
	int parent;
};

class PathFinder {
public:
	PathFinder(HexMap *mapp);
	void findPath(HexCoordinate start,HexCoordinate end,Ship &ship);
	PathNode findNode(HexCoordinate coordinate,int cost,int pa = 0);
private:
	HexMap *map;
	HexCoordinate target;
};

#endif /* PATHFINDER_H_ */
