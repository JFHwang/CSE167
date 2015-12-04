#include "Bezier.h"
#include <math.h>

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

Bezier::Bezier() {
	//Curve 1
	pointsV.push_back(Matrix4());
	pointsV.push_back(Matrix4());
	pointsV.push_back(Matrix4());
	pointsV.push_back(Matrix4());

}

void Bezier::setCurve(int index, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) {
	if (index >= 0 && index < 4) {
		pointsV[index].set(
			p1[0], p1[1], p1[2], 0, 
			p2[0], p2[1], p2[2], 0,
			p3[0], p3[1], p3[2], 0, 
			p4[0], p4[1], p4[2], 0);
	}
	else { printf("Attemting to set out of bounds point"); }
}

void Bezier::update(float t) {
	pointsV[3].set(0, 2, .6*sin(t));
	pointsV[3].set(1, 2, .6*sin(t+.1));
	pointsV[3].set(2, 2, .6*sin(t-.3));
	pointsV[3].set(3, 2, .6*sin(t+.2));

	pointsV[2].set(0, 2, .5*sin(t + .5));
	pointsV[2].set(1, 2, .5*sin(t + .1 + .3));
	pointsV[2].set(2, 2, .5*sin(t - .3 + .3));
	pointsV[2].set(3, 2, .5*sin(t + .2 + .3));

	pointsV[1].set(0, 2, .4*sin(t + 1));
	pointsV[1].set(1, 2, .4*sin(t + .1 + .6));
	pointsV[1].set(2, 2, .4*sin(t - .3 + .6));
	pointsV[1].set(3, 2, .4*sin(t + .2 + .6));
}

void Bezier::update2(float t, Bezier * parent) {
	pointsV[3].set(0, 2, .4 * sin(t + .2 - 1.67));
	pointsV[3].set(1, 2, .4 * sin(t + .3 - 1.67));
	pointsV[3].set(2, 2, .4 * sin(t + .2 - 1.67));
	pointsV[3].set(3, 2, .4 * sin(t + .7 - 1.67));

	pointsV[2].set(0, 2, .4 * sin(t + .2 - .9));
	pointsV[2].set(1, 2, .4 * sin(t + .1 - .9));
	pointsV[2].set(2, 2, .4 * sin(t + .2 - .9));
	pointsV[2].set(3, 2, .4 * sin(t + -.3 - .9));

	pointsV[0].set(0, 2, parent->pointsV[3].get(0, 2));
	pointsV[0].set(1, 2, parent->pointsV[3].get(1, 2));
	pointsV[0].set(2, 2, parent->pointsV[3].get(2, 2));
	pointsV[0].set(3, 2, parent->pointsV[3].get(3, 2));

	pointsV[1].set(0, 2, pointsV[0].get(0, 2) * 2 - parent->pointsV[2].get(0, 2));
	pointsV[1].set(1, 2, pointsV[0].get(1, 2) * 2 - parent->pointsV[2].get(1, 2));
	pointsV[1].set(2, 2, pointsV[0].get(2, 2) * 2 - parent->pointsV[2].get(2, 2));
	pointsV[1].set(3, 2, pointsV[0].get(3, 2) * 2 - parent->pointsV[2].get(3, 2));
}

Vector4 Bezier::Bez(float t, Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3) {
	c0 = pow(1 - t, 3);
	c1 = 3 * t * pow(1 - t, 2);
	c2 = 3 * pow(t, 2) * (1 - t);
	c3 = pow(t, 3);
	Ct = Vector4(c0, c1, c2, c3);

	Matrix4 M = Matrix4(p0[0], p0[1], p0[2], 0,
		p1[0], p1[1], p1[2], 0, 
		p2[0], p2[1], p2[2], 0, 
		p3[0], p3[1], p3[2], 0);

	Vector4 result = M * Ct;

	return result;
}

Vector4 Bezier::Bez(float t, Matrix4 M) {
	c0 = pow(1 - t, 3);
	c1 = 3 * t * pow(1 - t, 2);
	c2 = 3 * pow(t, 2) * (1 - t);
	c3 = pow(t, 3);
	Ct = Vector4(c0, c1, c2, c3);

	Vector4 result = M * Ct;

	return result;
}

void Bezier::drawPatches() {
	flag->bind();
	for (float t = 0.0; t < 1; t += .01) {
		Vector4 q0 = Bez(t, pointsV[0]);
		Vector4 q1 = Bez(t, pointsV[1]);
		Vector4 q2 = Bez(t, pointsV[2]);
		Vector4 q3 = Bez(t, pointsV[3]);

		Vector4 r0 = Bez(t + .01f, pointsV[0]);
		Vector4 r1 = Bez(t + .01f, pointsV[1]);
		Vector4 r2 = Bez(t + .01f, pointsV[2]);
		Vector4 r3 = Bez(t + .01f, pointsV[3]);

		glBegin(GL_QUADS);
		for (float t2 = 0.0f; t2 < 1; t2 += .01f) {
			Vector4 u0 = Bez(t2, q0, q1, q2, q3);
			Vector4 u1 = Bez(t2 + .01f, q0, q1, q2, q3);
			Vector4 v0 = Bez(t2, r0, r1, r2, r3);
			Vector4 un = Bez(t2 + .01f, q0, q1, q2, q3);
			Vector4 vn = Bez(t2 + .01f, r0, r1, r2, r3);

			Vector3 tanu = (u1 - u0).toVector3().normalize();
			Vector3 tanv = (v0 - u0).toVector3().normalize();
			Vector3 normal = tanu.cross(tanv);
			
			glNormal3f(normal[0], normal[1], normal[2]);
			glTexCoord2d(t2, 1.0f - t);						glVertex3f(u0[0], u0[1], u0[2]);
			glTexCoord2d(t2 + .01f, 1.0f - t);				glVertex3f(un[0], un[1], un[2]);
			glTexCoord2d(t2 + .01f, 1.0f - t - .01f);		glVertex3f(vn[0], vn[1], vn[2]);
			glTexCoord2d(t2, 1.0f - t - .01f);				glVertex3f(v0[0], v0[1], v0[2]);

		}
		glEnd();
	}
	flag->unbind();
}