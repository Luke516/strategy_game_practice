/*
 * HexMap.h
 *
 *  Created on: 2014/8/22
 *      Author: LukeWu
 */

#ifndef HEXMAP_H_
#define HEXMAP_H_
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "HexMapUnit.h"

class Renderer;

class HexMap {
public:
	HexMap(int w=12, int h=12, float len=4.0f);
	void update();
	void render(Renderer *renderer);
	void keyActive(int key, int action);
	float mouseActive(int button, glm::vec3 pos, glm::vec3 dir);
	void setMode(int next_mode);
private:
	int selected;
	int touched;
	int width;
	int height;
	float unit_len;
	std::vector<HexMapUnit> map_unit_list;
};

#endif /* HEXMAP_H_ */
