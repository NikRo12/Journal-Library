#include "server.h"

TcpServer::TcpServer(int port) : port_(port), server_fd_(-1) {
    init_logger("log.txt", LogLevel::DEBUG);
}

TcpServer::~TcpServer() {
    if (server_fd_ != -1) close(server_fd_);
}

void TcpServer::start() {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == 0) {
        perror("Socket failed");
        return;
    }

    int opt = 1;
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Setsockopt failed");
        return;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    if (bind(server_fd_, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return;
    }

    if (listen(server_fd_, 10) < 0) {
        perror("Listen failed");
        return;
    }

    std::cout << "Server started on port " << port_ << "..." << std::endl;

    while (true) {
        int addrlen = sizeof(address);
        int client_fd = accept(server_fd_, (struct sockaddr*)&address, (socklen_t*)&addrlen);
            
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        std::cout << "New client" << std::endl;
        std::thread(&TcpServer::handleClient, this, client_fd).detach();
    }
}

LogLevel TcpServer::choose_log_level(const std::string& str) {
    if (str == "DEBUG") return LogLevel::DEBUG;
    if (str == "INFO")  return LogLevel::INFO;
    if (str == "ERROR") return LogLevel::ERROR;
    
    return LogLevel::NONE;
}

void TcpServer::handleClient(int client_fd) {
    char buffer[1024] = {0};
    const char* message1 = "Enter log message:\n";
    const char* message2 = "Enter log level (DEBUG, INFO, ERROR):\n";

    while(true) {
        if (send(client_fd, message1, strlen(message1), 0) <= 0) break;
            
        ssize_t n = read(client_fd, buffer, sizeof(buffer) - 1);
        if (n <= 0) break;

        buffer[n] = '\0';
        std::string request = trim(std::string(buffer, n));

        if (send(client_fd, message2, strlen(message2), 0) <= 0) break;
            
        n = read(client_fd, buffer, sizeof(buffer) - 1);
        if (n <= 0) break;

        buffer[n] = '\0';
        buffer[strcspn(buffer, "\r\n")] = 0;
            
        LogLevel level = choose_log_level(trim(buffer));

        log_message(request.c_str(), level);
    }

    close(client_fd);
    std::cout << "Closed connection" << std::endl;
}