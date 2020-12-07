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

class MyTcpSocket{
protected:
	WSADATA m_wsa_data;
	sockaddr_in m_serveraddr;

public:
	SOCKET m_sock;

	MyTcpSocket(){
		m_sock = -1;
	}

	// 发送报文，buf_len取0发送字符流，发送二进制数据取二进制数据块大小
	bool tcpSend(SOCKET sock, const char* buffer, const int buf_len=0) {
		if (sock == -1) return false;
		fd_set tmpfd;

		FD_ZERO(&tmpfd);
		FD_SET(sock, &tmpfd);

		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		if (select((int)sock + 1, 0, &tmpfd, 0, &timeout) <= 0) return false;

		int post_len = 0;
		if (buf_len == 0) post_len = strlen(buffer);
		else post_len = buf_len;
		int i_post_len = htonl(post_len);

		char* send_buffer = new char[post_len + 4];
		memset(send_buffer, 0, post_len + 4);
		memcpy(send_buffer, &i_post_len, 4);
		memcpy(send_buffer + 4, buffer, post_len);

		int left_len, writen_len, index_write;
		left_len = post_len + 4;
		index_write = 0;

		while (left_len > 0) {
			if ((writen_len = send(sock, send_buffer + index_write, left_len, 0)) <= 0) return false;

			left_len -= writen_len;
			index_write += writen_len;
		}
		return true;
	}
	// 接收报文，s_timeout为超时时间，取0为无限等待
	bool tcpRecv(SOCKET sock, char* buffer, const int s_timeout=0) {
		if (sock == -1) return false;

		if (s_timeout > 0) {
			fd_set tmpfd;

			FD_ZERO(&tmpfd);
			FD_SET(sock, &tmpfd);

			struct timeval timeout;
			timeout.tv_sec = s_timeout;
			timeout.tv_usec = 0;

			if (select((int)sock + 1, 0, &tmpfd, 0, &timeout) <= 0) return false;
		}

		int buf_len = 0;
		if (recv(sock, (char*)&buf_len, 4, 0) == SOCKET_ERROR) return false;
		buf_len = ntohl(buf_len);

		int left_len, read_len, index_read;
		left_len = buf_len;
		index_read = 0;

		while (left_len > 0) {
			if ((read_len = recv(sock, buffer + index_read, left_len, 0)) <= 0) return false;

			left_len -= read_len;
			index_read += read_len;
		}
		return true;
	}

	~MyTcpSocket(){
		WSACleanup();
	}


};

