/*
 * Renderer.cpp
 *
 *  Created on: 2014/7/30
 *      Author: LukeWu
 */

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <cstdio>
#include "Renderer.h"
#include "MyShader.h"

Renderer::Renderer(MyWindow* w):
		fovy(45.0),z_near(0.1),light(5),window_proportion(4.0f / 3.0f),
		camera_position(12,12,-24),camera_lookat_position(0,0,0),camera_up(0,1,0),
		projection_matrix(glm::perspective(fovy, window_proportion, z_near, 100.0f)),
		view_matrix (glm::lookAt(camera_position,camera_lookat_position,camera_up)),
		lightColor(255,0,0),LightPosition_worldspace(2,2,0)
{
	pv_matrix = projection_matrix*view_matrix;
	window = w;
}

void Renderer::init() {
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	createShaderProgram("VertexShader.vert", "FragmentShader.frag");
	matrix_location = glGetUniformLocation(shader_program_list[0], "MVP");
	model_matrix_location = glGetUniformLocation(shader_program_list[0], "M");
	view_matrix_location = glGetUniformLocation(shader_program_list[0], "V");
	light_location = glGetUniformLocation(shader_program_list[0],"light");
	light_color_location = glGetUniformLocation(shader_program_list[0],"lightColor");
	light_position_location = glGetUniformLocation(shader_program_list[0],"LightPosition_worldspace");
	texture_unif_location = glGetUniformLocation(shader_program_list[0],"myTextureSampler");
}

unsigned int Renderer::createShaderProgram(const char* vert_path,const char* frag_path) {
	printf("vert_path:%s\nfrag_path:%s\n",vert_path, frag_path);
	GLuint vertex_shader = MyShader::CreateShaderFromFile( vert_path, GL_VERTEX_SHADER);
	GLuint fragment_shader = MyShader::CreateShaderFromFile( frag_path, GL_FRAGMENT_SHADER);

	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	shader_program_list.push_back(shader_program);

	return shader_program_list.size()-1;
}

void Renderer::useProgram(unsigned int id) {
	glUseProgram(shader_program_list[id]);
}

void Renderer::render(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(unsigned int i=0; i<render_list.size(); i++){
		render_list[i] -> render(this);
	}
	glfwPollEvents();
	window -> swapBuffer();
	return;
}

void Renderer::setUniform(glm::mat4 model_matrix, unsigned int texture_unif,int mode){
	if(mode == 0)light = 5;
	else if(mode ==1)light = 10;
	else if(mode ==2)light = 20;

	glActiveTexture(GL_TEXTURE0 + texture_unif);
	glUniform1i(texture_unif_location, texture_unif);

	glm::mat4 MVP = pv_matrix * model_matrix;

	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, &model_matrix[0][0]);
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, &view_matrix[0][0]);
	glUniform3fv(light_color_location, 1, &lightColor[0]);
	glUniform3fv(light_position_location, 1, &LightPosition_worldspace[0]);
	glUniform1f(light_location, light);
}

void Renderer::push(BasicObject *np){
	render_list.push_back(np);
}

void Renderer::resize(){
	int w = window->getWindowWidth();
	int h = window->getWindowHeight();
	printf("w=%d h=%d\n",w,h);
	glViewport(0,0,w,h);
	window_proportion = (float)w/h;
	projection_matrix = glm::mat4(glm::perspective(fovy, window_proportion, z_near, 100.0f));
	pv_matrix = projection_matrix*view_matrix;
}
