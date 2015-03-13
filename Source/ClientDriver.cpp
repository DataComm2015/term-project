//> In the main file
#include "AppWindow.h"
#include "Logic/GameScene.h"
// include the separate scene file

int main()
{
	GameScene scene1;

	AppWindow::getInstance().addScene(&scene1);

	AppWindow::getInstance().run();

	return 0;
}