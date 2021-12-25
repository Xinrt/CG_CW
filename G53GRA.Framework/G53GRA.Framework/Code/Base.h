#pragma once

#include "DisplayableObject.h"
#include "ObjLoader.h"

/*
This is a class that should dispaly our lamp with they rough rigid body
transform between our key frames
Here is a more complex example of the effects that can be achieved:
http://www.youtube.com/watch?v=cdtHSyfcSDs
*/

class Base :
	public DisplayableObject
{
public:
	Base();
	~Base() {};

	void Display();

private:

	void DrawBase();
	
	ObjLoader* objBase;
	ObjLoader* objBox;
	ObjLoader* objPlantForm;


	GLint baseTex;
	GLint plantFormTex;

	

};

#pragma once
