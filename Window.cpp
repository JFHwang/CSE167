#include <iostream>
#include "GLee.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

//#include <GL/freeglut.h>
#include "Window.h"
#include "sphere.h"
#include "OBJObject.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Texture.h"
#include "Shader.h"



int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
bool shading = true;
Shader * shader;

void Window::initialize(void)
{
	//Initialize skybox textures
	Globals::skybox = *new Skybox();
	Globals::skybox.top = new Texture("skybox_top.ppm");
	Globals::skybox.base = new Texture("skybox_base.ppm");
	Globals::skybox.front = new Texture("skybox_front.ppm");
	Globals::skybox.back = new Texture("skybox_back.ppm");
	Globals::skybox.right = new Texture("skybox_right.ppm");
	Globals::skybox.left = new Texture("skybox_left.ppm");

	Globals::bezier.flag = new Texture("Ucsd-logo.ppm");
	Globals::bezier2.flag = new Texture("Ucsd-logo.ppm");

    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.0002;

	//Globals::camera.set(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	
	//Patch 1
	Vector3 a = Vector3(-.5, -.25, .3);		Vector3 b = Vector3(-.5, 0, .1);	Vector3 c = Vector3(-.5, .25, .3);	Vector3 d = Vector3(-.5, .5, .2);
	Vector3 e = Vector3(-.25, -.25, .4);	Vector3 f = Vector3(-.25, 0, .2);	Vector3 g = Vector3(-.25, .25, .2);	Vector3 h = Vector3(-.25, .5, .4);
	Vector3 i = Vector3(0, -.25, .5);		Vector3 j = Vector3(0, 0, .4);		Vector3 k = Vector3(0, .25, .1);	Vector3 l = Vector3(0, .5, .4);
	Vector3 m = Vector3(.25, -.25, .2);		Vector3 n = Vector3(.25, 0, .2);	Vector3 o = Vector3(.25, .25, .5);	Vector3 p = Vector3(.25, .5, .4);
	
	//Patch 2
	Vector3 q = Vector3(.5, -.25, 2 * m[2] - i[2]);		Vector3 r = Vector3(.5, 0, 2*n[2] - j[2]);		Vector3 s = Vector3(.5, .25, 2*o[2] - k[2]);	Vector3 t = Vector3(.5, .5, 2*p[2] - l[2]);
	Vector3 u = Vector3(.75, -.25, .3);		Vector3 v = Vector3(.75, 0, .1);	Vector3 w = Vector3(.75, .25, .7);	Vector3 x = Vector3(.75, .5, .2);
	Vector3 y = Vector3(1, -.25, .8);		Vector3 z = Vector3(1, 0, .9);		Vector3 aa = Vector3(1, .25, .3);	Vector3 bb = Vector3(1, .5, .4);
	
	Globals::bezier.setCurve(0, a, b, c, d);
	Globals::bezier.setCurve(1, e, f, g, h);
	Globals::bezier.setCurve(2, i, j, k, l);
	Globals::bezier.setCurve(3, m, n, o, p);

	Globals::bezier2.setCurve(0, m, n, o, p);
	Globals::bezier2.setCurve(1, q, r, s, t);
	Globals::bezier2.setCurve(2, u, v, w, x);
	Globals::bezier2.setCurve(3, y, z, aa, bb);
	
	
	shader = new Shader("shader.vert", "shader.frag", true);
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
   
    //Call the display routine to draw the sphere
    displayCallback();
}


//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
   
	glViewport(0, 0, w, h);                                          //Set new viewport size
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); //Set perspective projection viewing frustum

}

float t = 0;
//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{

	//rasterizeVertex
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Set the OpenGL matrix mode to ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());

	glPushMatrix();
	
	Globals::light.bind(0);

	Globals::bezier.update(t);
	Globals::bezier2.update2(t, &Globals::bezier);
	GLint loc = glGetUniformLocation(shader->getPid(), "cameraPosition");	
	if(loc != -1)
		glUniform3f(loc, Globals::camera.e[0], Globals::camera.e[1], Globals::camera.e[2]);

	shader->unbind();
	Globals::skybox.draw();
	if (shading == true) {
		shader->bind();
	}
	Globals::bezier.drawPatches();
	Globals::bezier2.drawPatches();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	t += .1;
}


//TODO: Keyboard callbacks!
void Window::processNormalKeys(unsigned char key, int x, int y) {
	//The d key is pressed
	if (key == 100) {
		Matrix4 rotate;
		rotate.identity();
		rotate = rotate.makeRotateY(-.05);

		//Rotate camera right
		Globals::camera.set(rotate * Globals::camera.e, Globals::camera.d, Globals::camera.up);
	}

	//The a key is pressed
	if (key == 97) {
		Matrix4 rotate;
		rotate.identity();
		rotate = rotate.makeRotateY(.05);

		//Rotate camera left
		Globals::camera.set(rotate * Globals::camera.e, Globals::camera.d, Globals::camera.up);
	}

	//The w key is pressed
	if (key == 119) {
		Matrix4 rotate;
		rotate.identity();
		rotate = rotate.makeRotateX(-.05);

		//Rotate camera left
		Globals::camera.set(rotate * Globals::camera.e, Globals::camera.d, Globals::camera.up);
	}

	//The letter 's' is pressed, zoom in
	if (key == 115) {
		Matrix4 rotate;
		rotate.identity();
		rotate = rotate.makeRotateX(.05);

		//Rotate camera left
		Globals::camera.set(rotate * Globals::camera.e, Globals::camera.d, Globals::camera.up);
	}

	//If the letter t is pressed, turn off animation
	if (key == 116) {
		shading = !shading;
	}
}

