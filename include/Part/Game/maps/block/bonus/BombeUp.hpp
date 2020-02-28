/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** BombeUp (.hpp)
*/

#ifndef BOMBEUP_HPP__
#define BOMBEUP_HPP__

#include "IBonus.hpp"

class BombeUp : public IBonus
{
    public:
        BombeUp(int number);
        ~BombeUp();
        std::vector<std::string> GetVector();
        std::string GetName();
        std::string GetBonus();

    private:
        void InitAsset();
        std::string _name;
        std::vector<std::string> _vector;

};

#endif