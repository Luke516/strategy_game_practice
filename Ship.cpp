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
#include "MyObjLoader.h"
#include "MyTextureLoader.h"

Ship::Ship(float xx, float yy,float zz):x(xx),y(yy),z(zz),mode(0),
		model_matrix(glm::mat4(1.0f)),vbo_vertex(0),vbo_uv(0),vbo_normal(0)
{
	MyObjLoader::LoadObjFromFileWithAABB("cube00.obj", &obj_vertex, &obj_uv, &obj_normal,
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

	texture_id = MyTextureLoader::LoadTexture("2.bmp");

	if (x || y || z) {
		glm::vec3 translate_vector(x, y, z);
		model_matrix = glm::translate(model_matrix, translate_vector);
		glm::vec4 bl(aabb_bottom_left,1.0);
		glm::vec4 tr(aabb_top_right,1.0);

		///glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f)*glm::lookAt(glm::vec3(0,0,20),glm::vec3(0,0,0),glm::vec3(0,1,0))

		bl = model_matrix * bl;
		tr = model_matrix * tr;
		aabb_bottom_left = glm::vec3(bl[0],bl[1],bl[2]);
		aabb_top_right = glm::vec3(tr[0],tr[1],tr[2]);
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
	renderer->setUniform(model_matrix,0,mode);
	glDrawArrays(GL_TRIANGLES, 0, obj_vertex.size());
}

bool Ship::mouseActive(int button, glm::vec3 pos, glm::vec3 dir){
	float t;
	float tx1 = (aabb_bottom_left.x - pos.x)/dir.x;
	float tx2 = (aabb_top_right.x - pos.x)/dir.x;
	float ty1 = (aabb_bottom_left.y - pos.y)/dir.y;
	float ty2 = (aabb_top_right.y - pos.y)/dir.y;
	float tz1 = (aabb_bottom_left.z - pos.z)/dir.z;
	float tz2 = (aabb_top_right.z - pos.z)/dir.z;
	float tmin = glm::max(glm::max(glm::min(tx1, tx2), glm::min(ty1, ty2)), glm::min(tz1, tz2));
	float tmax = glm::min(glm::min(glm::max(tx1, tx2), glm::max(ty1, ty2)), glm::max(tz1, tz2));
	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
	    t = tmax;
	    printf("false!\n");
	    mode = 0;
	    return false;
	}
	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
	    t = tmax;
	    printf("false!\n");
	    mode = 0;
	    return false;
	}

	t = tmin;
	mode = 1;
	printf("true!\n");
	return true;
}
