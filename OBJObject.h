#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Drawable.h"
#include "Matrix4.h"

struct Face
{
    int vertexIndices[3];
    int normalIndices[3];
    //Add more members as necessary
};

class OBJObject : public Drawable
{
    
protected:
    
    //Storage vectors
    /*
	std::vector<Vector3*>* vertices;
	std::vector<Vector3*>* colors;
    std::vector<Vector3*>* normals;
    */

	std::vector<Face>* faces;
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void parse(std::string&);
	Matrix4 startMatrix;
    
public:
	std::vector<Vector3>* vertices;
	std::vector<Vector3>* colors;
	std::vector<Vector3>* normals;

	std::vector<Vector3>* all;

    OBJObject(std::string);
    virtual ~OBJObject(void);
    
	virtual void draw(DrawData&);
    virtual void update(UpdateData&);

	int getSize();
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
	void rotate(Vector3, float);
	void translate(Vector3);
    
};

#endif
