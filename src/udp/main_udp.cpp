#include "udp/udpserver.h"
#include "udp/udpclient.h"

#include <thread>

unsigned int WINAPI pthClient(void *) {
	UdpClient client;
	client.initClient("127.0.0.1", 10227);
	for (int i = 0; i < 100; i++) {
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "hello %d", i);
		if (client.udpSend(buffer) == false) {
			cout << "断开" << endl;
			break;
		}
		memset(buffer, 0, sizeof(buffer));
		if (client.udpRecv(buffer, 10) == false) {
			break;
		}
		cout << buffer << endl;
		Sleep(1000);
	}
	return 0;
}

int main(int argc, char** argv) {
	UdpServer server;
	if (server.initServer(10227) == false) {
		cout << "服务端初始化失败" << endl;
		return -1;
	}

	HANDLE pth_client = (HANDLE)_beginthreadex(NULL, 0, pthClient, 0, 0, NULL);

	while (true) {
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));

		if (server.udpRecv(buffer) == false) {
			continue;
		}
		cout << buffer << endl;
		if (server.udpSend("udp ok") == false) {
			continue;
		}

	}
	system("pause");
	CloseHandle(pth_client);
	return 0;
}