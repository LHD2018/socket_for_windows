#include "tcp/tcpserver.h"

TcpServer::TcpServer() {
	m_clientsock = -1;
}

bool TcpServer::tcpInit(const int port) {
	WSAStartup(MAKEWORD(2, 2), &m_wsa_data);
	if (m_sock > 0 || m_clientsock > 0) {
		tcpClose();
	}
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&m_serveraddr, 0, sizeof(m_serveraddr));
	m_serveraddr.sin_family = AF_INET;
	m_serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_serveraddr.sin_port = htons(port);
	if (bind(m_sock, (SOCKADDR*)&m_serveraddr, sizeof(SOCKADDR)) != 0) return false;
	if (listen(m_sock, 20) != 0) return false;
	return true;
}

bool TcpServer::tcpAccept() {
	int n_size = sizeof(m_clientaddr);
	if ((m_clientsock = accept(m_sock, (SOCKADDR*)&m_clientaddr, &n_size)) < 0) return false;
	return true;
}

void TcpServer::tcpClose() {
	closesocket(m_clientsock);
	closesocket(m_sock);
}

TcpServer::~TcpServer() {
	tcpClose();
}