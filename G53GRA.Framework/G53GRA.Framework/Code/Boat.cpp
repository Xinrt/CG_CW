#include "Boat.h"
#include "ObjLoader.h"
#include "Camera.h"

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
Boat::Boat() : keyframe(-1), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0), animateTime(0.0), drawTimes(3600), Radius(1.0)
{
	objBase = new ObjLoader("./data/boat.obj");
	boatTex = Scene::GetTexture("./Textures/grass.bmp");


	//glTranslatef(animateTime2 * 100.0f - 600.0f, 220.0f, 0.0f);
	totalNumbers = 1;
}

/// Update the lamps position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Boat::Update(const double& deltaTime)
{
	// update the time and rotation steps
	animateTime += static_cast<float>(deltaTime);
	animateRotation += static_cast<float>(deltaTime);
	animateTime2 += static_cast<float>(deltaTime);

	// check if we hit the end of the animation (3 seconds), if so reset
	if (animateTime >= 3.0f)
	{
		animateTime = 0.0f;
		keyframe = -1;
	}

	if (animateTime2 >= 36.0f)
	{
		animateTime2 = 0.0f;
	}



	// check if we are in the 1st second of animation
	if (animateTime < 1.5f)
	{
		// check if we have only just entered the 1st keyframe in which case
		// set up the parameters
		if (keyframe != 0)
		{
			animateTime = 0.0f;
			animateRotation = 0.0f;
			animateTranslation = 0.0f;
			keyframe = 0;
			interpA = -30.0f;
			interpB = -60.0f;
			interpTime = 1.0f;
		}
	}
	else
	{
		// check if we have only just entered the 3rd keyframe
		// in which case set up the parameters
		if (keyframe != 2)
		{
			keyframe = 2;
			animateRotation = 0.0f;
			interpA = -60.0f;
			interpB = -30.0f;
			interpTime = 1.0f;
		}

		// continue to update the height value of the bounce by solving the 
		// suvat equation s = u*t + 1/2*a*t^2

		animateTranslation = 4.0f * -GRAVITY * (animateTime - 1.0f) + 0.5f * (animateTime - 1.0f) * (animateTime - 1.0f) * 4.0f * GRAVITY;
	}
}

void Boat::DrawCube()
{
	// This function draws a unit cube centered around the origin

	glBegin(GL_QUADS);
	// Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	// Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	// Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	// Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	// Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	// Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
}

void Boat::DrawTorus(double Radius, double TubeRadius, int Sides, int Rings)
{
	double sideDelta = 2.0 * PI / Sides;
	double ringDelta = 2.0 * PI / Rings;
	double theta = 0;
	double cosTheta = 1.0;
	double sinTheta = 0.0;

	double phi, sinPhi, cosPhi;
	double dist;
	glColor3f(1, 0, 0);
	for (int i = 0; i < Rings; i++)
	{
		double theta1 = theta + ringDelta;
		double cosTheta1 = cos(theta1);
		double sinTheta1 = sin(theta1);

		glBegin(GL_QUAD_STRIP);
		phi = 0;
		for (int j = 0; j <= Sides; j++)
		{
			phi = phi + sideDelta;
			cosPhi = cos(phi);
			sinPhi = sin(phi);
			dist = Radius + (TubeRadius * cosPhi);

			glNormal3f(cosTheta * cosPhi, sinTheta * cosPhi, sinPhi);
			glColor3f(cosTheta, sinTheta, sinPhi);
			glVertex3f(cosTheta * dist, sinTheta * dist, TubeRadius * sinPhi);

			glNormal3f(cosTheta1 * cosPhi, sinTheta1 * cosPhi, sinPhi);
			glColor3f(cosTheta1, sinTheta1, sinPhi);
			glVertex3f(cosTheta1 * dist, sinTheta1 * dist, TubeRadius * sinPhi);
		}
		glEnd();
		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;
	}
}






//void Butterfly::DrawButterflys(float moveX, float moveY, float moveZ, int color)
void Boat::DrawBase()
{
	glPushMatrix();
;	glTranslatef(1200.0f, -100.0f, 160.0f);
	glScalef(300.0f, 300.0f, 300.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	//objBase->Draw(boatTex);
	objBase->Draw();


	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(1.3f, 1.0f, 1.0f);
	DrawCube();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.32f, 0.2f, -0.45f);
	glScalef(0.55f, 0.4f, 0.12f);
	glColor3f(1.0f, 1.0f, 0.5f);
	DrawCube();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.32f, 0.2f, -0.45f);
	glScalef(0.55f, 0.4f, 0.12f);
	glColor3f(1.0f, 1.0f, 0.5f);
	DrawCube();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glScalef(1.5f, 0.05f, 1.5f);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawCube();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.15f, -0.3f, 0.3f);
	glScalef(0.2f, 0.2f, 0.2f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(0.9f, 0.5f, 0.5f);
	DrawTorus(1.0f, 0.2f, 20, 30);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.15f, -0.3f, 1.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(0.9f, 0.5f, 0.5f);
	DrawTorus(1.0f, 0.2f, 20, 30);
	glPopMatrix();

	glPopMatrix();
}



void Boat::Display()
{
	// Always push before making any changes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glTranslatef(3000.0f, 0.0f, 0.0f);
	glRotatef(-animateTime2 * 10.0f, 0.0f, 1.0f, 0.0f);
	DrawBase();
	glPopMatrix();

	
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing

}





