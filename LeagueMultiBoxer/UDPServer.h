#pragma once

#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "Ws2_32.lib")

class UDPServer
{
private:
	SOCKET sock;
	WORD port;
public:
	UDPServer(int port): port(port)
	{
	}

	int startServer();
};
