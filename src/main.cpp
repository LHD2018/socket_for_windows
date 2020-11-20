#include "tcpserver.h"
#include "tcpclient.h"
#include <thread>

void pthClient() {
	TcpClient client;
	client.tcpInit("127.0.0.1", 10127);
	for (int i = 0; i < 40; i++) {
		client.tcpSend(client.m_sock, "hello");
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		client.tcpRecv(client.m_sock, buffer);
		cout << "client recv:" << buffer << endl;
		Sleep(1000);
	}
}

int main(int argc, char** argv) {
	TcpServer server;
	server.tcpInit(10127);
	thread cl_thread(pthClient);
	cl_thread.detach();
	server.tcpAccept();
	while (true) {
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		server.tcpRecv(server.m_clsock, buffer);
		cout << "server recv:" << buffer << endl;
		strcpy_s(buffer, "ok");
		server.tcpSend(server.m_clsock, buffer);
	}

	return 0;
}

