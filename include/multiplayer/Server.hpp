/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "../../Errors/Error.hpp"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>

class Server {
	public:
		Server();
		~Server();
                void bind_socket();
                void servLoop();
                void connect();
                void sendtoClient(std::string msg);
                void reicvfromClient();
                std::string getMsg();

	protected:
	private:
                int _port;
                int _sockfd;
                struct sockaddr_in _sock;
                struct sockaddr_in _client[3];
                int _clientfd[3];
                std::string _clientCurrentMsg;
                size_t _incClient;
};

#endif /* !SERVER_HPP_ */
