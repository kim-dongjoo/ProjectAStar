#include "TestActor.h"
#include <iostream>

void TestActor::Tick(float deltaTime)
{
	// Actor::Tick(deltaTime);
	super::Tick(deltaTime);

	std::cout 
		<< "TestACtor::Tick. FPS: "
		<< (1.0f / deltaTime)
		<< std::endl;
}
