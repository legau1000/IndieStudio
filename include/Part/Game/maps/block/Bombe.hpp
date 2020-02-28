/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Bombe (.hpp)
*/

#ifndef BOMBE_HPP__
#define BOMBE_HPP__

#include <vector>
#include <iostream>

class Bombe
{
    public:
        Bombe(std::string name, int x, int z, int puissance);
        ~Bombe();
        //Include all function for utilisation of Bonus IG
        std::vector<std::string> GetVector();
        std::string GetName();
        bool BeWall() {return (true);};
        bool Explose();
        int GetX();
        int GetZ();

    private:
        void InitAsset();
        std::vector<std::string> _typeOfAsset;
        std::string _name;
        int _x;
        int _z;
        int _puissance;
		int _seconds;

};

#endif