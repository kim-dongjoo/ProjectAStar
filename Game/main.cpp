#include <iostream>
#include "Engine.h"
#include "Math/Vector2.h"

int main()
{
	Vector2 a(10, 20);
	Vector2 b(20, 30);
	std::cout << (a + b).ToString() << "\n";


	Engine engine;
	engine.Run();
}