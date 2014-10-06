/*
 * TurnCounter.cpp
 *
 *  Created on: 2014/9/6
 *      Author: LukeWu
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "TurnCounter.h"
#include "GlobalLoaders.h"

TurnCounter::TurnCounter(std::vector<Ship> &list):
	avilible(true),mode(1),ship_list(list),texture_unif(0)
{
	obj_loader.LoadObjFromFile("hex01.obj",&obj_vertex,&obj_uv,&obj_normal);
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

	texture_id = tex_loader.LoadTexture("turn_counter_tex.bmp");
	//model_matrix = glm::rotate(model_matrix, 120.0f, glm::vec3(0,0,1));
	model_matrix = glm::scale(model_matrix , glm::vec3(1,1,1));
	model_matrix = glm::translate(model_matrix, glm::vec3(1.1,-0.75,0));
}

void TurnCounter::render(Renderer* renderer){
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
	renderer->setUniform(model_matrix, texture_unif,mode,false);
	glDrawArrays(GL_TRIANGLES, 0, obj_vertex.size());
}


float TurnCounter::mouseActive(int button, int x_pos, int y_pos){

	return -1.0;
}

void TurnCounter::keyActive(int key){
	if(key == 'N'){
		for(unsigned int i=0; i<ship_list.size(); i++){
			ship_list[i].addAP();
		}
	}
	return;
}
