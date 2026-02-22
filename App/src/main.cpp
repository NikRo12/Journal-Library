#include "server.h"

int main(int argc, const char* argv[]) {
    std::string filename;
    LogLevel def;

    parseParams(filename, def, argc, argv);

    TcpServer server(8080, filename, def);
    server.start();
    return 0;
}