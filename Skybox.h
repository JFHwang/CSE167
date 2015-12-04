#ifndef CSE167_Skybox_h
#define CSE167_Skybox_h

#include "Texture.h"
#include "Matrix4.h"

class Skybox {
public:
	Texture * top;
	Texture * front;
	Texture * back;
	Texture * base;
	Texture * right;
	Texture * left;

	int width;
	int height;
	int length;

	Matrix4 toWorld;

	Skybox();

	virtual void draw();
};

#endif