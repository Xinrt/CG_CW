#pragma once
#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>
#include <string>
#include <vector>;
using namespace std;
class Tree :
    public DisplayableObject //making tree a displayable object
{
public:
    Tree();                                 // constructor
    ~Tree() { };                            // destructor
    void Display();                         // overloaded virtual display function
    void addReplaceString(char flag, string str);
    void setReplaceString(char flag, string str);
    void setNumIter(unsigned int num);
    void setInitString(string str);
    string sequence; //sequence to draw tree
    float angle;
private:
    void branch();       // draw branch function
    void getSequence();  // obtain sequence for drawing tree    

    int iter;
    string init;
    vector<string> change;
    vector<char> flags;
    bool toTexture;
    GLuint bark;

};

#pragma once
