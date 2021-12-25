#include "Ballon.h"
#include "ObjLoader.h"

#define GRAVITY -9.8f


Ballon::Ballon()
{

	ballonTex = Scene::GetTexture("./Textures/ballon.bmp");
	objBallon = new ObjLoader("./data/ballon2.obj");


}


/// Update the lamps position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Ballon::Update(const double& deltaTime)
{
	// update the time and rotation steps
	animateTime += static_cast<float>(deltaTime);
	animateTime2 += static_cast<float>(deltaTime);
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


void Ballon::Display()
{

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS); //save and all attributes to bird object
	

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1500.0f+animateTime2*60.0f, -2200.0f+ animateTime2 * 20.0f, -6700.0f);
	//glTranslatef(-1500.0f, -2200.0f, -6700.0f);
	glScalef(200.0f, 200.0f, 200.0f);
	glColor3f(1.0f, 0.5f, 0.0f);
	objBallon->Draw(ballonTex);

	glPopAttrib();
	glPopMatrix();
}



