#pragma once


#include "mysocket.hpp"

class TcpServer :public MySocket {
public:
	WSADATA m_wsa_data;
	SOCKET m_sock;
	SOCKET m_clsock;
	sockaddr_in m_sock_addr;
	SOCKADDR m_claddr;

	TcpServer();
	bool tcpInit(const int port);
	bool tcpAccept();
	void tcpClose();
	~TcpServer();
};