/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Start Game (.hpp)
*/

#ifndef BASICMAP_HPP__
#define BASICMAP_HPP__

#include <iostream>
#include <memory>
#include "IMap.hpp"
#include "Graphique.hpp"
#include "IBlock.hpp"

class BasicMap
{
public:
    BasicMap();
    ~BasicMap();
    void setGraphicLib(std::shared_ptr<Graphique> graphic);
    void initMap(std::vector<std::vector<std::shared_ptr<IBlock>>> map);
    bool trymoove(core::vector3df coordonnePlayer, std::string MyMoove);
    int convertX(int X);
    int convertZ(int Z);
    std::string convertMap(std::vector<core::vector3df> coorPlayer);

    std::vector<std::vector<std::shared_ptr<IBlock>>> _map;

    private:
        std::string addPlayer(std::vector<core::vector3df> coorPlayer, int z, int x);
        // void detectColiZ(int index, int z, int x, std::string Isz);
        // void detectColiX(int index, int z, int x, std::string Isz);
        bool checkcase(int x, int z, int PlayerX, int PlayerZ);

        std::shared_ptr<Graphique> _graphic;

};

#endif