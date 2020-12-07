#include "udp/udpserver.h"

bool UdpServer::initServer(const int port) {
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    if (m_sock > 0) {
        udpClose();
    }
	
    //创建套接字
    m_sock = socket(PF_INET, SOCK_DGRAM, 0);
    //绑定套接字
    m_addr_len = sizeof(struct sockaddr_in);
    memset(&m_clientaddr, 0, sizeof(m_clientaddr));

    memset(&m_serveraddr, 0, sizeof(m_serveraddr));  //每个字节都用0填充
    m_serveraddr.sin_family = AF_INET;  //使用IPv4地址
    m_serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
    m_serveraddr.sin_port = htons(port);  //端口
    if(bind(m_sock, (SOCKADDR*)&m_serveraddr,  m_addr_len) != 0) return false;
    return true;

}

bool UdpServer::udpRecv(char* buffer, const int s_timeout) {
    
    return udpRead(buffer, (SOCKADDR*)&m_clientaddr, s_timeout);
}

bool UdpServer::udpSend(const char* buffer) {
    
    return udpWrite(buffer, (SOCKADDR*)&m_clientaddr);
}
