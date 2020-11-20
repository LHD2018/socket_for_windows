#include "tcpclient.h"

TcpClient::TcpClient() {
	m_sock = -1;
}

bool TcpClient::tcpInit(const char* server_ip, const int port) {
	WSAStartup(MAKEWORD(2, 2), &m_wsa_data);		// 加载DLL
	m_sock = socket(AF_INET, SOCK_STREAM, 0);		// 创建sock
	memset(&m_sock_addr, 0, sizeof(m_sock_addr));	
	m_sock_addr.sin_family = AF_INET;
	inet_pton(AF_INET, server_ip, &m_sock_addr.sin_addr);	// 将server_ip转网络字节序并传入sin_addr
	m_sock_addr.sin_port = htons(port);
	if (connect(m_sock, (sockaddr*)&m_sock_addr, sizeof(m_sock_addr)) == SOCKET_ERROR) return false;
	return true;
}

void TcpClient::tcpClose() {
	closesocket(m_sock);
	WSACleanup();
}

TcpClient::~TcpClient() {
	tcpClose();
}