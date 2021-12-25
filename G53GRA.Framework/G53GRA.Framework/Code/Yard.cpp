#include "Yard.h"
#include "LampMesh.h"
#include "ObjLoader.h"

#include <cmath>

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
Yard::Yard() : keyframe(-1), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0), animateTime(0.0), drawTimes(3600), Radius(1.0) 
{
	Base = new ObjLoader("./data/base.obj");


	grassLand = Scene::GetTexture("./Textures/grass.bmp");
	fencePiece = Scene::GetTexture("./Textures/fence.bmp");
	wallPiece = Scene::GetTexture("./Textures/housewood.bmp");
	door = Scene::GetTexture("./Textures/frontdoor.bmp");
	//stone = Scene::GetTexture("./Textures/house.bmp");
	woodFloorTex = Scene::GetTexture("./Textures/woodFloor.bmp");
	
}

/// Update the lamps position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Yard::Update(const double& deltaTime)
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

void Yard::DrawDoor()
{
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 120.0f, 120.0f);
	glColor3f(1.0f, 1.0f, 0.5f);
	glScalef(16.0, 0.0, 40.0);
	//glScalef(6.0, 6.0, 6.0);
	glScalef(3.2f, 0.2f, 2.0f);
	//DrawFrontDoor(door);
	//DrawTextureCube(door);
	DrawTextureCube(fencePiece);
	glPopMatrix();
}

void Yard::DrawGlass()
{
	glPushMatrix();
	glEnable(GL_BLEND); // transparent
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);
	//glColor4f(230.0 / 255, 230.0 / 255, 230.0 / 255, 0.2);
	glColor4f(230.0 / 255, 230.0 / 255, 230.0 / 255, 0.6);

	// first glass
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	//glColor4f(230.0 / 255, 230.0 / 255, 230.0 / 255, 0.2);
	//DrawCube();
	glutSolidCube(1);
	glPopMatrix();

	

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);

	glColor4f(230.0 / 255, 230.0 / 255, 230.0 / 255, 0.2);

	glPopMatrix();
}

void Yard::DrawFront()
{
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 120.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.5f);
	glScalef(62.0, 0.0, 20.0);
	//glScalef(6.0, 6.0, 6.0);
	glScalef(4.0f, 0.2f, 2.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	DrawCube();



	glPopMatrix();
}


//void  Yard::DrawHouse()
//{
//	glPushMatrix();
//
//	// top & bottom
//	//glColor3f(0.5f, 1.0f, 0.5f);
//	//glScalef(80.0, 60.0, 70.0);
//	////glScalef(400.0, 120.0, 1.0);
//	//glScalef(4.0f, 0.2f, 2.0f);
//	//glTranslatef(0.0f, 7.0f, 0.0f);
//	//DrawTextureCube(wallPiece);
//
//
//	glPopMatrix();
//	glPushMatrix();
//	glColor3f(0.5f, 1.0f, 0.5f);
//	glScalef(62.0, 0.1, 62.0);
//	//glScalef(400.0, 120.0, 1.0);
//	glTranslatef(0.0f, -1950.0f, 0.0f);
//	glScalef(4.0f, 0.2f, 2.0f);
//
//	//DrawTextureCube(wallPiece);
//	glScalef(2.0f, 2.0f, 2.0f);
//	DrawCube();
//
//	// front & back wall
//	glPopMatrix();
//	glPushMatrix();
//
//	DrawFront();
//
//
//	glPopMatrix();
//	glPushMatrix();
//	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//	glTranslatef(0.0f, -120.0f, 80.0f);
//	glColor3f(1.0f, 1.0f, 0.5f);
//	glScalef(62.0, 0.0, 62.0);
//	//glScalef(6.0, 6.0, 6.0);
//	glScalef(4.0f, 0.2f, 2.0f);
//	//DrawTextureCube(wallPiece);
//	glScalef(2.0f, 2.0f, 2.0f);
//	DrawCube();
//
//
//
//	// two small squares
//	glPopMatrix();
//	glPushMatrix();
//	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
//	glTranslatef(-80.0f, 240.0f, 0.0f);
//	glColor3f(1.0f, 0.5f, 0.5f);
//	glScalef(62.0, 0.0, 62.0);
//	//glScalef(6.0, 6.0, 6.0);
//	glScalef(2.0f, 0.2f, 2.0f);
//	//DrawTextureCube(wallPiece);
//	glScalef(2.0f, 2.0f, 2.0f);
//	DrawCube();
//
//	glPopMatrix();
//	glPushMatrix();
//	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
//	glTranslatef(-80.0f, -240.0f, 0.0f);
//	glColor3f(1.0f, 0.5f, 0.5f);
//	glScalef(62.0, 0.0, 62.0);
//	//glScalef(6.0, 6.0, 6.0);
//	glScalef(2.0f, 0.2f, 2.0f);
//	//DrawTextureCube(wallPiece);
//	glScalef(2.0f, 2.0f, 2.0f);
//	DrawCube();
//
//	//roof
//	glPopMatrix();
//	glPushMatrix();
//	glRotatef(-90, 1.0, 0.0, 0.0);
//	glTranslatef(0.0f, 0.0f, 50.0f);
//	glColor3f(1.0f, 1.0f, 0.0f);
//	glScalef(80.0, 80.0, 80.0);
//	//glScalef(8.0, 8.0, 8.0);
//	glScalef(4.2f, 2.1f, 2.0f);
//	DrawTextureTetrahedron(fencePiece);
//
//
//	glPopMatrix();
//
//}

