//
// Created by frankenliu on 2016/11/17.
//
#include <ServerSocket.h>
#include <iostream>

int main(int args, char *argv[]) {
    iva::ServerSocket* socket = new iva::ServerSocket();
    bool is_create = socket->createServerSocket(AF_INET, SOCK_STREAM, 0);
    if(!is_create) {
        std::cerr << "create server socket fail." << std::endl;
        return -1;
    }
    bool is_bind = socket->serverSocketBind(iva::PORT, iva::LOCAL);
    if(!is_bind) {
        std::cerr << "bind server socket fail." << std::endl;
        return -1;
    }
    bool is_listen = socket->serverSocketListen(5);
    if(!is_listen) {
        std::cerr << "server socket listen fail." << std::endl;
        return -1;
    }
    while(1) {
        bool flag = socket->serverSocketAccept();
        if(!flag) {
            continue;
        }
        std::string rec_text;
        socket->recvMsg(socket->getClientSockets(), rec_text);
        std::cout << "client text:" << rec_text << std::endl;
    }


}

