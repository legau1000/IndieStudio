/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Metal (.cpp)
*/

#include <fstream>
#include "Error.hpp"
#include "Metal.hpp"

Metal::Metal(int number)
{
    this->_name = "metal" + std::to_string(number);
    this->InitAsset();
}

Metal::~Metal()
{}

std::vector<std::string> Metal::GetVector()
{
    return (this->_typeOfAsset);
}

std::string Metal::GetName()
{
    return (this->_name);
}

bool Metal::BeDestroy()
{
    return (false);
}

void Metal::InitAsset()
{
    std::string content;
    std::fstream file("./media/metalWall/metal.txt", std::fstream::in);

    try {
        if (!file)
            throw(Error(std::cerr, "No such file or directory"));
        while (std::getline(file, content))
            this->_typeOfAsset.push_back(content);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    file.close();
}

int Metal::BombeExist()
{
    return (0);
}

void Metal::SetExist(int power)
{}

bool Metal::BeWall()
{
    return (true);
}

bool Metal::HaveBonus()
{
    return (false);
}

std::string Metal::GetBonus()
{
    return ("000");
}

std::vector<std::string> Metal::GetBonusVector()
{
    std::vector<std::string> vec;

    return (vec);
}

std::string Metal::GetBonusName()
{
    return (nullptr);
}

bool Metal::GetDangerous()
{
    return (false);
}

void Metal::SetDangerous(bool TrueOrFalse)
{
    this->_isDangerous = TrueOrFalse;
}
