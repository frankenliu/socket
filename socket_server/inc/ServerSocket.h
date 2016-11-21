//
// Created by frankenliu on 2016/11/17.
//

#ifndef DEVICEASSISTANT_SERVERSOCKET_H
#define DEVICEASSISTANT_SERVERSOCKET_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include<errno.h>
#include <netinet/in.h>

#include <string>

namespace iva
{
const int NG = -1;
const int MAX = 4096;
const std::string LOCAL = "127.0.0.1";
const int PORT = 6666;

class ServerSocket
{
public:
    ServerSocket();
    ~ServerSocket();
    bool createServerSocket(int domain = AF_UNIX, int type = SOCK_STREAM, int protocol = 0);
    bool serverSocketBind(int port, std::string host);
    bool serverSocketListen(int connectNumber);
    bool serverSocketAccept();
    bool recvMsg(int clientSocket, std::string& recv_buf);
    bool sendMsg(int clientSocket, std::string& send_buf);
    int getClientSockets();
private:
    bool IsOk(int res);
    int serverSocket;
    int maxClientSockets; //
    int m_domain;
    int clientSockets;
};
}

#endif //DEVICEASSISTANT_SERVERSOCKET_H
