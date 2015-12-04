#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Vector3.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
	static float spinSpeed;
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void processNormalKeys(unsigned char, int, int);
	static void processSpecialKeys(int, int, int);
	static void processMouseClick(int, int, int, int);
	static void processMouseMotion(int, int);
	static void processMouseWheel(int, int, int, int);
	static Vector3 trackball(float, float);

    
};

#endif

