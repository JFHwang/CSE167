#ifndef CSE167_Cube1_h
#define CSE167_Cube1_h

#include "Drawable.h"

class Cube1 : public Drawable
{

public:

	float size;

	Cube1(float);
	virtual ~Cube1(void);

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

