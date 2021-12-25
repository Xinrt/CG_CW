/**
* Entry file to framework. Should not edit this file, though to change window
* size, adjust parameters in creastion of new scene
* <p>
* {@code new MyScene(argc, argv, "title", (const int)width, (const int)height)}
* @author wil
* @date 09/02/16
*/
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "MyScene.h"
#include "Camera.h"

/**
 * Entry method, takes command line arguments and creates new Scene engine to
 * render your G53GRA Coursework
 *
 * @see MyScene
 */
int main(int argc, char* argv[])
{
	sf::Music music;
	if (!music.openFromFile("./data/audio/sound.wav"))
		return -1;
	music.play();
	music.setLoop(true);

	// Create new instance of MyScene - the OpenGL context on which your 
	// coursework is built
	MyScene* scene = NULL;
	scene = new MyScene(argc, argv, "G53GRA", static_cast<const int>(1000), static_cast<const int>(600));
	// Begin the main GL loop
	scene->Run();

	//play music
	//mciSendString(L"open ./data/audio/sea.wav", 0, 0, 0);
	//mciSendString("play MYBGM repeat", 0, 0, 0);
	//PlaySound(LPCSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	//PlaySound(LPCSTR"./data/audio/sea.wav", NULL, SND_ASYNC);
	//while(true) {}



	

	// On exit, clean up and return success (0x0)
	delete scene;
	return 0;
}
