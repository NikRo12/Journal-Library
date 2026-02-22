#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "journal_api.h"
#include "utils.h"

class TcpServer {
public:
    TcpServer(int port, const std::string& filename, LogLevel def);
    ~TcpServer();
    void start();

private:
    int port_;
    int server_fd_;
    void handleClient(int client_fd);
};

#endif // SERVER_H