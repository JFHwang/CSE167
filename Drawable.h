#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>
#include "Vector3.h"


class Drawable
{
    
public:
    
    Matrix4 toWorld;
    Material material;
	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;
    
    Drawable(void);
    ~Drawable(void);
    
	int arraySize();
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);

	std::vector<Vector3>* all;
    
};

#endif
