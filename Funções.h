#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

void MsgBoxAddy(DWORD addy)
{

	char szBuffer[1024];
	sprintf_s(szBuffer, "Address: %02x", addy); // 
	MessageBox(NULL, szBuffer, "Attached nessa porra", MB_OK);

}

MODULEINFO GetModuleInfo(const char* szModule)
{
	MODULEINFO modelinformation = { 0 };
	HMODULE hModule = GetModuleHandle(szModule);
	if (hModule == 0)
		return modelinformation;
	GetModuleInformation(GetCurrentProcess(), hModule, &modelinformation, sizeof(MODULEINFO));
	return modelinformation;
}

void WTM(uintptr_t AddressToWrite, const char* ValueToWrite, int bNum)
{
	unsigned long OldProtection;


	VirtualProtect((LPVOID)(AddressToWrite), bNum, PAGE_EXECUTE_READWRITE, &OldProtection); // 0X40 = PAGE_EXECUTE_READWRITE - Enables execute, read-only, or read/write access to the committed region of pages.


	memcpy((LPVOID)AddressToWrite, ValueToWrite, bNum);

	VirtualProtect((LPVOID)(AddressToWrite), bNum, OldProtection, NULL);

}



DWORD FindPattern(const char* module, const char* Pattern, const char* mask) // 
{

	MODULEINFO modelinformation = GetModuleInfo(module);


	DWORD BASE = (DWORD)modelinformation.lpBaseOfDll;
	DWORD SIZE = (DWORD)modelinformation.SizeOfImage;

	DWORD patternLength = (DWORD)strlen(mask);

	for (DWORD i = 0; i < SIZE - patternLength; i++)
	{
		bool found = true;
		for (DWORD j = 0; j < patternLength; j++)
		{
			found &= mask[j] == '?' || Pattern[j] == *(char*)(BASE + i + j);
		}

		if (found)
		{
			return BASE + i;
		}
	}
	return NULL;
}


