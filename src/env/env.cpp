/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** detect env error (.cpp)
*/

#include "Error.hpp"
#include "env.hpp"

EnvErr::EnvErr(char **env)
{
    this->_env = env;
}

EnvErr::~EnvErr()
{}

bool EnvErr::detectPath()
{
    std::string tmp = this->_env[0];
    int index = 0;
    return (true);
}

bool EnvErr::detectErrorEnv()
{
    try {
        if (!this->_env || !this->_env[0])
            throw(Error(std::cerr, "No environment detected."));
        if (!this->detectPath())
            throw(Error(std::cerr, "Path to Graphic Library was empty."));
    } catch(Error &e) {
        e.where() << "Error on environment: " << e.what() << std::endl;
        return (true);
    }
    return (false);
}