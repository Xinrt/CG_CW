#include "Carrot.h"
#include "ObjLoader.h"
#include <string>

#define GRAVITY -9.8f

Carrot::Carrot()
{
	objCarrotLeaf = new ObjLoader("./data/carrot_leaf.obj");
	objCarrot = new ObjLoader("./data/carrot.obj");
	carrotLeafTex = Scene::GetTexture("./Textures/grass.bmp");
	carrotTex = Scene::GetTexture("./Textures/carrot.bmp");

	move = 0;

}
void Carrot::Update(const double& deltaTime)
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

void Carrot::Display()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    // Project from Object Space to World Space
    //glTranslatef(pos[0], pos[1], pos[2]);			// Position
    //glScalef(scale[0], scale[1], scale[2]);			// Scale

	if (!move) {
		glTranslatef(pos[0], pos[1], pos[2]);			// Position
		glScalef(scale[0], scale[1], scale[2]);			// Scale
		glColor3f(0.0, 1.0, 0.0);
		objCarrotLeaf->Draw();
		glTranslatef(0.6f, 1.1f, -2.8f);
		glColor3f(1.0, 0.2, 0.0);
		objCarrot->Draw();
	}
	else {
		glTranslatef(pos[0], pos[1]+80.0f, pos[2]);			// Position
		glScalef(scale[0], scale[1], scale[2]);			// Scale
		glColor3f(0.0, 1.0, 0.0);
		objCarrotLeaf->Draw();
		glTranslatef(0.6f, 1.1f, -2.8f);
		glColor3f(1.0, 0.2, 0.0);
		objCarrot->Draw();
	}
	//glTranslatef(pos[0], pos[1] + 80.0f, pos[2]);			// Position
	//glScalef(scale[0], scale[1], scale[2]);			// Scale
	//objCarrotLeaf->Draw();
	//glTranslatef(0.6f, 1.1f, -2.8f);
	//objCarrot->Draw();
	//objCarrotLeaf->Draw();
	//glTranslatef(0.6f, 1.1f, -2.8f);
	//objCarrot->Draw();


    glPopMatrix();
    glPopAttrib();
}

void Carrot::HandleKey(unsigned char key, int state, int x, int y)
{
	if (key == 'c' && state) {
		move = !move;
	}
}






