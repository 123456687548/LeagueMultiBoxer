#pragma once

#include <string>
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

private:
	void checkForButtonPresses(std::string* str);

	void sendMouseClick()
	{
		
	}
	
	void sendKeyWithSendInput(int key, bool up)
	{
		INPUT input = {0};
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = key;
		input.ki.dwFlags = 0;
		if (up) input.ki.dwFlags |= KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(input));
	}

	void pressKeyWithSendInput(WORD key)
	{
		sendKeyWithSendInput(key, false);
		sendKeyWithSendInput(key, true);
	}
};
