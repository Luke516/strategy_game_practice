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
public:
	virtual ~Order();
	virtual void active(Ship *ship) = 0;
};

class MoveOrder:public Order{
public:
	MoveOrder(PathNode &node);
	virtual void active(Ship *ship);
private:
	int x,y;
};

class AttackOrder:public Order{
public:
	virtual void active(Ship *ship);
};

class PatrolOrder:public Order{
public:
	virtual void active(Ship *ship);
};

#endif /* ORDER_H_ */
