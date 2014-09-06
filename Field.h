/*
 * Field.h
 *
 *  Created on: 2014/7/30
 *      Author: LukeWu
 */

#ifndef FIELD_H_
#define FIELD_H_
#include <vector>
#include "Ship.h"
#include "HexMap.h"
#include "Renderer.h"
#include "BasicObject.h"

class Field:public BasicObject {
public:
	Field();
	virtual ~Field();
	virtual void render(Renderer *renderer);
	virtual void update();
	virtual void keyActive(int key, int action);
	virtual void mouseActive(int button, glm::vec3 pos, glm::vec3 dir);
private:
	HexMap map;
	std::vector<Ship> ship_list;
	std::vector<unsigned int> touched_list;
	std::vector<unsigned int> selected_list;
};

#endif /* FIELD_H_ */
