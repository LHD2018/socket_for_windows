#pragma once

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class MyUdpSocket {
protected:
	WSADATA m_wsa_data;
	SOCKET m_sock;
	int m_addr_len;
	sockaddr_in m_serveraddr;
public:
	MyUdpSocket() {
		m_sock = -1;
		m_addr_len = 0;
	}

	bool udpRead(char *buffer, SOCKADDR *from_addr, const int s_timeout=0) {
		if (m_sock == -1) return false;

		if (s_timeout > 0) {
			fd_set tmpfd;

			FD_ZERO(&tmpfd);
			FD_SET(m_sock, &tmpfd);

			struct timeval timeout;
			timeout.tv_sec = s_timeout;
			timeout.tv_usec = 0;

			if (select((int)m_sock + 1, &tmpfd, 0, 0, &timeout) <= 0) return false;
		}

		if (recvfrom(m_sock, buffer, sizeof(buffer), 0, from_addr, &m_addr_len) == -1) return false;

		return true;
	}

	bool udpWrite(const char* buffer, SOCKADDR* to_addr) {
		if (m_sock == -1) return false;

		fd_set tmpfd;

		FD_ZERO(&tmpfd);
		FD_SET(m_sock, &tmpfd);

		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		if (select((int)m_sock + 1, 0, &tmpfd, 0, &timeout) <= 0) return false;

		if (sendto(m_sock, buffer, sizeof(buffer), 0, to_addr, m_addr_len) == -1) return false;

		return true;
	}

	void udpClose() {
		closesocket(m_sock);
	}

	~MyUdpSocket() {
		udpClose();
		WSACleanup();
	}




};
