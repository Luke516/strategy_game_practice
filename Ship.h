/*
 * Ship.h
 *
 *  Created on: 2014/8/6
 *      Author: LukeWu
 */

#ifndef SHIP_H_
#define SHIP_H_
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"

class Ship {
public:
	Ship(float xx=0, float yy=0, float zz=0);
	void render(Renderer* renderer);
	void update();
	void keyActive(char c);
	bool mouseActive(int button, glm::vec3 pos, glm::vec3 dir);
private:
	float x,y,z;
	int mode;// 0->none 1->touched 2->selected
	std::vector<float> obj_vertex;
	std::vector<float> obj_uv;
	std::vector<float> obj_normal;
	glm::vec3 aabb_bottom_left, aabb_top_right;
	glm::mat4 model_matrix;
	GLuint vbo_vertex, vbo_uv, vbo_normal;
	unsigned int texture_id, texture_unif;
};

#endif /* SHIP_H_ */
