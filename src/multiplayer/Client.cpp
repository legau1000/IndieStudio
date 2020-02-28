/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Client
*/

#include "../../include/multiplayer/Client.hpp"

Client::Client()
{
}

Client::~Client()
{
}

int Client::createSocket(char *ip)
{
    try {
        if ((this->_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            throw(Error(std::cerr, "client socket"));
        }
        this->_sock.sin_port = htons(40270);
        this->_sock.sin_family = AF_INET;
        this->_sock.sin_addr.s_addr = inet_addr(ip);
        if (connect(this->_sockfd, (sockaddr *)&this->_sock, sizeof(this->_sock)) == -1) {
            throw(Error(std::cerr, "client socket"));
        }
    }
    catch (Error &e) {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
}

int Client::sendtoServer(std::string msg)
{
    try {
        if (send(this->_sockfd, msg.c_str(), msg.length() + 1, 0) == -1) {
            throw(Error(std::cerr, "client send"));
        }
    }
    catch (Error &e) {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
}

int Client::reicvfromServer()
{

    char buf[4096];
    memset(buf, 0, 4096);
    try {
        if (recv(this->_sockfd, buf, 4096, 0) == -1)
            throw(Error(std::cerr, "client reicv"));
        this->_serverCurrentMsg = (std::string)buf;
    }
    catch (Error &e) {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
}

std::string Client::getMsg() { return (this->_serverCurrentMsg); }