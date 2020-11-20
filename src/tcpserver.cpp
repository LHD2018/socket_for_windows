#include "tcpserver.h"

TcpServer::TcpServer() {
	m_sock = -1;
	m_clsock = -1;
}

bool TcpServer::tcpInit(const int port) {
	WSAStartup(MAKEWORD(2, 2), &m_wsa_data);
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&m_sock_addr, 0, sizeof(m_sock_addr));
	m_sock_addr.sin_family = AF_INET;
	m_sock_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_sock_addr.sin_port = htons(port);
	if (bind(m_sock, (SOCKADDR*)&m_sock_addr, sizeof(SOCKADDR)) != 0) return false;
	if (listen(m_sock, 20) != 0) return false;
	return true;
}

bool TcpServer::tcpAccept() {
	int n_size = sizeof(m_claddr);
	if ((m_clsock = accept(m_sock, (SOCKADDR*)&m_claddr, &n_size)) < 0) return false;
	return true;
}

void TcpServer::tcpClose() {
	closesocket(m_clsock);
	closesocket(m_sock);
	WSACleanup();
}

TcpServer::~TcpServer() {
	tcpClose();
}