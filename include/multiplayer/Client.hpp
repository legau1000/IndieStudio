/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../../Errors/Error.hpp"
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

class Client {
	public:
		Client();
		~Client();
		int createSocket(char *ip);
		int sendtoServer(std::string msg);
		int reicvfromServer();
		std::string getMsg();

	protected:
	private:
        int _sockfd;
        int _port;
        char *_ip;
        struct sockaddr_in _sock;
		std::string _serverCurrentMsg;
};

#endif /* !CLIENT_HPP_ */
