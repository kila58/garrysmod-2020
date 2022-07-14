#pragma once

typedef uintptr_t ptr;
typedef unsigned int uint;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

class Memory
{
public:
	static HMODULE __stdcall GetModuleBaseAddress(std::string modulename);
	static PIMAGE_NT_HEADERS GetNTHeader(HMODULE hmModule);

	static std::string HexToBytes(std::string hex);
	static ptr SigScan(const char* pattern, const char* module);
};