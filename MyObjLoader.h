/*
 * ObjLoader.h
 *
 *  Created on: 2014/7/19
 *      Author: LukeWu
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MyObjLoader {
public:
	MyObjLoader();
	static bool LoadObjFromFileWithAABB(const char*,std::vector<float>*,std::vector<float>*,std::vector<float>*,
			glm::vec3*, glm::vec3*);
	static bool LoadObjFromFileVertexOnly(const char*,std::vector<float>*);
	static bool LoadObjFromFileVertexAndNormal(const char*,std::vector<float>*,std::vector<float>*);
};

#endif /* OBJLOADER_H_ */
