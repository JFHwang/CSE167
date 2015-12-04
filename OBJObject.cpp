#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include "Globals.h"


#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)


OBJObject::OBJObject(std::string filename) : Drawable()
{
	this->faces = new std::vector<Face>();

	this->vertices = new std::vector<Vector3>();
	this->colors = new std::vector<Vector3>();
	this->normals = new std::vector<Vector3>();
	this->all = new std::vector<Vector3>();
    
    parse(filename);

	//Translating the OBJObject to the origin
	float xCenter = (maxX + minX) / 2.0;
	float yCenter = (maxY + minY) / 2.0;
	float zCenter = (maxZ + minZ) / 2.0;
	float size = 40.0 / sqrt(3) / (maxX - minX);

	Matrix4 translate;
	translate.makeTranslate(-xCenter, -yCenter, -zCenter);
	toWorld = translate * toWorld;
	Matrix4 scale;

	if (filename == "bunny.obj") { //screenWidth/objectWidth = 40/sqrt(3)/(maxX-minX)
		scale.makeScale(16.37/20.0*size);
	}
	else if (filename == "bear.obj") {
		scale.makeScale(15.25/20.0*size);
	}
	else if (filename == "dragon.obj") {
		scale.makeScale(18.44/20.0*size);
	}

	toWorld = scale * toWorld;

	startMatrix = toWorld;
	
}


OBJObject::~OBJObject()
{
	//No pointers = no deletions?
}

int OBJObject::getSize(){
	return (int)all->size();
}

void OBJObject::draw(DrawData& data)
{
	glEnable(GL_LIGHTING);
    material.apply();
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);

		
	for (int i = 0; i < (int)all->size(); i += 3) {
		//Original implementation
		//glColor3f((*all)[i][0], (*all)[i][1], (*all)[i][2]);
		glNormal3f((*all)[i+1][0], (*all)[i+1][1], (*all)[i+1][2]);
		glVertex3f((*all)[i + 2][0], (*all)[i + 2][1], (*all)[i + 2][2]);
	
	}
    glEnd();

    glPopMatrix();
}



void OBJObject::update(UpdateData& data)
{
    //
}

