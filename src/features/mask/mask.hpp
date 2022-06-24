#pragma once

#include "../src/garrysmod.hpp"

class Mask
{
public:
	bool Init();

private:
	Hook* hook = nullptr;
};

extern Mask mask;