#pragma once

#include "myudpsocket.hpp"

class UdpServer : public MyUdpSocket{
private:
	sockaddr_in m_clientaddr;
public:

	bool initServer(const int port);

	bool udpRecv(char* buffer, const int s_timeout=0);

	bool udpSend(const char* buffer);
};
