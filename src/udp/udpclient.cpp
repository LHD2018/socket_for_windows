#include "udp/udpclient.h"

void UdpClient::initClient(const char* server_ip, const int server_port) {
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);

	if (m_sock > 0) {
		udpClose();
	}
	m_sock = socket(PF_INET, SOCK_DGRAM, 0);
	m_addr_len = sizeof(SOCKADDR);
	memset(&m_serveraddr, 0, sizeof(m_serveraddr));
	m_serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, server_ip, &m_serveraddr.sin_addr);
	m_serveraddr.sin_port = htons(server_port);
}

bool UdpClient::udpRecv(char* buffer, const int s_timeout) {
	

	return udpRead(buffer, (SOCKADDR*)&m_serveraddr, s_timeout);
}

bool UdpClient::udpSend(const char* buffer) {
	
	return udpWrite(buffer, (SOCKADDR*)&m_serveraddr);
}
