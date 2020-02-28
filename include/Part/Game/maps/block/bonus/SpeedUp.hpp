/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** BombeUp (.hpp)
*/

#ifndef SPEEDUP_HPP__
#define SPEEDUP_HPP__

#include "IBonus.hpp"

class SpeedUp : public IBonus
{
    public:
        SpeedUp(int number);
        ~SpeedUp();
        std::vector<std::string> GetVector();
        std::string GetName();
        std::string GetBonus();

    private:
        void InitAsset();
        std::string _name;
        std::vector<std::string> _vector;

};

#endif