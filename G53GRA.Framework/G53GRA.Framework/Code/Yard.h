#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "ObjLoader.h"

/*
This is a class that should dispaly our lamp with they rough rigid body
transform between our key frames
Here is a more complex example of the effects that can be achieved:
http://www.youtube.com/watch?v=cdtHSyfcSDs
*/

class Yard :
	public DisplayableObject,
	public Animation
{
public:
	Yard();
	~Yard() {};

	void Display();
	void Update(const double& deltaTime);

private:

	void DrawCube();            // function to draw a unit cube over the origin
	void DrawTetrahedron();
	void DrawCircle();
	void DrawCone();
	void DrawTextureTetrahedron(GLint texID2);
	void DrawTextureCube(GLint texID1);
	void DrawFrontDoor(GLint texID3);

	void DrawHouse();
	void DrawFencePiece();
	void DrawFence();
	void DrawGround();
	void DrawYardNo1();
	void DrawStone();
	void DrawPath();
	void DrawDoor();
	void DrawGlass();
	void DrawFront();


	int keyframe;               // variable to track which keyframe we are on
	float animateRotation;      // variable to track the current amount of rotation steps
	float animateTranslation;   // variable to track the current amount of translation steps
	float interpA;              // variable to hold what the first keyframe angle is
	float interpB;              // variable to hold what the second keyframe angle is
	float interpTime;           // variable to track how long the keyframe lasts i.e. how long do we have
								// to move from interpA to interpB
	float animateTime;
	float drawTimes;
	float Radius;


	GLint grassLand;
	GLint fencePiece;
	GLint wallPiece;
	GLint door;
	GLint stone;
	GLint woodFloorTex;

	ObjLoader* Base;

};

