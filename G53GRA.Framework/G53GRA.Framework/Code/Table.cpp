#include "Table.h"
#include "iostream"
#include "ObjLoader.h"

Table::Table()
{
	texTable = Scene::GetTexture("./Textures/plantForm.bmp");
	pillowTex = Scene::GetTexture("./Textures/texture2.bmp");
	objChair = new ObjLoader("./data/chair.obj");
	objBed = new ObjLoader("./data/bed.obj");
	objPillow = new ObjLoader("./data/pillow.obj");
	//objAnchor = new ObjLoader("./data/anchor.obj");
}

void Table::DrawTable()
{
	glPushMatrix();

	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(30.0f, 30.0f, 2.0f);
	DrawPiece();

	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(15.0f, 2.0f, 2.0f);
	glTranslatef(-1.0f, 13.0f, 10.0f);
	DrawPiece();

	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(15.0f, 2.0f, 2.0f);
	glTranslatef(-1.0f, -13.0f, 10.0f);
	DrawPiece();

	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(15.0f, 2.0f, 2.0f);
	glTranslatef(-1.0f, 13.0f, -10.0f);
	DrawPiece();

	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(15.0f, 2.0f, 2.0f);
	glTranslatef(-1.0f, -13.0f, -10.0f);
	DrawPiece();
	glPopMatrix();
}


void Table::DrawPiece()
{
	// Enable Texturing
	glEnable(GL_TEXTURE_2D);

	// Enable setting the colour of the material the cube is made from
	// as well as the material for blending.
	glEnable(GL_COLOR_MATERIAL);

	// Tell openGL which texture buffer to use

	glBindTexture(GL_TEXTURE_2D, texTable);
	glBegin(GL_QUADS);

	// draw the front sky

	// set the colour of the front sky
	glColor3f(1.0f, 1.0f, 1.0f);

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

	glBindTexture(GL_TEXTURE_2D, texTable);
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

	glBindTexture(GL_TEXTURE_2D, texTable);
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

	glBindTexture(GL_TEXTURE_2D, texTable);
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

	glBindTexture(GL_TEXTURE_2D, texTable);
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

	glBindTexture(GL_TEXTURE_2D, texTable);
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

void Table::Display()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	//glTranslatef(0.0f, 40.0f, 500.0f);
	glTranslatef(155.0f, 40.0f, -70.0f);
	glScalef(3.0f, 2.0f, 2.0f);
	DrawTable();

	glPushMatrix();
	glTranslatef(-15.0f, -30.0f, -130.0f);
	glScalef(12.0f, 12.0f, 17.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	objChair->Draw(texTable);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-45.0f, 70.0f, 15.0f);
	glScalef(8.0f, 8.0f, 15.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	objBed->Draw(texTable);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-28.0f, 52.0f, -180.0f);
	glScalef(7.5f, 7.5f, 13.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	objPillow->Draw(pillowTex);

	glPopMatrix();
	glPushMatrix();
	//glTranslatef(-28.0f, 72.0f, -180.0f);
	//glScalef(7.5f, 7.5f, 13.0f);
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(20.0f, 20.0f, 20.0f);
	glRotatef(-4.0f, 1.0f, 0.0f, 0.0f);
	//objAnchor->Draw();
	glPopMatrix();

	glPopAttrib();

}

