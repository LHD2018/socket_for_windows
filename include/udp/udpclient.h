#pragma once

#include "myudpsocket.hpp"

class UdpClient : public MyUdpSocket {

public:

	void initClient(const char* server_ip, const int server_port);

	bool udpRecv(char* buffer, const int s_timeout =0);

	bool udpSend(const char* buffer);

};
