#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include <vector>
#include <string>
using namespace std;

class ObjLoader {

public:

	ObjLoader(string filename);
	//void Init();
	void Draw(GLint texID);
	void Draw();

private:

	//GLint lastFrameTime;
	//GLint animationLastingTime;

	vector<vector<GLfloat>>vSets;
	vector<vector<GLint>>fSets;
	vector<vector<GLint>>VTIndexSets;
	vector<vector<GLint>>VNIndexSets;
	vector<vector<GLfloat>>vnSets;
	vector<vector<GLfloat>>vtSets;

};


