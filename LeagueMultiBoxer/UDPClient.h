#pragma once

#include <string>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "Ws2_32.lib")

class UDPClient
{
private:
	SOCKET sock;
	WORD port;
	char* ipAddress;
	bool wasQPressed;
	bool wasWPressed;
	bool wasEPressed;
	bool wasRPressed;
	bool wasTPressed;
	bool wasDPressed;
	bool wasFPressed;
	bool wasYPressed;
	bool wasXPressed;
public:
	UDPClient(int port, char* ipAddress) : port(port), ipAddress(ipAddress)
	{
		wasQPressed = false;
		wasWPressed = false;
		wasEPressed = false;
		wasRPressed = false;
		wasTPressed = false;
		wasDPressed = false;
		wasFPressed = false;
		wasYPressed = false;
	}

	int startClient();
	std::string checkKeyState();
};
