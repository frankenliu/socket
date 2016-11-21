//
// Created by frankenliu on 2016/11/17.
//
#include "ClientSocket.h"
#include <iostream>

int main(int args, char *argv[]) {
    iva::ClientSocket* socket = new iva::ClientSocket();
    bool is_create = socket->createClientSocket(AF_INET, SOCK_STREAM, 0);
    if(!is_create) {
        std::cerr << "create socket fail." << std::endl;
        return -1;
    }
    bool flag = socket->connectServer(iva::PORT, iva::LOCAL);
    if(!flag) {
       std::cerr << "connect socket fail." << std::endl;
        return -1;
    }
    std::string text("fasdaf");
    bool is_send = socket->sendMsg(text);
    if(!is_send) {
        std::cerr << "socket send fail." << std::endl;
        return -1;
    }
    return 0;
}

