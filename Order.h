/*
 * Order.h
 *
 *  Created on: 2014/9/11
 *      Author: LukeWu
 */

#ifndef ORDER_H_
#define ORDER_H_

class Ship;
class PathNode;

class Order {
private:
	int ap_cost;
public:
	virtual ~Order();
	virtual void setApCost(int cost){ap_cost = cost;}
	virtual int getApCost(){return ap_cost;}
	virtual bool active(Ship *ship) = 0;
};

class MoveOrder:public Order{
public:
	MoveOrder(PathNode &node);
	virtual bool active(Ship *ship);
private:
	int x,y;
};

class AttackOrder:public Order{
public:
	virtual bool active(Ship *ship);
};

class PatrolOrder:public Order{
public:
	virtual bool active(Ship *ship);
};

#endif /* ORDER_H_ */
