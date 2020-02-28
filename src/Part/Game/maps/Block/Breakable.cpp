/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Breakable (.cpp)
*/

#include <fstream>
#include "Error.hpp"
#include "Breakable.hpp"

Breakable::Breakable(int number)
{
    this->_name = "box" + std::to_string(number);
    this->InitAsset();
}

Breakable::~Breakable()
{}

std::vector<std::string> Breakable::GetVector()
{
    return (this->_typeOfAsset);
}

std::string Breakable::GetName()
{
    return (this->_name);
}

bool Breakable::BeDestroy()
{
    return (true);
}

void Breakable::InitAsset()
{
    std::string content;
    std::fstream file("./media/caisse/box.txt", std::fstream::in);

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

int Breakable::BombeExist()
{
    return (0);
}

void Breakable::SetExist(int power)
{}

bool Breakable::BeWall()
{
    return (true);
}

bool Breakable::HaveBonus()
{
    return (false);
}

std::string Breakable::GetBonus()
{
    return ("000");
}

std::vector<std::string> Breakable::GetBonusVector()
{
    std::vector<std::string> vec;

    return (vec);
}

std::string Breakable::GetBonusName()
{
    return (nullptr);
}

bool Breakable::GetDangerous()
{
    return (false);
}

void Breakable::SetDangerous(bool TrueOrFalse)
{
    this->_isDangerous = TrueOrFalse;
}
