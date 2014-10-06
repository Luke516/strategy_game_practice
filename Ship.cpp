/*
 * Ship.cpp
 *
 *  Created on: 2014/8/6
 *      Author: LukeWu
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Ship.h"
#include "GlobalLoaders.h"

Ship::Ship(float map_x, float map_y, float map_unit_len):
		coordinate(map_x,map_y),mode(0),texture_unif(0),
		model_matrix(glm::mat4(1.0f)),vbo_vertex(0),vbo_uv(0),vbo_normal(0),
		ap_per_turn(5),ap(0)
{
	x = map_x * map_unit_len * 1.5;
	z = (map_y - map_x/2) * map_unit_len * 1.73205;
	y = 2.0f;

	MyObjLoader::LoadObjFromFileWithAABB("ship00.obj", &obj_vertex, &obj_uv, &obj_normal,
			&aabb_bottom_left, &aabb_top_right);
	glGenBuffers(1, &vbo_vertex);
	glGenBuffers(1, &vbo_uv);
	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
	glBufferData(GL_ARRAY_BUFFER, obj_vertex.size() * sizeof(float),&obj_vertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, obj_normal.size() * sizeof(float),&obj_normal[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glBufferData(GL_ARRAY_BUFFER, obj_uv.size() * sizeof(float), &obj_uv[0],GL_STATIC_DRAW);

	texture_id = tex_loader.LoadTexture("2.bmp");

	if (x || y || z) {
		glm::vec3 translate_vector(x, y, z);
		model_matrix = glm::translate(model_matrix, translate_vector);
		glm::vec4 bl(aabb_bottom_left,1.0);
		glm::vec4 tr(aabb_top_right,1.0);

		bl = model_matrix * bl;
		tr = model_matrix * tr;
		aabb_bottom_left_model = glm::vec3(bl[0],bl[1],bl[2]);
		aabb_top_right_model = glm::vec3(tr[0],tr[1],tr[2]);
	}
}

void Ship::render(Renderer* renderer){
	renderer->useProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindTexture(GL_TEXTURE_2D,texture_id);
	renderer->setUniform(model_matrix, texture_unif ,mode);
	glDrawArrays(GL_TRIANGLES, 0, obj_vertex.size());
}

void Ship::update(){
	/*z += 0.1;
	glm::vec3 translate_vector(0,0,0.1);
	model_matrix = glm::translate(model_matrix, translate_vector);*/
	if(order_list.size() > 0){
		if(order_list.back() -> active(this)){
			printf("execute order!!!\n");
			order_list.pop_back();
		}
		else printf("ap not enough!!!\n");
	}
	return;
}

void Ship::addOrder(Order *order){
	order_list.push_back(order);
}

void Ship::move(float map_x,float map_y){
	if(ap==0)return;
	ap--;
	float x_offset = x;
	float y_offset = z;
	coordinate = HexCoordinate(map_x,map_y);
	x = map_x * 4.0 * 1.5;
	z = (map_y - map_x / 2) * 4.0 * 1.73205;

	glm::vec3 translate_vector(x - x_offset, 0, z - y_offset);
	model_matrix = glm::translate(model_matrix, translate_vector);
	glm::vec4 bl(aabb_bottom_left, 1.0);
	glm::vec4 tr(aabb_top_right, 1.0);

	bl = model_matrix * bl;
	tr = model_matrix * tr;
	aabb_bottom_left_model = glm::vec3(bl[0], bl[1], bl[2]);
	aabb_top_right_model = glm::vec3(tr[0], tr[1], tr[2]);
}

float Ship::mouseActive(int button, glm::vec3 pos, glm::vec3 dir){
	float t;
	float tx1 = (aabb_bottom_left_model.x - pos.x)/dir.x;
	float tx2 = (aabb_top_right_model.x - pos.x)/dir.x;
	float ty1 = (aabb_bottom_left_model.y - pos.y)/dir.y;
	float ty2 = (aabb_top_right_model.y - pos.y)/dir.y;
	float tz1 = (aabb_bottom_left_model.z - pos.z)/dir.z;
	float tz2 = (aabb_top_right_model.z - pos.z)/dir.z;
	float tmin = glm::max(glm::max(glm::min(tx1, tx2), glm::min(ty1, ty2)), glm::min(tz1, tz2));
	float tmax = glm::min(glm::min(glm::max(tx1, tx2), glm::max(ty1, ty2)), glm::max(tz1, tz2));
	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
	    t = tmax;
	    return -1;
	}
	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
	    t = tmax;
	    return -1;
	}

	t = tmin;
	return t;
}

void Ship::setMode(int button){
	mode = button;
}

void Ship::keyActive(int key, int action){

}
