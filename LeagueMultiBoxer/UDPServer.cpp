#include "UDPServer.h"


#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "keyCodes.h"

int UDPServer::startServer()
{
	long rc;
	char buf[256];
	char buf2[300];
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

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = ADDR_ANY;

	rc = bind(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (rc == SOCKET_ERROR)
	{
		printf("Fehler: bind, fehler code: %d\n", WSAGetLastError());
		return 1;
	}
	else
	{
		printf("Socket an Port %d gebunden\n", port);
	}

	while (1)
	{
		rc = recvfrom(sock, buf, 256, 0, (SOCKADDR*)&remoteAddr, &remoteAddrLen);
		if (rc == SOCKET_ERROR)
		{
			printf("Fehler: recvfrom, fehler code: %d\n", WSAGetLastError());
			return 1;
		}
		else
		{
			buf[rc] = '\0';
		}

		std::string recvData = buf;
		int newX = std::stoi(recvData.substr(0, recvData.find('|')));
		int newY = std::stoi(recvData.substr(recvData.find('|') + 1, recvData.rfind('|')));
		SetCursorPos(newX, newY);
		printf("%s\n", recvData.c_str());

		checkForButtonPresses(&recvData);
	}
	return 0;
}

void UDPServer::checkForButtonPresses(std::string* str)
{
	if (str->find('Q') != std::string::npos)
	{
		pressKeyWithSendInput(VK_Q);
	}
	if (str->find('W') != std::string::npos)
	{
		pressKeyWithSendInput(VK_W);
	}
	if (str->find('E') != std::string::npos)
	{
		pressKeyWithSendInput(VK_E);
	}
	if (str->find('R') != std::string::npos)
	{
		pressKeyWithSendInput(VK_R);
	}
	if (str->find('D') != std::string::npos)
	{
		pressKeyWithSendInput(VK_D);
	}
	if (str->find('F') != std::string::npos)
	{
		pressKeyWithSendInput(VK_F);
	}
	if (str->find('T') != std::string::npos)
	{
		pressKeyWithSendInput(VK_T);
	}
	if (str->find('mr') != std::string::npos)
	{
		pressKeyWithSendInput(VK_T);
	}
}
