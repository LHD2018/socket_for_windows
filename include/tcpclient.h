#pragma once

#include "mysocket.hpp"

class TcpClient : public MySocket {
public:
	WSADATA m_wsa_data;
	SOCKET m_sock;
	sockaddr_in m_sock_addr;

	TcpClient();
	bool tcpInit(const char* server_ip, const int port);
	void tcpClose();
	~TcpClient();
};

