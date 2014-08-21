/*
 * MyTextureLoader.h
 *
 *  Created on: 2014/7/29
 *      Author: LukeWu
 */

#ifndef MYTEXTURELOADER_H_
#define MYTEXTURELOADER_H_

#include <vector>
#include <windows.h>
#include <wingdi.h>

class MyTextureLoader {
public:
	MyTextureLoader();
	~MyTextureLoader();
	static unsigned int LoadTexture(const char* path);
};

#endif /* MYTEXTURELOADER_H_ */
