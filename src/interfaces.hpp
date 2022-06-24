#pragma once

#include <string>

typedef void* (*tCreateInterface)(const char* name, int* returncode);

class Interfaces
{
public:
	bool Init();
	template<typename T> T GetInterface(const char* module, const char* name);
};

extern Interfaces interfaces;