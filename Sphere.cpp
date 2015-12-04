#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;

	float xCenter = (maxX + minX) / 2;
	float yCenter = (maxY + minY) / 2;
	float zCenter = (maxZ + minZ) / 2;
	toWorld.set(3, 0, -xCenter);
	toWorld.set(3, 1, -yCenter);
	toWorld.set(3, 2, -zCenter);
}

void Sphere::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
	maxX = radius;
	maxY = radius;
	maxZ = radius;
	minX = -radius;
	minY = -radius;
	minZ = -radius;

	
    glutSolidSphere(radius, slices, stacks);

    glPopMatrix();
}


void Sphere::update(UpdateData& data)
{
    //
}
void Sphere::scaleUp() {
	Matrix4 scale;
	scale.makeScale(1.1);

	toWorld = toWorld * scale;
}


void Sphere::scaleDown() {
	Matrix4 scale;
	scale.makeScale(.9);

	toWorld = toWorld * scale;
}

void Sphere::translate(Vector3 dir) {
	Matrix4 translation;
	translation.makeTranslate(dir[0], dir[1], dir[2]);

	toWorld = translation * toWorld;
}

void Sphere::rotate(Vector3 axis, float angle) {
	Matrix4 rotate;
	rotate.makeRotateArbitrary(axis, angle);

	toWorld = rotate * toWorld;
}