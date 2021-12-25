#include "Bird.h"

#define GRAVITY -9.8f

Bird::Bird()
{

}
void Bird::Update(const double& deltaTime)
{
	// update the time and rotation steps
	animateTime += static_cast<float>(deltaTime);
	animateRotation += static_cast<float>(deltaTime);

	// check if we hit the end of the animation (3 seconds), if so reset
	if (animateTime >= 3.0f)
	{
		animateTime = 0.0f;
		keyframe = -1;
	}

	// check if we are in the 1st second of animation
	if (animateTime < 1.0f)
	{
		// check if we have only just entered the 1st keyframe in which case
		// set up the parameters
		if (keyframe != 0)
		{
			animateTime = 0.0f;
			animateRotation = 0.0f;
			animateTranslation = 0.0f;
			keyframe = 0;
			interpA = -45.0f;
			interpB = -60.0f;
			interpTime = 1.0f;
		}
	}
	// check if we are in the 1.0 to 1.25 seconds of animation
	else if (animateTime < 1.25f)
	{
		// check if we have only just entered the 2nd keyframe in which case 
		// set up the parameters
		if (keyframe != 1)
		{
			keyframe = 1;
			animateRotation = 0.0f;
			interpA = -60.0f;
			interpB = -15.0f;
			interpTime = 0.25f;
		}

		/*
		motion equations are usually referred to as the "SUVAT" equations.
		"SUVAT" is an acronym from the variables:
			S = displacement (s0 = initial displacement),
			U = initial velocity,
			V = final velocity,
			A = acceleration,
			T = time.
		*/

		// update the height value of the bounce using the suvat equation 
		// s = u*t + 1/2*a*t^2, let t = (animateTime-1.0)

		animateTranslation = 4.0f * -GRAVITY * (animateTime - 1.0f) + 0.5f * (animateTime - 1.0f) * (animateTime - 1.0f) * 4.0f * GRAVITY;
	}
	// check if we are in the 1.25 to 3 seconds of animation
	else
	{
		// check if we have only just entered the 3rd keyframe
		// in which case set up the parameters
		if (keyframe != 2)
		{
			keyframe = 2;
			animateRotation = 0.0f;
			interpA = -15.0f;
			interpB = -45.0f;
			interpTime = 1.75f;
		}

		// continue to update the height value of the bounce by solving the 
		// suvat equation s = u*t + 1/2*a*t^2

		animateTranslation = 4.0f * -GRAVITY * (animateTime - 1.0f) + 0.5f * (animateTime - 1.0f) * (animateTime - 1.0f) * 4.0f * GRAVITY;
	}
}

void Bird::Display()
{

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS); //save and all attributes to bird object
	glColor3f(0.f, 0.f, 1.f); //blue color
	glTranslatef(pos[0], pos[1]+ animateTranslation*5.0f, pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	drawBird();
	glPopAttrib();
	glPopMatrix();
}

void Bird::drawBird()
{

	glPushMatrix();
	glTranslatef(0.f, 1.f, 0.f); // move bired position up one
	drawBody(); //draw the round body of bird
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0f, 4.5f, 0.f); //move neck position back and up
	glRotatef(-30.f, 0.f, 0.f, 1.f); //rotate position 30 degrees forward in the z-axis
	drawNeck(); // draw neck
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.f, 2.f, -0.5f); //move tail position back
	glRotatef(-45.f, 0.f, 0.f, 1.f); // rotate tail position 45 degrees forward in the z-axis
	drawTail(); //draw tail
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5f, 1.f, 0.f);
	//draw right wing
	drawWing();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-3.5f, 1.f, -4.f);
	//draw left wing
	drawWing();
	glPopMatrix();

	//draw right leg
	glPushMatrix();
	glTranslatef(1.f, -1.f, 1.f);
	glRotatef(45.f, 0.f, 0.f, 1.f);
	drawLeg();
	glPopMatrix();

	//draw right talon
	glPushMatrix();
	glTranslatef(-3.f, 0.3f, 1.72f);
	drawTalons();
	glPopMatrix();

	//draw left leg
	glPushMatrix();
	glTranslatef(1.f, -1.f, -1.5f);
	glRotatef(45.f, 0.f, 0.f, 1.f);
	drawLeg();
	glPopMatrix();

	//draw left talon
	glPushMatrix();
	glTranslatef(-3.f, 0.3f, -0.78f);
	drawTalons();
	glPopMatrix();

}

void Bird::drawBody()
{
	glPushMatrix();
	glTranslatef(-4.f, 1.f, 0.f);
	glutSolidSphere(2.f, 10, 10);
	glPopMatrix();
}


void Bird::drawNeck()
{
	glPushMatrix();
	glScalef(0.2f, 1.f, 0.2f);
	glutSolidCube(2.5);
	glPushMatrix(); //push unto a stack and stack drawing the head in relation to the neck
	glTranslatef(1.f, 1.f, 0.f);
	drawHead();
	glPopMatrix();
	glPopMatrix();
}

void Bird::drawHead()
{
	glPushMatrix();
	glScalef(2.5f, 0.5f, 2.5f);
	glutSolidSphere(2.5f, 10, 10);
	glPushMatrix();
	glTranslatef(1.f, 0.f, 0.f);
	glRotatef(90.f, 0.f, 1.f, 0.f); //push unto a stack and start drawing beak in realtion to the head
	drawBeak();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 2.5f);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -2.5f);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();

	glPopMatrix();
}


void Bird::drawWing()
{
	glPushMatrix();
	glDisable(GL_CULL_FACE); //disable, so we can see other side of the wind when we change camera view
	glBegin(GL_TRIANGLES);
	glVertex3f(1.f, 1.f, 2.f);
	glVertex3f(0.f, 2.f, 2.f);
	glVertex3f(-3.f, -3.f, 2.f);
	glEnd();
	glEnable(GL_CULL_FACE);
	glPopMatrix();
}

void Bird::drawTail()
{
	glPushMatrix();
	glDisable(GL_CULL_FACE); //disable, so we can see other side of the wind when we change camera view
	glBegin(GL_TRIANGLES);
	glVertex3f(1.f, 1.f, 0.5f);
	glVertex3f(0.f, -2.f, 2.f);
	glVertex3f(0.f, -2.f, -1.5f);
	glEnd();
	glEnable(GL_CULL_FACE);
	glPopMatrix();
}

void Bird::drawBeak()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(1.f, 1.f, 0.f); //yellow
	glutSolidCone(2, 5, 10, 10);
	glPopAttrib();
	glPopMatrix();
}

void Bird::drawLeg()
{
	glPushMatrix();
	glTranslatef(-2.f, 4.5f, 0.2f);
	glScalef(0.2f, 1.5f, 0.2f);
	glutSolidCube(1.f);
	glPopMatrix();
}

void Bird::drawTalons()
{
	//draw three cubes to represent the talons of the bird
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(1.f, 1.f, 0.f); //yellow
	glTranslatef(0.f, 0.f, -0.5f);
	glRotatef(-45.f, 0.f, 1.f, 0.f);
	glScalef(0.5f, 0.2, 0.2f);
	glutSolidCube(0.5f);
	glPopAttrib();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, -0.55f);
	glScalef(0.5f, 0.2, 0.2f);
	glutSolidCube(0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, -0.6f);
	glRotatef(45.f, 0.f, 1.f, 0.f);
	glScalef(0.5f, 0.2, 0.2f);
	glutSolidCube(0.5f);
	glPopMatrix();
}

