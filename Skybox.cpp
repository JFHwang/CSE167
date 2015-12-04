#include "Skybox.h"
#include <stdio.h>
#include "Globals.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

Skybox::Skybox() {
	width = 500;
	height = 500;
	length = 500;
}

void Skybox::draw() {
	glDisable(GL_LIGHTING);

	//Bind texture
	glColor3f(1.0, 1.0, 1.0);
	top->bind();

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0f);
	glVertex3f(-width, height, length);	// Bottom Right Of The Quad (Top)
	glTexCoord2d(1.0f, 0.0f);	
	glVertex3f(width, height, length);	// Top Right Of The Quad (Top)
	glTexCoord2d(1.0f, 1.0f);	
	glVertex3f(width, height, -length);	// Top Left Of The Quad (Top)
	glTexCoord2d(0.0, 1.0f);	
	glVertex3f(-width, height, -length);	// Bottom Left Of The Quad (Top)
	glEnd();
	top->unbind();

	glColor3f(1.0, 1.0, 1.0);
	base->bind();
	glBegin(GL_QUADS);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(width, -height, -length);	// Top Right Of The Quad (Top)
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(width, -height, length);	// Top Left Of The Quad (Top)
	glTexCoord2d(0.0, 1.0f);
	glVertex3f(-width, -height, length);	// Bottom Left Of The Quad (Top)
	glTexCoord2d(0.0, 0.0f);
	glVertex3f(-width, -height, -length);	// Bottom Right Of The Quad (Top)
	glEnd();
	base->unbind();

	glColor3f(1.0, 1.0, 1.0);
	right->bind();
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);	
	glVertex3f(width, height, -length);	// Top Right Of The Quad (Right)
	glTexCoord2d(1.0f, 0.0f);	
	glVertex3f(width, height, length);	// Top Left Of The Quad (Right)
	glTexCoord2d(1.0f, 1.0f);	
	glVertex3f(width, -height, length);	// Bottom Left Of The Quad (Right)
	glTexCoord2d(0.0f, 1.0f);	
	glVertex3f(width, -height, -length);	// Bottom Right Of The Quad (Right)
	glEnd();
	right->unbind();

	glColor3f(1.0, 1.0, 1.0);
	left->bind();
	glBegin(GL_QUADS);
	glTexCoord2d(1.0f, 0.0f);	
	glVertex3f(-width, height, -length);	// Top Right Of The Quad (Left)
	glTexCoord2d(1.0f, 1.0f);	
	glVertex3f(-width, -height, -length);	// Top Left Of The Quad (Left)
	glTexCoord2d(0.0f, 1.0f);	
	glVertex3f(-width, -height, length);	// Bottom Left Of The Quad (Left)
	glTexCoord2d(0.0f, 0.0f);	
	glVertex3f(-width, height, length);	// Bottom Right Of The Quad (Left)
	glEnd();
	left->unbind();

	glColor3f(1.0, 1.0, 1.0);
	back->bind();
	glBegin(GL_QUADS);
	glTexCoord2d(1.0f, 1.0f);	
	glVertex3f(-width, -height, length);	// Bottom Left Of The Quad (Back)
	glTexCoord2d(0.0f, 1.0f);	
	glVertex3f(width, -height, length);	// Bottom Right Of The Quad (Back)
	glTexCoord2d(0.0f, 0.0f);	
	glVertex3f(width, height, length);	// Top Right Of The Quad (Back)
	glTexCoord2d(1.0f, 0.0f);	
	glVertex3f(-width, height, length);	// Top Left Of The Quad (Back)
	glEnd();
	back->unbind();

	glColor3f(1.0, 1.0, 1.0);
	front->bind();
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);	
	glVertex3f(-width, height, -length);	// Top Right Of The Quad (Front)
	glTexCoord2d(1.0f, 0.0f);	
	glVertex3f(width, height, -length);	// Top Left Of The Quad (Front)
	glTexCoord2d(1.0f, 1.0f);	
	glVertex3f(width, -height, -length);	// Bottom Left Of The Quad (Front)
	glTexCoord2d(0.0f, 1.0f);	
	glVertex3f(-width, -height, -length);	// Bottom Right Of The Quad (Front)
	glEnd();
	front->unbind();

	glEnable(GL_LIGHTING);
}

