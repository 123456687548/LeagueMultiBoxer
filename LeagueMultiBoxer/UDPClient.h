#pragma once

#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "Ws2_32.lib")

class UDPClient
{
private:
	SOCKET sock;
	WORD port;
	char* ipAddress;
public:
	UDPClient(int port, char* ipAddress) : port(port), ipAddress(ipAddress){}
	int startClient();
};

