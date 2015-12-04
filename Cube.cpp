#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Vector3.h"
#include "Window.h"
#include "math.h"
#include "Globals.h"

Cube::Cube(float size) : Drawable()
{
    this->size = size;
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}


void Cube::draw(DrawData& data)
{
	float halfSize = size / 2.0;

	//Apply the material properties
	//From here forward anything drawn will be drawn with this material
	material.apply();

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	//Make cube!
	//Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
	//These are special calls that 'freeze' many internal states of OpenGL.
	//Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
	//As a good habit, only call glBegin just before you need to draw, and call end just after you finish
	glBegin(GL_QUADS);

	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();

	//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
	//glutSolidCube(size);

	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();
}


void Cube::update(UpdateData& data)
{
    //
}


void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians);
    
    toWorld = toWorld * rotation;
}

void Cube::left(float dist) {
	Matrix4 translation;
	translation.makeTranslate(-dist, 0, 0);

	toWorld = translation * toWorld; 
}

void Cube::right(float dist) {
	Matrix4 translation;
	translation.makeTranslate(dist, 0, 0);

	toWorld = translation * toWorld;
}

void Cube::up(float dist) {
	Matrix4 translation;
	translation.makeTranslate(0, dist, 0);

	toWorld = translation * toWorld;
}

void Cube::down(float dist) {
	Matrix4 translation;
	translation.makeTranslate(0, -dist, 0);

	toWorld = translation*toWorld;
}

void Cube::in(float dist) {
	Matrix4 translation;
	translation.makeTranslate(0, 0, -dist);

	toWorld = translation*toWorld;
}

void Cube::out(float dist) {
	Matrix4 translation;
	translation.makeTranslate(0, 0, dist);

	toWorld = translation*toWorld;
}

void Cube::reset() {
	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	toWorld.identity();
}

void Cube::scaleUp() {
	Matrix4 scale;
	scale.makeScale(1.1);

	toWorld = toWorld * scale;
}

void Cube::scaleDown() {
	Matrix4 scale;
	scale.makeScale(.9);

	toWorld = toWorld * scale;
}

void Cube::orbit(float angle) {	
	Matrix4 rotate;
	rotate.makeRotateZ(angle);
	
	toWorld = rotate * toWorld;
}

void Cube::print() {
	//Prints out the current location relative to the origin
	Vector3 loca;
	loca.set(toWorld.get(3,0), toWorld.get(3,1), toWorld.get(3,2));
	loca.print("");
}