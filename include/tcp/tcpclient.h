#pragma once

#include "mytcpsocket.hpp"

class TcpClient : public MyTcpSocket {
public:
	
	bool tcpInit(const char* server_ip, const int port);
	void tcpClose();
	~TcpClient();
};

