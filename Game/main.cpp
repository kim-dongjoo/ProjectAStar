#include <iostream>
#include "Engine.h"
#include "DemoLevel.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine engine;
	engine.AddLevel(new DemoLevel());
	engine.Run();
}