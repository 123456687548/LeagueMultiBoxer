#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "UDPClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

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
		
		//rc = sendto(s, buf, strlen(buf), 0, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
		POINT p;
		if (!GetCursorPos(&p))
		{
			// cursor pos error
		}


		std::string str = std::to_string(p.x) + "|" + std::to_string(p.y);
		const char* mousePos = str.c_str();
		strcpy_s(buf, mousePos);

		rc = send(sock, buf, strlen(buf), 0);

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
