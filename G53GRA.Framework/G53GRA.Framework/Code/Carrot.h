#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "ObjLoader.h"
#include "Input.h"

class Carrot :
    public DisplayableObject,
    public Animation,
    public Input
{
public:
    Carrot();                                 // constructor
    ~Carrot() { };                            // destructor

    void Display();                         // overloaded virtual display function
    void Update(const double& deltaTime);
    void HandleKey(unsigned char key, int state, int x, int y);

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

    ObjLoader* objCarrotLeaf;
    ObjLoader* objCarrot;
    
    GLint carrotLeafTex;
    GLint carrotTex;

    double move;

};

#pragma once
