#include "Globals.h"

Camera Globals::camera;

Cube Globals::cube(10.0);
Sphere Globals::sphere(10, 100, 100);

House Globals::house;

Light Globals::light;
Light Globals::pointLight;
Light Globals::dirLight;
Light Globals::spotLight;

Skybox Globals::skybox;

DrawData Globals::drawData;
UpdateData Globals::updateData;

Matrix4 Globals::D;
Matrix4 Globals::P;
Vector3 Globals::lastPoint;

Bezier Globals::bezier;
Bezier Globals::bezier2;

bool Globals::spotAdjust;
bool Globals::spin;
bool Globals::drag;
bool Globals::scale;
float Globals::clickX;
float Globals::clickY;

