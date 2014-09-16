/*
 * PathFinder.cpp
 *
 *  Created on: 2014/9/13
 *      Author: LukeWu
 */

#include <queue>
#include <vector>
#include <algorithm>
#include "PathFinder.h"
#include "Order.h"


PathNode::PathNode(HexCoordinate coord,int dis,int cost, int p):
	distance_to_target(dis),current_cost(cost),
	coordinate(coord),parent(p)
{
}

bool PathNode::operator == (const PathNode &a)const{
	if(a.getCoordinate() == coordinate)return true;
	return false;
}


struct path_finder_compare
{
  bool operator()(const PathNode &a, const PathNode &b)
  {
      return a.getScore() > b.getScore();
  }
};

PathFinder::PathFinder(HexMap *mapp):map(mapp),target(0,0)
{
	// TODO Auto-generated constructor stub

}

void PathFinder::findPath(HexCoordinate start,HexCoordinate end,Ship &ship){
	bool find(false);
	int i,x,y,offset,current_cost;
	int map_width=map->getWidth(),map_height=map->getHeight();
	int pa,count=0;

	std::priority_queue<PathNode,std::vector<PathNode>,path_finder_compare> open;
	std::vector<PathNode> close;
	PathNode node, next_node;
	HexCoordinate cur,next[6];

	target = end;
	open.push(findNode(start,0));
	while(!find && count<500 && open.size()==0){
		node = open.top();
		open.pop();
		pa = close.size();
		cur = node.getCoordinate();
		current_cost = node.getCost();
		next[0] = cur+HexCoordinate(0 , 1);
		next[1] = cur+HexCoordinate(1 , 0);
		next[2] = cur+HexCoordinate(1 , 1);
		next[3] = cur+HexCoordinate(0 ,-1);
		next[4] = cur+HexCoordinate(-1, 0);
		next[5] = cur+HexCoordinate(-1,-1);
		for(i=0;i<6;i++){
			x = next[i].getX();
			y = next[i].getY();
			offset = x/2;
			if(x < map_width && (y-offset) < map_height )next_node = findNode(next[i],current_cost+1,pa);
			if(std::find(close.begin(),close.end(),next_node) == close.end() ) open.push(next_node);

			if(next[i] == target){
				close.push_back(next_node);
				find = true;
				break;
			}
		}
		close.push_back(node);
		count++;
	}
	if(find){
		std::vector<MoveOrder *> order_list;
		MoveOrder *np;
		int cur,next;
		cur = close.size() - 1;
		for(;;){
			node = close[cur];
			np = new MoveOrder(node);
			order_list.push_back(np);
			next = node.getParent();
			if(next == cur)break;
		}
		for(i=order_list.size()-1 ;i>=0; i--){
			ship.addOrder(order_list[i]);
		}
	}
	return;
}

PathNode PathFinder::findNode(HexCoordinate coordinate,int cost,int pa){
	int distance = target.getDis(coordinate);
	return PathNode(coordinate,distance,cost,pa);
}
