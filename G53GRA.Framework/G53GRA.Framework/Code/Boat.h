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

class Boat :
	public DisplayableObject,
	public Animation
{
public:
	Boat();
	~Boat() {};

	void Display();
	void Update(const double& deltaTime);

private:

	void DrawBase();
	void DrawCube();
	void DrawTorus(double Radius, double TubeRadius, int Sides, int Rings);
	//void DrawButterflys(float moveX, float moveY, float moveZ, int color);

	ObjLoader* objBase;
	int totalNumbers;


	int keyframe;               // variable to track which keyframe we are on
	float animateRotation;      // variable to track the current amount of rotation steps
	float animateTranslation;   // variable to track the current amount of translation steps
	float interpA;              // variable to hold what the first keyframe angle is
	float interpB;              // variable to hold what the second keyframe angle is
	float interpTime;           // variable to track how long the keyframe lasts i.e. how long do we have
								// to move from interpA to interpB
	float animateTime;
	float animateTime2;
	float drawTimes;
	float Radius;

	GLint boatTex;

};

#pragma once
