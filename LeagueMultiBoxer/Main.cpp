#include "keyCodes.h"
#include "UDPClient.h"
#include "UDPServer.h"

void sendKeyWithSendMessage(HWND window, WORD key, char letter)
{
	SendMessageA(window, WM_KEYDOWN, key, 0);
	if (letter != 0) SendMessageA(window, WM_CHAR, letter, 1);
	SendMessageA(window, WM_KEYUP, key, 1);
}

int main(int argc, char** argv)
{
	switch (argc)
	{
	case 2:
		{
			UDPServer server{atoi(argv[1])};
			server.startServer();
			break;
		}
	case 3:
		{
			UDPClient client{atoi(argv[1]), argv[2]};
			client.startClient();
			break;
		}
	default:
		return 1;
	}
}
