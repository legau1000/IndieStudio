/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** PowerUp (.hpp)
*/

#include <fstream>
#include "Error.hpp"
#include "PowerUp.hpp"

PowerUp::PowerUp(int number)
{
    this->_name = "PowerUp" + std::to_string(number);
    this->InitAsset();
}

PowerUp::~PowerUp()
{}

void PowerUp::InitAsset()
{
    std::string content;
    std::fstream file("./media/fireUp/fireUp.txt", std::fstream::in);

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

std::vector<std::string> PowerUp::GetVector()
{
    return (this->_vector);
}

std::string PowerUp::GetName()
{
    return (this->_name);
}

std::string PowerUp::GetBonus()
{
    return ("010");
}