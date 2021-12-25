#include "Butterfly.h"
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
Butterfly::Butterfly() : keyframe(-1), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0), animateTime(0.0), drawTimes(3600), Radius(1.0)
{
	objl = new ObjLoader("./data/wings.obj");
	btTex = Scene::GetTexture("./Textures/grass.bmp");


	//glTranslatef(animateTime2 * 100.0f - 600.0f, 220.0f, 0.0f);
	totalNumbers = 1;
}

/// Update the lamps position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Butterfly::Update(const double& deltaTime)
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

	if (animateTime2 >= 10.0f)
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

// set the total number of butterflys on the screen
void Butterfly::setNumbers(int setNum)
{
	totalNumbers = setNum;
}

//void Butterfly::DrawButterflys(float moveX, float moveY, float moveZ, int color)
void Butterfly::DrawButterflys()
{
	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);


	// Save current style attributes

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 60.0f);
	glScalef(15.0f, 15.0f, 15.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(interpA + animateRotation * ((interpB - interpA) / interpTime), 0.0f, 1.0f, 0.0f);
	//glColor3f(1.0f, 1.0f, 0.5f);
	//objl->Draw(btTex);
	objl->Draw();


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 60.0f);
	glScalef(15.0f, 15.0f, 15.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(interpA + animateRotation * ((interpB - interpA) / interpTime), 0.0f, -1.0f, 0.0f);
	//glColor3f(1.0f, 1.0f, 0.5f);
	//objl->Draw(btTex);
	objl->Draw();

	glPopMatrix();
	glPopMatrix();
}

void Butterfly::DrawButterflys2()
{
	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);


	// Save current style attributes

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 60.0f);
	glScalef(15.0f, 15.0f, 15.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(interpA + animateRotation * ((interpB - interpA) / interpTime), 0.0f, 1.0f, 0.0f);
	//glColor3f(1.0f, 1.0f, 0.5f);
	//objl->Draw(btTex);
	objl->Draw();


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 60.0f);
	glScalef(15.0f, 15.0f, 15.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(interpA + animateRotation * ((interpB - interpA) / interpTime), 0.0f, -1.0f, 0.0f);
	//glColor3f(1.0f, 1.0f, 0.5f);
	//objl->Draw(btTex);
	objl->Draw();

	glPopMatrix();
	glPopMatrix();
}


void Butterfly::Display()
{
	// Always push before making any changes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//glTranslatef(0.0f, 220.0f, -60.0f);
	//glTranslatef(0.0f, 220.0f, -60.0f);
	if (totalNumbers == 1) {
		glPushMatrix();
		glTranslatef(animateTime2 * 100.0f - 600.0f, 220.0f, 0.0f);	
		glColor3f(1.0f, 1.0f, 0.5f);
		DrawButterflys();
		glPopMatrix();
	}
	else if (totalNumbers == 2) {
		glPushMatrix();

		if (animateTime2 < 5.0f) {
			glTranslatef(animateTime2 * 100.0f - 200.0f, 220.0f, 220.0f);
			glColor3f(1.0f, 1.0f, 0.5f);
			DrawButterflys();
		}/* else {
			glTranslatef(200.0f - (animateTime2 - 5) * 100.0f, 220.0f, 120.0f);
		}*/
		
		//glRotatef(animateTime2 * 360.0f * 0.1f, 0.0f, 0.0f, 1.0f);
		//glTranslatef(0.0f, 220.0f, 0.0f);

		//glTranslatef(300.0f, 0.0f, 0.0f);
		//glRotatef(animateTime2 * 20.0f, 0.0f, 1.0f, 0.0f);


		if (animateTime2 >= 5) {
			glTranslatef(200.0f - (animateTime2 - 5) * 100.0f, 220.0f, 120.0f);
			glColor3f(1.0f, 1.0f, 0.5f);
			DrawButterflys2();
		}
		//DrawButterflys();

		//glPopMatrix();
		//glPushMatrix();
		//glScalef(0.6f, 0.6f, 0.6f);
		////glTranslatef(animateTime2 * 100.0f - 600.0f, 200.0f, 0.0f);
		////glTranslatef(0.0f, 110.0f, -320.0f);
		//glTranslatef(animateTime2 * 50.0f, 110.0f+ animateTime2*50.0f, -320.0);
		//glColor3f(1.0f, 0.7f, 0.5f);
		//DrawButterflys();
		glPopMatrix();

	}


	//glTranslatef(animateTime2*startX-600.0f, startY, startZ);




	
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing

}

