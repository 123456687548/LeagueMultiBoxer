#include "UDPClient.h"
#include "UDPServer.h"

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
