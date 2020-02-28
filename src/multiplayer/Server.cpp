/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Server
*/

#include "../../include/multiplayer/Server.hpp"

Server::Server() : _incClient(0)
{
    this->_clientfd[0] = 0;
    this->_clientfd[1] = 0;
    this->_clientfd[2] = 0;
}

Server::~Server()
{
}

void Server::bind_socket()
{
    int yes = 1;
    try {
        if ((this->_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            throw(Error(std::cerr, "socket creation"));
        }
        this->_sock.sin_family = AF_INET;
        this->_sock.sin_addr.s_addr = INADDR_ANY;
        this->_sock.sin_port = htons(40270);
        if(setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            throw(Error(std::cerr, "setsockopt"));
        }
        if ((bind(this->_sockfd, (struct sockaddr *)&this->_sock, sizeof(this->_sock))) == -1) {
            throw(Error(std::cerr, "bind"));
        }
        if (listen(this->_sockfd, 3) == -1) {
            throw(Error(std::cerr, "listen"));
        }
    }
    catch (Error &e)
    {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
}


/*
void Server::connect()
{
    socklen_t clientSize = sizeof(this->_client);
    char host[4096];
    char service[4096];

    memset(host, 0, 4096);
    memset(service, 0, 4096);
    try {
        this->_clientfd = accept(this->_sockfd, (sockaddr *)&this->_client, &clientSize);
        if (this->_clientfd == -1) {
            throw(Error(std::cerr, "accept"));
        }
    }
    catch (Error &e)
    {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
    int resget = getnameinfo((sockaddr *)&this->_client, sizeof(this->_client), host, 4096, service, 4096, 0);
    if (resget > 0)
        std::cout << host << " connected on " << service << std::endl;
    else {
        inet_ntop(AF_INET, &this->_client.sin_addr, host, 4096);
        std::cout << host << " connected on " << ntohs(this->_client.sin_port) << std::endl;
    }
}
*/
 
 void Server::connect()
{
    socklen_t addrlen = sizeof(this->_sock);
    fd_set readfd;
    int ret = 0;
    int nsocket;
     char host[4096];
    char service[4096];

    while (1) {
        memset(host, 0, 4096);
        memset(service, 0, 4096);
        inet_addr("192.168.122.1");
        FD_ZERO(&readfd);
        FD_SET(this->_sockfd, &readfd);
        try {
            if ((ret = select(this->_sockfd + 1, &readfd, NULL, NULL, NULL)) >= 0) {
                if (FD_ISSET(this->_sockfd, &readfd)) {
                    if ((this->_clientfd[this->_incClient] = accept(this->_sockfd, (struct sockaddr *)&this->_client[this->_incClient], &addrlen)) == -1) {
                        throw(Error(std::cerr, "accept"));
                    }
                }
            }
        }
        catch (Error &e) {
            e.where() << "You threw an exception: " << e.what() << std::endl;
        }
        int resget = getnameinfo((sockaddr *)&this->_client, sizeof(this->_client), host, 4096, service, 4096, 0);
        if (resget > 0)
            std::cout << host << " connected on " << service << std::endl;
        else {
            inet_ntop(AF_INET, &this->_client[this->_incClient].sin_addr, host, 4096);
            std::cout << host << " connected on " << ntohs(this->_client[this->_incClient].sin_port) << std::endl;
        }
        this->_incClient++;
        if (this->_incClient > 2) {
            std::cout << "server is full" << std::endl;
            break;
        }
    }
}

void Server::sendtoClient(std::string msg)
{   
    size_t inc = 0;
    while (inc < 3) {
        try {
            if (send(this->_clientfd[inc], msg.c_str(), msg.length() + 1, 0) == -1) {
                throw(Error(std::cerr, "server send"));
            }
        }
        catch (Error &e) {
            e.where() << "You threw an exception: " << e.what() << std::endl;
        }
        inc++;
    }
}

void Server::reicvfromClient()
{
    size_t inc = 0;
    char buf[4096];
    while (inc < 3) {
        memset(buf, 0, 4096);
        try {
            if (recv(this->_clientfd[inc], buf, 4096, 0) == -1)
                throw(Error(std::cerr, "server reicv"));
    //        this->_clientCurrentMsg = (std::string)buf;
            std::cout << (std::string)buf << std::endl;
        }
        catch (Error &e) {
            e.where() << "You threw an exception: " << e.what() << std::endl;
        }
        inc++;
    }
}

std::string Server::getMsg() { return (this->_clientCurrentMsg); }

/*
void Server::servLoop()
{    
    char buf[4096];
    while (1) {
        memset(buf, 0, 4096);
        int brecv = recv(this->_clientfd, buf, 4096, 0);
        if (brecv == -1) {
            std::cerr << "error recv" << std::endl;
            break;
        }
        else if (strncmp(buf, "exit", 4) == 0) {
            std::cout << "Exit" << std::endl;
            break;
        }
        std::cout << "Received: " << (std::string)buf << std::endl;
        send(this->_clientfd, buf, brecv + 1, 0);
    }
    close(this->_clientfd);
    close(this->_sockfd);
}
*/