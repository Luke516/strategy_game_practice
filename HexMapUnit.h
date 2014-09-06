/*
 * HexMapUnit.h
 *
 *  Created on: 2014/8/22
 *      Author: LukeWu
 */

#ifndef HEXMAPUNIT_H_
#define HEXMAPUNIT_H_
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"

class HexMapUnit {
public:
	HexMapUnit(int xx, int yy, float lenn);
	void render(Renderer *renderer);
	void setMode(int next_mode);
private:
	int mode;
	int x;
	int y;
	float len;
	std::vector<float> obj_vertex;
	std::vector<float> obj_uv;
	std::vector<float> obj_normal;
	glm::mat4 model_matrix;
	unsigned int vbo_vertex, vbo_uv, vbo_normal;
	unsigned int texture_id, texture_unif;
};

#endif /* HEXMAPUNIT_H_ */
