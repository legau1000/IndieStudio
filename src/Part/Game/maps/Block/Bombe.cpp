/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Bombe (.cpp)
*/

#include <fstream>
#include <ctime>
#include "Error.hpp"
#include "Bombe.hpp"

Bombe::Bombe(std::string name, int x, int z, int puissance)
{
    this->_name = name;
    this->_x = x;
    this->_z = z;
    this->_puissance = puissance;
    this->InitAsset();
    time_t timer1;
    std::time(&timer1);
    struct tm *newTime1;
    newTime1 = std::localtime(&timer1);
    _seconds = newTime1->tm_sec;
}

Bombe::~Bombe()
{
}

std::vector<std::string> Bombe::GetVector()
{
    return (this->_typeOfAsset);
}

std::string Bombe::GetName()
{
    return (this->_name);
}

bool Bombe::Explose()
{
    time_t timer1;
    std::time(&timer1);
    struct tm *newTime1 = std::localtime(&timer1);
    int seconds = newTime1->tm_sec;

    if (seconds >= _seconds + 3)
        return (true);
    return (false);
}

void Bombe::InitAsset()
{
    std::string content;
    std::fstream file("./media/bombe/bombe.txt", std::fstream::in);

    try
    {
        if (!file)
            throw(Error(std::cerr, "No such file or directory"));
        while (getline(file, content))
            this->_typeOfAsset.push_back(content);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    file.close();
}

int Bombe::GetX()
{
    return (this->_x);
}

int Bombe::GetZ()
{
    return (this->_z);
}