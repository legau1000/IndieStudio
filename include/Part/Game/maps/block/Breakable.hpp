/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Breakable (.hpp)
*/

#ifndef BREAKABLE_HPP__
#define BREAKABLE_HPP__

#include "IBlock.hpp"

class Breakable : public IBlock
{
    public:
        Breakable(int number);
        ~Breakable();
        //Include all function for utilisation of Bonus IG
        std::vector<std::string> GetVector();
        std::string GetName();
        bool BeDestroy();
        bool BeWall();
        int BombeExist();
        void SetExist(int power);
        bool HaveBonus();
        std::string GetBonus();
        bool GetDangerous();
        void SetDangerous(bool TrueOrFalse);

        std::vector<std::string> GetBonusVector();
        std::string GetBonusName();

    private:
        void InitAsset();

        std::vector<std::string> _typeOfAsset;
        std::string _name;
        bool _isDangerous;
};

#endif