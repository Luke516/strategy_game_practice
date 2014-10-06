/*
 * HexMapUnit.cpp
 *
 *  Created on: 2014/8/22
 *      Author: LukeWu
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "HexMapUnit.h"
#include "GlobalLoaders.h"

HexMapUnit::HexMapUnit(int xx, int yy, float lenn):mode(0),coordinate(xx,yy),len(lenn),texture_unif(0)
{
	obj_loader.LoadObjFromFile("hex00.obj",&obj_vertex,&obj_uv,&obj_normal);
	glGenBuffers(1, &vbo_vertex);
	glGenBuffers(1, &vbo_uv);
	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
	glBufferData(GL_ARRAY_BUFFER, obj_vertex.size() * sizeof(float),
			&obj_vertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, obj_normal.size() * sizeof(float),
			&obj_normal[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glBufferData(GL_ARRAY_BUFFER, obj_uv.size() * sizeof(float), &obj_uv[0],
			GL_STATIC_DRAW);

	texture_id = tex_loader.LoadTexture("hex_tex.bmp");

	//glm::vec3 translate_vector(10*x , 0.0, 10*y);
	//glm::vec3 translate_vector(x*len*1.5 , 0.0, y*1.73205*len+abs(x%2)*(1.73205*len/2));
	glm::vec3 translate_vector(xx * len * 1.5, 0.0, yy * 1.73205 * len - xx * (1.73205 * len / 2));
	model_matrix = glm::translate(model_matrix, translate_vector);

}

void HexMapUnit::render(Renderer* renderer){
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
	renderer->setUniform(model_matrix, texture_unif,mode);
	glDrawArrays(GL_TRIANGLES, 0, obj_vertex.size());
}

void HexMapUnit::setMode(int next_mode){
	if(mode == 2 && next_mode == 1)return;
	else mode = next_mode;
}
