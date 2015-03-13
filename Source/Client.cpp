//> In the main file
#include "AppWindow.h"
#include "Usage.cpp"
// include the separate scene file

int main()
{
	StartScreen scene1;

	AppWindow::getInstance().addScene(&scene1);

	AppWindow::getInstance().run();

	return 0;
}
