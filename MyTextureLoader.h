/*
 * MyTextureLoader.h
 *
 *  Created on: 2014/7/29
 *      Author: LukeWu
 */

#ifndef MYTEXTURELOADER_H_
#define MYTEXTURELOADER_H_

#include <vector>
#include <string>
#include <windows.h>
#include <wingdi.h>
#include <map>

class MyTextureLoader {
public:
	MyTextureLoader();
	~MyTextureLoader();
	unsigned int LoadTexture(const char* path);
	bool path_exist(std::string key);
private:
	unsigned int count;
	std::map<std::string,unsigned int> path_map;
	std::vector<unsigned int> id_list;
};

#endif /* MYTEXTURELOADER_H_ */
