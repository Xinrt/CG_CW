#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "ObjLoader.h"

class Ballon :
	public DisplayableObject,
	public Animation
{
public:
	Ballon();
	~Ballon() {};

	void Display();
	void Update(const double& deltaTime);
private:
	
	
	
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

	GLint ballonTex;

	ObjLoader* objBallon;
	

};

