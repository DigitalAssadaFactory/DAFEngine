#include "Engine.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR ipCmdLine, int nCmdShow)
{
	Engine engine("DigitalAssadaFactory", 800, 600);

	engine.StartUp();
	engine.Run();
	engine.ShutDown();
	
	return 0;
}