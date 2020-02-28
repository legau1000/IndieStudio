/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Rock (.cpp)
*/

#include <fstream>
#include "Error.hpp"
#include "Rock.hpp"

Rock::Rock(int number)
{
    this->_name = "rock" + std::to_string(number);
    this->InitAsset();
}

Rock::~Rock()
{}

std::vector<std::string> Rock::GetVector()
{
    return (this->_typeOfAsset);
}

std::string Rock::GetName()
{
    return (this->_name);
}

bool Rock::BeDestroy()
{
    return (false);
}

void Rock::InitAsset()
{
    std::string content;
    std::fstream file("./media/rockWall/rock.txt", std::fstream::in);

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

int Rock::BombeExist()
{
    return (0);
}

void Rock::SetExist(int power)
{}

bool Rock::BeWall()
{
    return (true);
}

bool Rock::HaveBonus()
{
    return (false);
}

std::string Rock::GetBonus()
{
    return ("000");
}

std::vector<std::string> Rock::GetBonusVector()
{
    std::vector<std::string> vec;

    return (vec);
}

std::string Rock::GetBonusName()
{
    return (nullptr);
}

bool Rock::GetDangerous()
{
    return (false);
}

void Rock::SetDangerous(bool TrueOrFalse)
{
    this->_isDangerous = TrueOrFalse;
}
