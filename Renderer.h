/*
 * Renderer.h
 *
 *  Created on: 2014/7/30
 *      Author: LukeWu
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "BasicObject.h"
#include "MyWindow.h"

class Renderer {
public:
	Renderer(MyWindow *w);
	void init();
	void render();
	void clear();
	void setUniform(glm::mat4 model_matrix, unsigned int texture_unif,int mode=0);
	void push(BasicObject *np);
	void useProgram(unsigned int id);
	void resize();
	void cameraScale(float dis);
	void cameraTranslate(bool parallel, float dis);
	void cameraRotate();//not complete
	void keyActive(int key);

	unsigned int createShaderProgram(const char* vert_path, const char* frag_path);
	glm::vec3 getCameraPosition(){return camera_position;}
	glm::vec3 getCameraLookAtPosition(){return camera_lookat_position;}
	glm::vec3 getCameraUp(){return camera_up;}
	GLfloat getFovy(){return fovy;}
	GLfloat getZnear(){return z_near;}
private:
	MyWindow* window;
	GLfloat fovy;
	GLfloat z_near;
	GLfloat light;
	GLfloat window_proportion;
	glm::vec3 camera_position;
	glm::vec3 camera_lookat_position;
	glm::vec3 camera_up;
	std::vector<BasicObject*>render_list;
	std::vector<unsigned int>shader_program_list;
	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
	glm::mat4 pv_matrix;
	glm::vec3 lightColor;
	glm::vec3 LightPosition_worldspace;
	unsigned int matrix_location;
	unsigned int model_matrix_location;
	unsigned int view_matrix_location;
	unsigned int light_location;
	unsigned int light_color_location;
	unsigned int light_position_location;
	unsigned int texture_unif_location;

};

#endif /* RENDERER_H_ */
