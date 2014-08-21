/*
 * MyShader.h
 *
 *  Created on: 2014/7/29
 *      Author: LukeWu
 */

#include<iostream>
#include<fstream>
#include<streambuf>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#ifndef MYSHADER_H_
#define MYSHADER_H_

class MyShader {
public:
	static GLuint CreateShaderFromFile(const char *File,GLenum shaderType);
};

#endif /* MYSHADER_H_ */
