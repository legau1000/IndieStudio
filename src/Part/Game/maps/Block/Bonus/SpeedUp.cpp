/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** BombeUp (.hpp)
*/

#include <fstream>
#include "Error.hpp"
#include "SpeedUp.hpp"

SpeedUp::SpeedUp(int number)
{
    this->_name = "SpeedUp" + std::to_string(number);
    this->InitAsset();
}

SpeedUp::~SpeedUp()
{}

std::vector<std::string> SpeedUp::GetVector()
{
    return (this->_vector);
}

void SpeedUp::InitAsset()
{
    std::string content;
    std::fstream file("./media/speedUp/speedUp.txt", std::fstream::in);

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

std::string SpeedUp::GetName()
{
    return (this->_name);
}

std::string SpeedUp::GetBonus()
{
    return ("001");
}