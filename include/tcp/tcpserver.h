#pragma once


#include "mytcpsocket.hpp"

class TcpServer :public MyTcpSocket {
public:

	SOCKET m_clientsock;
	SOCKADDR m_clientaddr;

	TcpServer();
	bool tcpInit(const int port);
	bool tcpAccept();
	void tcpClose();
	~TcpServer();
};