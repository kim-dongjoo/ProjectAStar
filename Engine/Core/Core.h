#pragma once

#if BuildEngineDLL
#define Engine_API __declspec(dllexport)
#elif
#define Engine_API __declspec(dllimport)
#endif