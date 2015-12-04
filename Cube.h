#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"

class Cube : public Drawable
{

public:

	float size;

	Cube(float);
	virtual ~Cube(void);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	void spin(float);
	void left(float);
	void right(float);
	void up(float);
	void down(float);
	void in(float);
	void out(float);
	void reset();
	void scaleUp();
	void scaleDown();
	void orbit(float);
	void print();

};

#endif

