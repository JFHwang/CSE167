#ifndef CSE167_Bezier_h
#define CSE167_Bezier_h

#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Texture.h"

class Bezier {
public:
	std::vector<Matrix4> pointsV;
	Texture * flag;
	
	Bezier();

	void setCurve(int, Vector3, Vector3, Vector3, Vector3);
	void update(float);
	void update2(float, Bezier*);

	virtual void drawPatches();
	Vector4 Bez(float, Matrix4);
	Vector4 Bez(float, Vector4, Vector4, Vector4, Vector4);

protected:
	float t;
	float c0;
	float c1;
	float c2;
	float c3;
	Vector4 Ct;
};

#endif