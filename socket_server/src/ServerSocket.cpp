//
// Created by frankenliu on 2016/11/17.
//
#include "ServerSocket.h"
#include <iostream>

namespace iva
{
ServerSocket::ServerSocket()
{
    serverSocket = -1;
    maxClientSockets = 10;
    m_domain = AF_UNIX;
    clientSockets = 0;
}

ServerSocket::~ServerSocket()
{
    if(IsOk(serverSocket)) {
        close(serverSocket);
    }
}

bool ServerSocket::createServerSocket(int domain, int type, int protocol)
{
    bool res = false;
    this->serverSocket = socket(domain, type, protocol);
    this->m_domain = domain;
    if (IsOk(serverSocket)) {
        int opt = 1;
        int flag = setsockopt(serverSocket,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt));
        std::cout << "createServerSocket setsockopt, flag:" << flag << ", error:" << errno <<  ",str:" << strerror(errno) << std::endl;
        res = true;
    }
    return res;
}

bool ServerSocket::serverSocketBind(int port, std::string host)
{
    bool res = false;
    int flag = NG;
    if (IsOk(serverSocket)) {
//        /*声明一个UNIX域套接字结构*/
//        sockaddr_un servaddr;
//        /*配置服务器信息(通信协议)*/
//        servaddr.sun_family = m_domain;
//        /*配置服务器信息(socket 对象)*/
//        strcpy(servaddr.sun_path, "server_socket");

        sockaddr_in  servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = m_domain;
        servaddr.sin_addr.s_addr = inet_addr(host.c_str());
        servaddr.sin_port=htons(port);
        std::cout << "start bind socket, host:" << host << ", port:" << port << std::endl;
        flag = bind(serverSocket,(struct sockaddr*)&servaddr,sizeof(struct sockaddr_in));
        std::cout << "start bind socket 1111, flag:" << flag << ", error:" << errno <<  ",str:" << strerror(errno) << std::endl;
        if (IsOk(flag)) {
            res = true;
            std::cout << "start bind socket port:" << port << std::endl;
        }
    }
    return res;
}

bool ServerSocket::serverSocketListen(int connectNumber)
{
    bool res = false;
    int flag = -1;
    if (IsOk(serverSocket)) {
        flag = listen(serverSocket, connectNumber);
        if (IsOk(flag)) {
            maxClientSockets = connectNumber;
            res = true;
        }
    }
    return res;
}

bool ServerSocket::serverSocketAccept()
{
    bool res = false;
    if (IsOk(serverSocket)) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (IsOk(clientSocket)) {
            //TODO 客户端连接上来
            if(clientSockets == NULL) {
                clientSockets = clientSocket;
            }
            res = true;
        }
    }
    return res;
}

bool ServerSocket::recvMsg(int clientSocket, std::string& recv_buf)
{
    bool res = false;
    int flag = NG;
    char buf[MAX];
    recv_buf.clear();
    memset(buf, 0x0, MAX);
    if (IsOk(serverSocket)) {
        flag = read(clientSocket, &buf, MAX - 1);
        if (IsOk(flag)) {
            res = true;
            recv_buf = buf;
        }
    }
    return res;
}

bool ServerSocket::sendMsg(int clientSocket, std::string& send_buf)
{
    bool res = false;
    int flag = NG;
    if (IsOk(serverSocket)) {
        flag = write(clientSocket, send_buf.c_str(), send_buf.length());
        if (IsOk(flag)) {
            res = true;
        }
    }
    return res;
}

int ServerSocket::getClientSockets()
{
    return clientSockets;
}

bool ServerSocket::IsOk(int res)
{
    return res != NG;
}
}

