#include "Base.h"
#include "ObjLoader.h"

#include <cmath>
#include <string>

// define a gravity constance for the bounce equation
#define GRAVITY -9.8f
// define 
static float PI = (float)acos(-1);


/*
Linear interpolation between point A and B is used to decide where we are
between these two at time T.

NewPosition = startPosition + currentTime*[(distanceBetweenAandB)/totalTime];
or
NewPos = A + T*[(B-A)/totalTime]
(NewPos = interpA + animateRotation*[(interpB-interpA)/interpTime])

interpA is the position where the animation starts, in this case -15.
interpB is the position where it end, in this case -45.

interpTime is the total amount of time taken to move between the two
positions, in this case 1.75 seconds.

Then animateRotation keep track of the amount of time passed between starting
and ending the animation.
*/

// MAKE SURE WE INITIALISE OUR VARIABLES
Base::Base()
{
	objBase = new ObjLoader("./data/base.obj");
	objBox = new ObjLoader("./data/box.obj");
	objPlantForm = new ObjLoader("./data/plantForm.obj");

	baseTex = Scene::GetTexture("./Textures/grass.bmp");
	plantFormTex = Scene::GetTexture("./Textures/plantForm.bmp");
}




//void Butterfly::DrawButterflys(float moveX, float moveY, float moveZ, int color)
void Base::DrawBase()
{
	glPushMatrix();
	glTranslatef(1470.0f, -100.0f, 150.0f);
	//glRotatef(90, 1.0f, 0.0f, 0.0f);
	glScalef(130.0f, 130.0f, 130.0f);
	glClearColor(0.8f, 0.9f, 0.2f, 1.0f);
	//glColor3f(0.8f, 0.9f, 0.2f);
	objBase->Draw(baseTex);
	//objBase->Draw();

	glTranslatef(-9.0f, 3.0f, -3.0f);
	//glScalef(130.0f, 130.0f, 130.0f);
	objBase->Draw(baseTex);
	//objBox->Draw();

	glTranslatef(-5.0f, -1.0f, 0.0f);
	//glScalef(130.0f, 130.0f, 130.0f);
	objPlantForm->Draw(plantFormTex);
	//objBox->Draw();


	glPopMatrix();
}



void Base::Display()
{
	// Always push before making any changes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	DrawBase();


	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing

}

