#pragma once

#include "Level/Level.h"

class SokobanLevel : public Level
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

private:
	void ReadMapFile(const char* filename);
};