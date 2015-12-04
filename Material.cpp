#include "Material.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Material::Material()
{
    //Material setup goes hurr
    ambientColor = Color::ambientMaterialDefault();
    diffuseColor = Color::diffuseMaterialDefault();
    specularColor = Color::specularMaterialDefault();
    emissionColor = Color::emissionMaterialDefault();
    shininess = 10.0;
    
    //Set the initial color to a random pastel color
    //Can be removed once materials are implemented
    color = Color::randomPastel();
}

Material::~Material()
{
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(void)
{
    //Set the material properties for ambient, diffuse, specular, emission, and shininess
    //Hint: Lookup how glMaterialfv works
	GLfloat DiffuseMaterial[] = { diffuseColor[0], diffuseColor[1], diffuseColor[2] };
	GLfloat SpecularMaterial[] = { specularColor[0], specularColor[1], specularColor[2] };
	GLfloat EmissiveMaterial[] = { emissionColor[0], emissionColor[1], emissionColor[2] };
	
	GLfloat SpecularLight[] = { specularColor[0], specularColor[1], specularColor[2] };
	GLfloat AmbientLight[] = { ambientColor[0], ambientColor[1], ambientColor[2] };
	GLfloat DiffuseLight[] = { diffuseColor[0], diffuseColor[1], diffuseColor[2] };
	GLfloat mShininess[] = { shininess, shininess, shininess };
	/*
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	*/
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, EmissiveMaterial);
	



    //Set the color property (can be removed once materials are implemented)
    //Used for projects 1, 2, and 3
    glColor3fv(color.ptr());
}



