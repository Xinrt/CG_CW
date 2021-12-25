#include "FirePlace.h"
#include "iostream"
#include "ObjLoader.h"

#define GRAVITY -9.8f


FirePlace::FirePlace()
{
	firePlaceTex = Scene::GetTexture("./Textures/plantForm.bmp");
	objFirePlace = new ObjLoader("./data/fireplace.obj");

}

void FirePlace::Update(const double& deltaTime)
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

	if (animateTime2 >= 0.8f)
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



void FirePlace::Display()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	//glTranslatef(0.0f, 40.0f, 500.0f);
	glPushMatrix();
	glTranslatef(0.0f, -25.0f, -115.0f);
	glScalef(25.0f, 25.0f, 25.0f);
	objFirePlace->Draw(firePlaceTex);

	// fire
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.4f, 0.0f);
	glutSolidSphere(0.02f, 40, 40);
	/*glEnable(GL_LIGHTING);
	glDisable(GL_LIGHTING);*/

	// show
	glColor3f(1.0f, 0.8f, 0.0f);
	glTranslatef(0.1f, 0.1f, 0.0f);
	glutSolidSphere(0.02f, 40, 40);

	glColor3f(1.0f, 0.7f, 0.0f);
	glTranslatef(-0.1f, 0.1f, 0.1f);
	glutSolidSphere(0.02f, 40, 40);

	glColor3f(1.0f, 0.6f, 0.0f);
	glTranslatef(-0.1f, -0.1f, 0.1f);
	glutSolidSphere(0.02f, 40, 40);

	//glPushMatrix();
	glColor3f(1.0f, 0.2f, 0.0f);
	glTranslatef(-0.05f, 0.1f + animateTime2 * 0.1, -0.1f);
	glutSolidSphere(0.02f, 40, 40);

	glColor3f(1.0f, 0.05f, 0.0f);
	glTranslatef(0.1f, 0.1f, 0.0f);
	glutSolidSphere(0.02f, 40, 40);

	glColor3f(1.0f, 0.15f, 0.0f);
	glTranslatef(0.16f, 0.0f, 0.0f);
	glutSolidSphere(0.02f, 40, 40);

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -0.1f, 0.1f);
	glutSolidSphere(0.02f, 40, 40);

	glColor3f(1.0f, 0.15f, 0.0f);
	glTranslatef(-0.1f, 0.1f, 0.1f);
	glutSolidSphere(0.02f, 40, 40);

	//glPopMatrix();
	if (animateTime2 > 0.3) {
		glTranslatef(-0.1f, -0.3f, -0.1f);

		glColor3f(1.0f, 0.2f, 0.0f);
		glTranslatef(-0.05f, 0.1f, -0.1f);
		//glScalef(20.0f, 20.0f, 20.0f);
		glutSolidSphere(0.02f, 40, 40);

		glColor3f(1.0f, 0.05f, 0.0f);
		glTranslatef(0.1f, 0.1f, 0.0f);
		glutSolidSphere(0.02f, 40, 40);

		glColor3f(1.0f, 0.15f, 0.0f);
		glTranslatef(0.16f, 0.0f, 0.0f);
		glutSolidSphere(0.02f, 40, 40);

		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.1f);
		glutSolidSphere(0.02f, 40, 40);

		glColor3f(1.0f, 0.15f, 0.0f);
		glTranslatef(-0.1f, 0.1f, 0.1f);
		glutSolidSphere(0.02f, 40, 40);
	}
	glEnable(GL_LIGHTING);

	glPopMatrix();

	glPopAttrib();

}

