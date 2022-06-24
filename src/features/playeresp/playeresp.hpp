#pragma once

#include "../src/garrysmod.hpp"

class PlayerESP
{
public:
	bool Init();

private:
	Hook* hook = nullptr;
};

extern PlayerESP playeresp;