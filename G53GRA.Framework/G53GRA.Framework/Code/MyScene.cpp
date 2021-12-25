

#include "MyScene.h"

#include "Yard.h"
#include "ObjLoader.h"
#include "Skybox.h"
#include "Water.h"
#include "Tree.h"
#include "Bird.h"
#include "Table.h"
#include "Butterfly.h"
#include "Lamp.h"
#include "Boat.h"
#include "Ballon.h"
#include "Base.h"
#include "FirePlace.h"
#include "Light.h"
#include "Carrot.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// add skybox to the scene
	Skybox* skb = new Skybox();
	skb->size(500.0f);
	AddObjectToScene(skb);

	//
#ifdef __APPLE__
	Water* water = new Water(20, 20, "./water.bmp");
#else
	Water* water = new Water(20, 20, "./Textures/water.bmp");
#endif

	water->position(0.0f, -180.0f, 0.0f);;
	water->size(50000.0f);
	AddObjectToScene(water);

	 //add yard to the scene
	Yard* yard = new Yard();
	AddObjectToScene(yard);

	// add Butterfly to the scene
	Butterfly* bf = new Butterfly();
	bf->setNumbers(2);
	AddObjectToScene(bf);

	//add Boat
	Boat* boat = new Boat();
	//boat->position(300.0f, 0.0f, 170.0f);
	AddObjectToScene(boat);

	// add tree
	Tree* t = new Tree();
	t->setReplaceString('f', "ff[-f+<<+f][+f+&f][>f+&f][< f + &f]");
	t->position(400.0f, -20.0f, 150.0f);
	t->size(120.f, 80.0f, 60.0f);
	//t->position(400.0f, 0.0f, 170.0f);
	//t->size(12.f, 18.0f, 6.0f);
	AddObjectToScene(t);

	// add carrot
	Carrot* carrot = new Carrot();
	carrot->position(-200.0f, 20.0f, 300.0f);
	carrot->size(15.0f, 15.0f, 15.0f);
	//t->position(400.0f, 0.0f, 170.0f);
	//t->size(12.f, 18.0f, 6.0f);
	AddObjectToScene(carrot);

	// add bird to the scene
	Bird* bird = new Bird();
	bird->position(-1200.0f, 380.0f, -300.0f);
	bird->size(6.f);
	AddObjectToScene(bird);

	// add tower to the scene
	Ballon* ballon = new Ballon();
	AddObjectToScene(ballon);

	// add base to the scene
	Base* base = new Base();
	AddObjectToScene(base);

	// add table to the scene
	Table* table = new Table();
	AddObjectToScene(table);

	// add fireplace to the scene
	FirePlace* fireplace = new FirePlace();
	AddObjectToScene(fireplace);



	// add light to the scene
	Light* light = new Light();
	//light->position(300.0f, 0.0f, 170.0f);
	AddObjectToScene(light);



}



/// set the perspective of camera
void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 50000.0);
}
