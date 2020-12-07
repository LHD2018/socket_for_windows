#include "tcp/tcpclient.h"


bool TcpClient::tcpInit(const char* server_ip, const int port) {
	WSAStartup(MAKEWORD(2, 2), &m_wsa_data);		// 加载DLL
	if (m_sock > 0) {
		tcpClose();
	}
	m_sock = socket(AF_INET, SOCK_STREAM, 0);		// 创建sock
	memset(&m_serveraddr, 0, sizeof(m_serveraddr));	
	m_serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, server_ip, &m_serveraddr.sin_addr);	// 将server_ip转网络字节序并传入sin_addr
	m_serveraddr.sin_port = htons(port);
	if (connect(m_sock, (sockaddr*)&m_serveraddr, sizeof(m_serveraddr)) == SOCKET_ERROR) return false;
	return true;
}

void TcpClient::tcpClose() {
	closesocket(m_sock);
	
}

TcpClient::~TcpClient() {
	tcpClose();
}