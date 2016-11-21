//
// Created by frankenliu on 2016/11/17.
//

#ifndef DEVICEASSISTANT_CLIENTSOCKET_H
#define DEVICEASSISTANT_CLIENTSOCKET_H

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
const int PORT = 6666;
const std::string LOCAL = "127.0.0.1";

class ClientSocket
{
public:
    ClientSocket();
    ~ClientSocket();
    bool createClientSocket(int domain = AF_UNIX, int type = SOCK_STREAM, int protocol = 0);
    bool connectServer(int port, std::string host = LOCAL);
    bool recvMsg(std::string& recv_buf);
    bool sendMsg(std::string& send_buf);
private:
    bool IsOk(int res);
    int clientSocket;
    int m_domain;
};
}

#endif //DEVICEASSISTANT_CLIENTSOCKET_H
