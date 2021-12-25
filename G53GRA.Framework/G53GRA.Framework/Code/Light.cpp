#include "Light.h"
#include <cmath>


// 实现手电筒的功能
// initialise the parameters in tree class
Light::Light() {

}

// Display the tree
void Light::Display()
{
	GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };


	glEnable(GL_LIGHTING);
	// Set weak ambient light to make objects visible
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	// Sets the scattered light and mirror light composition of GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	// Sets the position of GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	// Set the spotlight effect of GL_LIGHT1, cut Angle 50 degrees
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0f);
	glEnable(GL_LIGHT1);
	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	// Setting material Properties
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);





	// 设置镜面光反射属性及强镜面指数
	/*glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 200);*/
}



