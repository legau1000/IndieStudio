/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include "../../include/multiplayer/Server.hpp"

int main(int argc, char **argv)
{
    Server serv;
    serv.bind_socket();
    serv.connect();
    serv.sendtoClient("server: test server issou tongue");
    serv.reicvfromClient();
//    std::cout << "Client: " << serv.getMsg() << std::endl;
    return (0);
}