void  Yard::DrawHouse()
{
	glPushMatrix();

	// top & bottom
	//glColor3f(0.5f, 1.0f, 0.5f);
	//glScalef(80.0, 60.0, 70.0);
	////glScalef(400.0, 120.0, 1.0);
	//glScalef(4.0f, 0.2f, 2.0f);
	//glTranslatef(0.0f, 7.0f, 0.0f);
	//DrawTextureCube(wallPiece);


	glPopMatrix();
	glPushMatrix();
	glColor3f(0.5f, 1.0f, 0.5f);
	glScalef(60.0, 60.0, 60.0);
	//glScalef(400.0, 120.0, 1.0);
	glScalef(4.0f, 0.2f, 2.0f);
	glTranslatef(0.0f, -15.0f, 0.0f);
	DrawTextureCube(woodFloorTex);

	// front & back wall
	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 125.0f, 55.0f);
	glColor3f(1.0f, 1.0f, 0.5f);
	glScalef(60.0, 60.0, 60.0);
	//glScalef(6.0, 6.0, 6.0);
	glScalef(4.0f, 0.2f, 2.0f);
	DrawFrontDoor(door);
	//DrawTextureCube(door);

	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -125.0f, 62.0f);
	glColor3f(1.0f, 1.0f, 0.5f);
	glScalef(60.0, 60.0, 60.0);
	//glScalef(6.0, 6.0, 6.0);
	glScalef(4.0f, 0.2f, 2.0f);
	DrawTextureCube(wallPiece);

	// two small squares
	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-60.0f, 220.0f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.5f);
	glScalef(60.0, 60.0, 60.0);
	//glScalef(6.0, 6.0, 6.0);
	glScalef(2.0f, 0.2f, 2.0f);
	DrawTextureCube(wallPiece);

	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-60.0f, -220.0f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.5f);
	glScalef(60.0, 60.0, 60.0);
	//glScalef(6.0, 6.0, 6.0);
	glScalef(2.0f, 0.2f, 2.0f);
	DrawTextureCube(wallPiece);

	//roof
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, 0.0f, 70.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef(80.0, 80.0, 80.0);
	//glScalef(8.0, 8.0, 8.0);
	glScalef(4.2f, 2.1f, 2.0f);
	DrawTextureTetrahedron(fencePiece);


	glPopMatrix();

}

