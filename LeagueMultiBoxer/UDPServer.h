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

	void sendKeyWithScanCode(WORD key, bool up)
	{
		INPUT input = {0};
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = key;
		input.ki.dwFlags = KEYEVENTF_SCANCODE;
		if (up) input.ki.dwFlags |= KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(input));
	}

	void pressKeyWithScanCode(WORD key)
	{
		sendKeyWithScanCode(key, false);
		sendKeyWithScanCode(key, true);
	}

	void sendMousePressWithSendInput(bool right, bool up)
	{
		INPUT input = {0};

		POINT p;
		if (!GetCursorPos(&p))
		{
			return;
		}

		input.type = INPUT_MOUSE;
		input.mi.dx = p.x;
		input.mi.dy = p.y;
		input.mi.mouseData = 0;
		if (up)
		{
			if (right)
			{
				input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			}
			else
			{
				input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			}
		}
		else
		{
			if (right)
			{
				input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
			}
			else
			{
				input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			}
		}
		SendInput(1, &input, sizeof(input));
	}

	void pressMouseButton(bool right)
	{
		sendMousePressWithSendInput(right, false);
		sendMousePressWithSendInput(right, true);
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
