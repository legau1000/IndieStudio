/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Ground (.hpp)
*/

#ifndef GROUND_HPP__
#define GROUND_HPP__

#include <memory>
#include "IBonus.hpp"
#include "IBlock.hpp"

class Ground : public IBlock
{
    public:
        Ground(int number);
        Ground(int number, bool bonus);
        ~Ground();
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
        void RandomBonus(int number);

        int _InBonus;
        std::unique_ptr<IBonus> _Bonus;
        std::vector<std::string> _typeOfAsset;
        std::string _name;
        bool _HaveBonus;
        int _power;
        bool _isDangerous;

};

#endif