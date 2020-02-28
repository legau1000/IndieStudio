/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Start Game (.hpp)
*/

#ifndef IBLOCK_HPP__
#define IBLOCK_HPP__

#include <iostream>
#include <vector>

class IBlock
{
    public:
        virtual ~IBlock() = default;
        //Include all function for utilisation of Bonus IG
        virtual std::vector<std::string> GetVector() = 0;
        virtual std::string GetName() = 0;
        virtual bool BeDestroy() = 0;
        virtual bool BeWall() = 0;
        virtual void SetExist(int power) = 0;
        virtual int BombeExist() = 0;
        virtual bool HaveBonus() = 0;
        virtual std::string GetBonus() = 0;
        virtual bool GetDangerous() = 0;
        virtual void SetDangerous(bool TrueOrFalse) = 0;

        virtual std::vector<std::string> GetBonusVector() = 0;
        virtual std::string GetBonusName() = 0;

};

#endif