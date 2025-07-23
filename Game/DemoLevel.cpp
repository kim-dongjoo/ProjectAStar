#include "DemoLevel.h"
#include "TestActor.h"

DemoLevel::DemoLevel()
{
	SpawnActor(new TestActor());
}