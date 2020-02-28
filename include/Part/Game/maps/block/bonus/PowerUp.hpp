/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** BombeUp (.hpp)
*/

#ifndef POWERDUP_HPP__
#define POWERDUP_HPP__

#include "IBonus.hpp"

class PowerUp : public IBonus
{
    public:
        PowerUp(int number);
        ~PowerUp();
        std::vector<std::string> GetVector();
        std::string GetName();
        std::string GetBonus();

    private:
        void InitAsset();
        std::string _name;
        std::vector<std::string> _vector;

};

#endif