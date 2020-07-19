#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "UDPClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "keyCodes.h"

int UDPClient::startClient()
{
	long rc;
	char buf[256];
	SOCKADDR_IN addr;
	SOCKADDR_IN remoteAddr;
	int remoteAddrLen = sizeof(SOCKADDR_IN);

	WSADATA wsa;
	rc = WSAStartup(MAKEWORD(2, 0), &wsa);

	if (rc != 0)
	{
		printf("Fehler: startWinsock, fehler code: %d\n", rc);
		return 1;
	}
	else
	{
		printf("Winsock gestartet!\n");
	}

	//UDP Socket erstellen
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
	{
		printf("Fehler: Der Socket konnte nicht erstellt werden, fehler code: %d\n", WSAGetLastError());
		return 1;
	}
	else
	{
		printf("UDP Socket erstellt!\n");
	}

	// addr vorbereiten
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ipAddress);

	rc = connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));

	// Daten austauschen
	while (1)
	{
		POINT p;
		if (!GetCursorPos(&p))
		{
			// cursor pos error
		}


		std::string str = std::to_string(p.x) + "|" + std::to_string(p.y) + "|" + checkKeyState();
		const char* mousePos = str.c_str();
		//strcpy_s(buf, mousePos);

		rc = send(sock, mousePos, strlen(mousePos), 0);

		if (rc == SOCKET_ERROR)
		{
			printf("Fehler: sendto, fehler code: %d\n", WSAGetLastError());
			return 1;
		}
		else
		{
			printf("%d Bytes gesendet!\n", rc);
		}
	}

	return 0;
}

std::string UDPClient::checkKeyState()
{
	std::string retVal;
	if (GetAsyncKeyState(VK_Q) & 1)
	{
		if (!wasQPressed)
		{
			retVal += "Q";
			wasQPressed = true;
		}
	}
	else
	{
		wasQPressed = false;
	}

	if (GetAsyncKeyState(VK_W) & 1)
	{
		if (!wasWPressed)
		{
			retVal += "W";
			wasWPressed = true;
		}
	}
	else
	{
		wasWPressed = false;
	}

	if (GetAsyncKeyState(VK_E) & 1)
	{
		if (!wasEPressed)
		{
			retVal += "E";
			wasEPressed = true;
		}
	}
	else
	{
		wasEPressed = false;
	}

	if (GetAsyncKeyState(VK_R) & 1)
	{
		if (!wasRPressed)
		{
			retVal += "R";
			wasRPressed = true;
		}
	}
	else
	{
		wasRPressed = false;
	}

	if (GetAsyncKeyState(VK_D) & 1)
	{
		if (!wasDPressed)
		{
			retVal += "D";
			wasDPressed = true;
		}
	}
	else
	{
		wasDPressed = false;
	}

	if (GetAsyncKeyState(VK_F) & 1)
	{
		if (!wasFPressed)
		{
			retVal += "F";
			wasFPressed = true;
		}
	}
	else
	{
		wasFPressed = false;
	}

	if (GetAsyncKeyState(VK_T) & 1)
	{
		if (!wasTPressed)
		{
			retVal += "T";
			wasTPressed = true;
		}
	}
	else
	{
		wasTPressed = false;
	}

	if (GetAsyncKeyState(VK_Y) & 1)
	{
		if (!wasYPressed)
		{
			retVal += "ml";
			wasYPressed = true;
		}
	}
	else
	{
		wasYPressed = false;
	}

	if (GetAsyncKeyState(VK_X) & 1)
	{
		if (!wasXPressed)
		{
			retVal += "mr";
			wasXPressed = true;
		}
	}
	else
	{
		wasXPressed = false;
	}
	return retVal;
}
