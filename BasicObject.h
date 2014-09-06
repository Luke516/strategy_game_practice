/*
 * BasicObject.h
 *
 *  Created on: 2014/7/30
 *      Author: LukeWu
 */

#ifndef BASICOBJECT_H_
#define BASICOBJECT_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer;

class BasicObject {
public:
	BasicObject(){}
	virtual ~BasicObject(){}
	virtual void render(Renderer *renderer)=0;
	virtual void update()=0;
	virtual void keyActive(int key, int action)=0;
	virtual void mouseActive(int button, glm::vec3 pos, glm::vec3 dir)=0;
};

#endif /* BASICOBJECT_H_ */
