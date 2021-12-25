#pragma once

#include "DisplayableObject.h"
#include "ObjLoader.h"

#include <string>

class Table :
	public DisplayableObject
{
public:
	Table();
	~Table() {}

	void Display();

private:
	void DrawPiece();
	void DrawTable();

	GLint texTable;
	GLint pillowTex;
	ObjLoader* objChair;
	ObjLoader* objBed;
	ObjLoader* objPillow;
	//ObjLoader* objAnchor;

};

