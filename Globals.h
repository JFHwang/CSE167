#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "House.h"
#include "Light.h"
#include "OBJObject.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Sphere.h"
#include "Skybox.h"
#include "Bezier.h"

class Globals
{
    
public:
    
    static Camera camera;
    static Cube cube;
	static Sphere sphere;
	static House house;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
	static Matrix4 D;
	static Matrix4 P;
	static bool spin;
	static bool drag;
	static bool scale;
	static bool spotAdjust;
	static float clickX;
	static float clickY;
	static Vector3 lastPoint;
	static Light pointLight;
	static Light dirLight;
	static Light spotLight;
	static Skybox skybox;
	static Bezier bezier;
	static Bezier bezier2;
    //Feel free to add more member variables as needed
    
};

#endif
