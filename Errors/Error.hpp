/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Virtual class Error
*/

#ifndef ERRORS_HPP__
#define ERRORS_HPP__

#include <iostream>

class Error: public std::exception
{
    public:
        Error(std::ostream &os, const std::string &message) throw() : _os(os)
        {
            this->_message = message;
        };
        ~Error() {};

        const char *what(void) const throw()
        {
            return this->_message.c_str();
        }

        std::ostream &where(void) const throw()
        {
            return this->_os;
        }

    protected:
    private:
        std::string _message;
        std::ostream &_os;

};
#endif