void Yard::DrawTextureCube(GLint texID)
{
	glColor3ub(255, 204, 117);
	// add texture 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glBegin(GL_QUADS);

	// draw the front sky

	// set the colour of the front sky
	//glColor3f(1.0f, 1.0f, 1.0f);

	// set the normal of the front sky
	glNormal3f(0.0f, 0.0f, -1.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the back sky

	// set the normal of the back sky
	glNormal3f(0.0f, 0.0f, 1.0f);

	// define texture coordinates for the 4 vertices

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the left sky

	// set the normal of the left sky
	glNormal3f(1.0f, 0.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the right sky

	// set the normal of the right sky
	glNormal3f(-1.0f, 0.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the top sky

	// set the normal of the top sky
	glNormal3f(0.0f, -1.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the bottom sky

	// set the normal of the bottom sky
	glNormal3f(0.0f, 1.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();

	// Stop blending textures and colours
	glDisable(GL_COLOR_MATERIAL);
	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}

void Yard::DrawFrontDoor(GLint texID3)
{
	glColor3ub(255, 204, 117);
	// add texture to roof 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glBegin(GL_QUADS);

	// draw the front sky

	// set the colour of the front sky
	//glColor3f(1.0f, 1.0f, 1.0f);

	// set the normal of the front sky
	glNormal3f(0.0f, 0.0f, -1.0f);

	// define texture coordinates for the 4 vertices
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the back sky

	// set the normal of the back sky
	glNormal3f(0.0f, 0.0f, 1.0f);

	// define texture coordinates for the 4 vertices

	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the left sky

	// set the normal of the left sky
	glNormal3f(1.0f, 0.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the right sky

	// set the normal of the right sky
	glNormal3f(-1.0f, 0.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the top sky

	// set the normal of the top sky
	glNormal3f(0.0f, -1.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	//glTexCoord2f(0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	//glTexCoord2f(1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// draw the bottom sky

	// set the normal of the bottom sky
	glNormal3f(0.0f, 1.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();

	// Stop blending textures and colours
	glDisable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}


void Yard::DrawFencePiece()
{
	glPushMatrix();

	// 1
	glColor3f(0.5f, 1.0f, 0.5f);
	glScalef(15.0f, 15.0f, 15.0f);
	glScalef(0.5f, 4.0f, 0.5f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	DrawTextureCube(fencePiece);

	// 2
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.5f, 1.0f, 0.5f);
	glScalef(15.0f, 15.0f, 15.0f);
	glScalef(0.5f, 4.5f, 0.5f);
	glTranslatef(1.0f, 0.06f, 0.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	DrawTextureCube(fencePiece);

	// 3
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.5f, 1.0f, 0.5f);
	glScalef(15.0f, 15.0f, 15.0f);
	glScalef(0.5f, 5.0f, 0.5f);
	glTranslatef(2.0f, 0.1f, 0.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	DrawTextureCube(fencePiece);

	// 2
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.5f, 1.0f, 0.5f);
	glScalef(15.0f, 15.0f, 15.0f);
	glScalef(0.5f, 4.5f, 0.5f);
	glTranslatef(3.0f, 0.06f, 0.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	DrawTextureCube(fencePiece);

	// 1
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.5f);
	glScalef(15.0f, 15.0f, 15.0f);
	glScalef(0.5f, 4.0f, 0.5f);
	glTranslatef(4.0f, 0.0f, 0.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	DrawTextureCube(fencePiece);

	glPopMatrix();
}

void Yard::DrawFence()
{
	glPushMatrix();

	// gate's right side
			// put 11 pieces
	//glTranslatef(-110.0f, 0.0f, 0.0f);
	DrawFencePiece();

	for (float i = 1.0f; i < 15; i++) {
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-110.0f + i * 37.0f, 0.0f, 0.0f);
		DrawFencePiece();
	}

	// put 7 pieces
	for (float j = 0.0f; j < 7; j++) {
		glPopMatrix();
		glPushMatrix();
		glTranslatef(480.0f, 0.0f, 30.0f - j * 37.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		DrawFencePiece();
	}


	// put 7 pieces
	for (float j2 = 0.0f; j2 < 7; j2++) {
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-80.0f, 0.0f, 30.0f - j2 * 37.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		DrawFencePiece();
	}

	//// back gate
	for (float kr = 0.0f; kr < 15; kr++) {
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-110.0f + kr * 37.0f, 0.0f, -265.0f);
		DrawFencePiece();
	}




	glPopMatrix();
}


/// Draw a cube with normals
void Yard::DrawCube()
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

void Yard::DrawTetrahedron()
{
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, -1.0f, 0.707f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 0.0f, 0.707f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 0.707f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 0.0f, 0.707f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.2f);
	glEnd();
}

void Yard::DrawTextureTetrahedron(GLint texID2)
{

	glColor3ub(255, 204, 117);
	// add texture to roof 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, -1.0f, 0.707f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.2f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 0.0f, 0.707f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.2f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 0.707f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.2f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 0.0f, 0.707f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.2f);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}

void Yard::DrawCircle()
{
	glBegin(GL_TRIANGLE_FAN);           //扇形连续填充三角形串
	glVertex3f(0.0f, 0.0f, 0.0f);
	int i = 0;
	for (i = 0; i <= 360; i +=15)
	{
		float p = i * 3.14 / 180;
		//glColor3f(sin(p), cos(p), tan(p));
		glVertex3f(sin(p), cos(p), 0.0f);
	}
	glEnd();
}

void Yard::DrawStone()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, stone);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

}

void Yard::DrawCone()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, grassLand);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBegin(GL_QUAD_STRIP);//连续填充四边形串
	int i = 0;
	for (i = 0; i <= 360; i += 15)
	{
		float p = i * 3.14 / 180;
		//glColor3f(sin(p), cos(p), 1.0f);
		//glColor3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0, 0, 1.0f);
		glVertex3f(sin(p), cos(p), 0.0f);
	}
	glEnd();

	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

}

void Yard::DrawPath()
{
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glPushMatrix();

	//glTranslatef(0.0f, 0.0f, -500.0f);
	glScalef(110.0f, 110.0f, 110.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawCircle();
	//DrawCube();

	for (int i = 0; i < 5; i++) {
		glTranslatef(1.5f, 0.0f, 1.2f);
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawCircle();
		//DrawCube();

		glTranslatef(-1.5f, 0.0f, 1.2f);
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawCircle();
		//DrawCube();
	}
	

	//glTranslatef(1.5f, 0.0f, 1.2f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	////DrawCircle();
	//DrawCube();

	//glTranslatef(-1.5f, 0.0f, 1.2f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	////DrawCircle();
	//DrawCube();

	glPopMatrix();
}


void Yard::DrawGround()
{
	//int floorSize = 1000;

	//// Enable Texturing
	//glEnable(GL_TEXTURE_2D);

	//// Enable setting the colour of the material the cube is made from
	//// as well as the material for blending.
	//glEnable(GL_COLOR_MATERIAL);

	//// Tell openGL which texture buffer to use
	//// apply the texture of soil to the whole circular floor
	//glBindTexture(GL_TEXTURE_2D, grassLand);

	//glBegin(GL_QUADS);

	//for (int i = -floorSize; i < floorSize; i++)
	//{
	//	for (int j = -floorSize; j < floorSize; j++)
	//	{
	//		// generate a circular region
	//		if (sqrt(i * i + j * j) >= floorSize)
	//			continue;
	//		glNormal3f(0.0f, 1.0f, 0.0f);
	//		glTexCoord2f(0.0f, 0.0f);
	//		glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j) + scale[2]);
	//		glTexCoord2f(0.0f, 1.0f);
	//		glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j));
	//		glTexCoord2f(1.0f, 1.0f);
	//		glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j));
	//		glTexCoord2f(1.0f, 0.0f);
	//		glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j) + scale[2]);


	//	}
	//}
	//glEnd();

	//// Stop blending textures and colours
	//glDisable(GL_COLOR_MATERIAL);

	//// Bind to the blank buffer to stop ourselves accidentaly
	//// using the wrong texture in the next draw call
	//glBindTexture(GL_TEXTURE_2D, NULL);
	//// Stop performing texturing
	//glDisable(GL_TEXTURE_2D);
	
	glScalef(500.0f, 1.0f, 500.0f);
	DrawTextureCube(grassLand);
}


void Yard::Display()
{
	// Always push before making any changes


	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//glTranslatef(0.0f, -100.0f, 0.0f);

	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

	// Set colour to pale grey
	glColor3ub(250, 250, 250);

	//gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, -50.0, 0.0, 1.0, 0.0);

	glScalef(0.4f, 0.4f, 0.4f);
	//glTranslatef(0.0f, -25.0f + animateTranslation, 0.0f);
	glPushMatrix();
	DrawYardNo1();


	

	glPopMatrix();
	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	

}

void Yard::DrawYardNo1()
{
	// start

	//glRotatef(90, 1.0, 0.0, 0.0);
	//glRotatef(animateTime*360.0f*0.5f, 1.0f, 0.0f, 0.0f);
	glPushMatrix();


	// show fence
	//glScalef(0.3f, 0.3f, 0.3f);
	//glRotatef(180, 0.0, 1.0, 0.0);
	glTranslatef(-250.0f, 0.0f, 400.0f);
	glScalef(0.5f, 0.3f, 0.3f);

	DrawFence();

	

	//// show house
	glPopMatrix();
	glPushMatrix();
	//glRotatef(90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 220.0f, -150.0f);
	glScalef(1.2f, 1.2f, 1.6f);
	DrawHouse();




	//glPopMatrix();
	//glPushMatrix();
	//glTranslatef(0.0f, 2.0f, 0.0f);
	//DrawGround();


	//glPopMatrix();
	//glPushMatrix();
	//glTranslatef(470.0f, -98.0f, 0.0f);
	////glRotatef(90, 1.0f, 0.0f, 0.0f);
	//glScalef(130.0f, 130.0f, 130.0f);
	//glClearColor(0.8f, 0.9f, 0.2f, 1.0f);
	//glColor3f(0.8f, 0.9f, 0.2f);
	//Base->Draw();


	//glPopMatrix();
	//glPushMatrix();
	//glRotatef(90, 1.0f, 0.0f, 0.0f);
	//glTranslatef(100.0f, 0.0f, 0.0f);
	//glScalef(200.0f, 200.0f, 200.0f);
	//glScalef(500.0f, 500.0f, 500.0f);
	//glRotatef(animateTime * 360.0f * 0.5f, 0.0f, 0.0f, 1.0f);
	//DrawCube();

	

	////glPopMatrix();
	////glPushMatrix();
	////string filePath = "data/stone.obj";
	//////string filePath = "data/tree.obj";
	////ObjLoader stone1 = ObjLoader(filePath);
	////glTranslatef(-470.0f, -140.0f, -90.0f);
	////glRotatef(animateTime * 360.0f * 0.5f, 1.0f, 0.0f, 0.0f);
	////stone1.Draw();


	////end
	glPopMatrix();
}