void OBJObject::parse(std::string& filename)
{
	int lineNum = 0;


	std::cout << "Starting parse..." << std::endl;

	FILE* fp;     // file pointer
	float x, y, z;  // vertex coordinates
	float n0, n1, n2; // normal coordinates
	float r, g, b;  // vertex color
	int c1, c2;    // characters read from file
	int xn, yn, zn; // normal indicies
	int xv, yv, zv; // vertex indicies
	int count;
	char ignore[256];

	fp = fopen(filename.c_str(), "rb");

	if (fp == NULL)
	{
		std::cerr << "error loading file" << std::endl; exit(-1);
	}

	while ((c1 = fgetc(fp)) != EOF) {
		c2 = fgetc(fp);

		//Progress
		if (++lineNum % 100000 == 0)
			std::cout << "At line " << lineNum << std::endl;

		//Vertex case
		if ((c1 == 'v') && (c2 == ' ')) {
			count = fscanf(fp, "%f %f %f %f %f %f \n", &x, &y, &z, &r, &g, &b);
			if (count != 6 && count != 3)
				break;
			//stuff it into the vector 
			vertices->push_back(Vector3(x,y,z));

			if (count == 3) {
				colors->push_back(Vector3(.8,.8,.8));
			}
			else {
				colors->push_back(Vector3(r,g,b));
			}
		}
		//Normal case
		else if ((c1 == 'v') && (c2 == 'n')) {
			count = fscanf(fp, "%f %f %f \n", &n0, &n1, &n2);
			if (count != 3)
				break;
			float mag = sqrt(n0 * n0 + n1 * n1 + n2 * n2);
			normals->push_back((Vector3(n0 / mag, n1 / mag, n2 / mag)));
		}
		//Face case
		else if ((c1 == 'f') && (c2 == ' ')) {
			count = fscanf(fp, "%d//%d %d//%d %d//%d \n", &xv, &xn, &yv, &yn, &zv, &zn);
			if (count != 6)
				break;

			Face* face = new Face;

			face->vertexIndices[0] = xv - 1;
			face->vertexIndices[1] = yv - 1;
			face->vertexIndices[2] = zv - 1;

			face->normalIndices[0] = xn - 1;
			face->normalIndices[1] = yn - 1;
			face->normalIndices[2] = zn - 1;

			faces->push_back(*face);
		}
		//Ignores blank and commented lines
		else {
			fgets(ignore, 256, fp);
		}
	}
	fclose(fp);   // make sure you don't forget to close the file when done

	//Transferring data to more optimal format
	for (int i = 0; i < (int)faces->size(); i++) {
		Face face = faces->at(i);

		int vIndex0 = face.vertexIndices[0];
		int vIndex1 = face.vertexIndices[1];
		int vIndex2 = face.vertexIndices[2];
		int nIndex0 = face.normalIndices[0];
		int nIndex1 = face.normalIndices[1];
		int nIndex2 = face.normalIndices[2];

		for (int j = 0; j < 3; j++) {
			float x = (*vertices)[face.vertexIndices[j]][0];
			float y = (*vertices)[face.vertexIndices[j]][1];
			float z = (*vertices)[face.vertexIndices[j]][2];

			//Updating min and max values of vertices
			if (i == 0) {
				maxX = x;
				minX = x;
				maxY = y;
				minY = y;
				maxZ = z;
				minZ = z;
			}
			else {
				if (x > maxX) { maxX = x; }
				else if (x < minX) { minX = x; }
				if (y > maxY) { maxY = y; }
				else if (y < minY) { minY = y; }
				if (z > maxZ) { maxZ = z; }
				else if (z < minZ) { minZ = z; }
			}
		}

		all->push_back((*colors)[vIndex0]);
		all->push_back((*normals)[nIndex0]);
		all->push_back((*vertices)[vIndex0]);

		all->push_back((*colors)[vIndex1]);
		all->push_back((*normals)[nIndex1]);
		all->push_back((*vertices)[vIndex1]);

		all->push_back((*colors)[vIndex2]);
		all->push_back((*normals)[nIndex2]);
		all->push_back((*vertices)[vIndex2]);
	}
	std::cout << "Done parsing." << std::endl;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void OBJObject::left(float dist) {
	Matrix4 translation;
	translation.makeTranslate(dist, 0, 0);

	toWorld = translation * toWorld;
}

void OBJObject::right(float dist) {
	Matrix4 translation;
	translation.makeTranslate(-dist, 0, 0);

	toWorld = translation * toWorld;
}

void OBJObject::up(float dist) {
	Matrix4 translation;
	translation.makeTranslate(0, dist, 0);

	toWorld = translation * toWorld;
}

void OBJObject::down(float dist) {
	Matrix4 translation;
	translation.makeTranslate(0, -dist, 0);

	toWorld = translation*toWorld;
}

void OBJObject::in(float dist) {
	Matrix4 translation;
	translation.makeTranslate(0, 0, -dist);

	toWorld = translation*toWorld;
}

void OBJObject::out(float dist) {
	Matrix4 translation;
	translation.makeTranslate(0, 0, dist);

	toWorld = translation*toWorld;
}

void OBJObject::reset() {
	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	toWorld = startMatrix;
}

void OBJObject::scaleUp() {
	Matrix4 scale;
	scale.makeScale(1.1);

	toWorld = scale * toWorld;
}

void OBJObject::scaleDown() {
	Matrix4 scale;
	scale.makeScale(.9);

	toWorld = scale * toWorld;
}

void OBJObject::orbit(float angle) {
	Matrix4 rotate;
	rotate.makeRotateZ(angle);

	toWorld = rotate * toWorld;
}

void OBJObject::rotate(Vector3 axis, float angle) {
	Matrix4 rotate;
	rotate.makeRotateArbitrary(axis, angle);

	toWorld = rotate * toWorld;
}

void OBJObject::translate(Vector3 direction) {
	Matrix4 translation;
	translation.makeTranslate(direction[0], direction[1], direction[2]);

	toWorld = translation*toWorld;
}