/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** BombeUp (.hpp)
*/

#include <fstream>
#include "Error.hpp"
#include "BombeUp.hpp"

BombeUp::BombeUp(int number)
{
    this->_name = "BombeUp" + std::to_string(number);
    this->InitAsset();
}

BombeUp::~BombeUp()
{}

std::vector<std::string> BombeUp::GetVector()
{
    return (this->_vector);
}

void BombeUp::InitAsset()
{
    std::string content;
    std::fstream file("./media/bombeUp/bombeUp.txt", std::fstream::in);

    try {
        if (!file)
            throw(Error(std::cerr, "No such file or directory"));
        while (std::getline(file, content))
            this->_vector.push_back(content);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    file.close();
}

std::string BombeUp::GetName()
{
    return (this->_name);
}

std::string BombeUp::GetBonus()
{
    return ("100");
}