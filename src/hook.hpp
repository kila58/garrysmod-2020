#pragma once

#include "definitions.hpp"

// meep's hook

#define ushort_max (unsigned short(-1))

typedef char* vtindex; // sizeof(pointer) with ability to add numbers and shit 
#ifndef offset
#define offset(x,y) ((char *)(x) - (char *)(y))
#endif

class Hook
{
private:
	vtindex* original_vt;
	vtindex* new_vt;
	void** hooked;
	uint index;
	void* func;
public:
	Hook(void* object, uint i, void* func) : index(i), func(func)
	{
		original_vt = *(vtindex**)object;
		vtindex* last_index = original_vt;
		while (*last_index++);

		unsigned int size = offset(last_index, original_vt) / sizeof(*last_index);

		new_vt = new vtindex[size];
		while (--last_index >= original_vt)
			new_vt[offset(last_index, original_vt) / sizeof(*last_index)] = *last_index;

		*(vtindex**)object = new_vt;

		hooked = (void**)object;
	}
	vtindex& getold(unsigned short index) { return original_vt[index]; }
	vtindex& get(unsigned short index) { return new_vt[index]; }
	void* ReplaceVirtual()
	{
		get(index) = (vtindex)func;

		return getold(index);
	}
	void RevertVirtual()
	{
		get(index) = getold(index);
	}
	~Hook()
	{
		*hooked = original_vt;
		delete[] new_vt;
	}
};