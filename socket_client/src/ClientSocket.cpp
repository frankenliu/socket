//
// Created by frankenliu on 2016/11/17.
//
#include "ClientSocket.h"
#include <iostream>

namespace iva {

ClientSocket::ClientSocket()
{
    clientSocket = -1;
    m_domain = AF_UNIX;
}

ClientSocket::~ClientSocket()
{
    if(IsOk(clientSocket)) {
        close(clientSocket);
    }
}

bool ClientSocket::createClientSocket(int domain, int type, int protocol)
{
    bool res = false;
    this->clientSocket = socket(domain, type, protocol);
    m_domain = domain;
    if (IsOk(clientSocket)) {
        res = true;
    }
    return res;
}

bool ClientSocket::connectServer(int port, std::string host)
{
    bool res = false;
    int flag = NG;
    if (IsOk(clientSocket)) {
//            /*声明一个UNIX域套接字结构*/
//            sockaddr_un servaddr;
//            /*配置服务器信息(通信协议)*/
//            servaddr.sun_family = m_domain;
//            /*配置服务器信息(socket 对象)*/
//            strcpy(servaddr.sun_path, "server_socket");

            sockaddr_in servaddr;
            memset(&servaddr, 0, sizeof(servaddr));
            servaddr.sin_family = m_domain;
            servaddr.sin_addr.s_addr = inet_addr(host.c_str());
            servaddr.sin_port=htons(port);

        std::cout << "start connect socket, host:" << host << ", port:" << port << std::endl;
        flag = connect(clientSocket, (struct sockaddr*)&servaddr,sizeof(servaddr));
        std::cout << "start connect socket 1111, flag:" << flag << "error:" << errno <<  ",str:" << strerror(errno) << std::endl;
        if (IsOk(flag)) {
            res = true;
        }
    }
    return res;
}

bool ClientSocket::recvMsg(std::string& recv_buf)
{
    bool res = false;
    int flag = NG;
    char buf[MAX];
    recv_buf.clear();
    memset(buf, 0x0, MAX);
    if (IsOk(clientSocket)) {
        flag = read(clientSocket, &buf, MAX - 1);
        if (IsOk(flag)) {
            res = true;
            recv_buf = buf;
        }
    }
    return res;
}

bool ClientSocket::sendMsg(std::string& send_buf)
{
    bool res = false;
    int flag = NG;
    if (IsOk(clientSocket)) {
        flag = write(clientSocket, send_buf.c_str(), send_buf.length());
        if (IsOk(flag)) {
            res = true;
        }
    }
    return res;
}

bool ClientSocket::IsOk(int res)
{
    return res != NG;
}

}

