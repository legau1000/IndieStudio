/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** IBonus (.hpp)
*/

#ifndef IBONUS_HPP__
#define IBONUS_HPP__

#include <iostream>
#include <vector>

class IBonus
{
    public:
        virtual ~IBonus() = default;
        virtual std::vector<std::string> GetVector() = 0;
        virtual std::string GetName() = 0;
        virtual std::string GetBonus() = 0;
        //Include all function for utilisation of Bonus IG

};

#endif