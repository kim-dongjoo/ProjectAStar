#include <iostream>
#include "Engine.h"
#include "Demo/DemoLevel.h"
#include "Level/SokobanLevel.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine engine;
	// engine.AddLevel(new DemoLevel());
	engine.AddLevel(new SokobanLevel());
	engine.Run();
}