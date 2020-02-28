#include "../../include/multiplayer/Client.hpp"


int main(int argc, char **argv)
{
    Client client;
    client.createSocket(argv[1]);
    client.sendtoServer("Client: test client issou tongue");
    client.reicvfromServer();
    std::cout << "Server: " << client.getMsg() << std::endl;
    return (0);
}
