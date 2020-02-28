/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Ground (.cpp)
*/

#include <ctime>
#include <fstream>
#include <memory>
#include "PowerUp.hpp"
#include "SpeedUp.hpp"
#include "BombeUp.hpp"
#include "Error.hpp"
#include "Ground.hpp"

Ground::Ground(int number)
{
    this->_name = "sol" + std::to_string(number);
    this->InitAsset();
    this->_power = 0;
    this->_InBonus = 0;
    this->_HaveBonus = false;
}

Ground::Ground(int number, bool bonus)
{
    this->_name = "sol" + std::to_string(number);
    this->InitAsset();
    this->_power = 0;
    if (bonus == true) {
        this->RandomBonus(number);
    }
}

void Ground::RandomBonus(int number)
{
    srand(std::time(NULL));
    this->_InBonus = rand() % (number) % 10;
    this->_HaveBonus = true;
    if (this->_InBonus == 3 || this->_InBonus == 4) {
        this->_Bonus = std::make_unique<PowerUp>(number);
    } else if (this->_InBonus == 5 || this->_InBonus == 6) {
        this->_Bonus = std::make_unique<BombeUp>(number);
    } else if (this->_InBonus == 7) {
        this->_Bonus = std::make_unique<SpeedUp>(number);
    } else {
        this->_HaveBonus = false;
    }
}

Ground::~Ground()
{}

std::vector<std::string> Ground::GetVector()
{
    return (this->_typeOfAsset);
}

std::string Ground::GetName()
{
    return (this->_name);
}

bool Ground::BeDestroy()
{
    return (false);
}

void Ground::InitAsset()
{
    std::string content;
    std::fstream file("./media/sol/sol.txt", std::fstream::in);

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

int Ground::BombeExist()
{
    return (this->_power);
}

void Ground::SetExist(int power)
{
    this->_power = power;
}

bool Ground::BeWall()
{
    return (false);
}

bool Ground::HaveBonus()
{
    return (this->_HaveBonus);
}

std::string Ground::GetBonus()
{
    this->_HaveBonus = false;
    return (this->_Bonus->GetBonus());
}

std::vector<std::string> Ground::GetBonusVector()
{
    return (this->_Bonus->GetVector());
}

std::string Ground::GetBonusName()
{
    return (this->_Bonus->GetName());
}

bool Ground::GetDangerous()
{
    return (false);
}

void Ground::SetDangerous(bool TrueOrFalse)
{
    this->_isDangerous = TrueOrFalse;
}
