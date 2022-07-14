#include "garrysmod.hpp"

#include "memory.hpp"

HMODULE __stdcall Memory::GetModuleBaseAddress(std::string modulename)
{
	PEB* peb = nullptr;
	LIST_ENTRY* listentry = nullptr;
	LDR_DATA_TABLE_ENTRY* datatablentry = nullptr;

	peb = (PPEB)__readgsqword(0x60);

	if (!peb)
		return nullptr;

	datatablentry = (PLDR_DATA_TABLE_ENTRY)peb->Ldr->InMemoryOrderModuleList.Flink;
	listentry = peb->Ldr->InMemoryOrderModuleList.Flink;

	do
	{
		if (lstrcmpiW(datatablentry->FullDllName.Buffer, std::wstring(modulename.begin(), modulename.end()).c_str()) == 0)
			return (HMODULE)datatablentry->Reserved2[0];

		listentry = listentry->Flink;
		datatablentry = (PLDR_DATA_TABLE_ENTRY)(listentry->Flink);

	} while (listentry != peb->Ldr->InMemoryOrderModuleList.Flink);

	return nullptr;
}

PIMAGE_NT_HEADERS Memory::GetNTHeader(HMODULE module)
{
	if (!module)
		return nullptr;

	IMAGE_DOS_HEADER* dosheader = reinterpret_cast<IMAGE_DOS_HEADER*>(module);

	if (dosheader->e_magic != IMAGE_DOS_SIGNATURE)
		return nullptr;

	PIMAGE_NT_HEADERS ntheader = *(PIMAGE_NT_HEADERS*)(module + dosheader->e_lfanew);

	if (ntheader->Signature != IMAGE_NT_SIGNATURE)
		return nullptr;

	return ntheader;
}

std::string Memory::HexToBytes(std::string hex)
{
	std::string bytes;

	hex.erase(std::remove_if(hex.begin(), hex.end(), isspace), hex.end());

	for (uint i = 0; i < hex.length(); i += 2)
	{
		if ((uchar)hex[i] == '?')
		{
			bytes += '?';
			i -= 1;

			continue;
		}

		uchar byte = (uchar)std::strtol(hex.substr(i, 2).c_str(), nullptr, 16);
		bytes += byte;
	}

	return bytes;
}

ptr Memory::SigScan(const char* pattern, const char* module)
{
	HMODULE mod = GetModuleBaseAddress(module);
	MODULEINFO info;
	GetModuleInformation(GetCurrentProcess(), mod, &info, sizeof(info));

	uchar* base = (uchar*)mod;

	std::string signature = HexToBytes(pattern);

	uchar first = (uchar)signature.at(0);
	uchar* end = (base + info.SizeOfImage) - signature.length();

	for (; base < end; ++base)
	{
		if (*base != first)
			continue;

		uchar* bytes = base;
		uchar* sig = (uchar*)signature.c_str();

		for (; *sig; ++sig, ++bytes)
		{
			if (*sig == '?')
				continue;

			if (*bytes != *sig)
				goto end;
		}

		return (ptr)base;

	end:;
	}

	return NULL;
}
