/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Basic map (.cpp)
*/

#include <iostream>
#include <fstream>
#include "BasicMap.hpp"

BasicMap::BasicMap()
{
}

BasicMap::~BasicMap()
{
}

void BasicMap::setGraphicLib(std::shared_ptr<Graphique> graphic)
{
    _graphic = graphic;
}

bool BasicMap::trymoove(core::vector3df coordonnePlayer, std::string MyMoove)
{
    int indexZmap = 0;
    int indexXmap = 0;
    int moove = 1;

    if (coordonnePlayer.Z > 44 || coordonnePlayer.Z < -64 || coordonnePlayer.X > 74 || coordonnePlayer.X < -94)
        return (false);
    indexZmap = this->convertZ(coordonnePlayer.Z);
    indexXmap = this->convertX(coordonnePlayer.X);
    if (MyMoove[0] == '-')
        moove = -1;
    if (MyMoove[1] != 'Z') {
        if (MyMoove[0] == '-') {
            if (this->checkcase(indexXmap + moove, indexZmap + 1, coordonnePlayer.X - 6, coordonnePlayer.Z) || this->checkcase(indexXmap + moove, indexZmap, coordonnePlayer.X - 6, coordonnePlayer.Z) || this->checkcase(indexXmap + moove, indexZmap - 1, coordonnePlayer.X - 6, coordonnePlayer.Z)) {
                return (false);
            }
        } else if (this->checkcase(indexXmap + moove, indexZmap + 1, coordonnePlayer.X, coordonnePlayer.Z) || this->checkcase(indexXmap + moove, indexZmap, coordonnePlayer.X, coordonnePlayer.Z) || this->checkcase(indexXmap + moove, indexZmap - 1, coordonnePlayer.X, coordonnePlayer.Z)) {
            return (false);
        }
    } else {
        if (MyMoove[0] != '-') {
            if (this->checkcase(indexXmap + 1, indexZmap + moove, coordonnePlayer.X, coordonnePlayer.Z + 6) || this->checkcase(indexXmap, indexZmap + moove, coordonnePlayer.X, coordonnePlayer.Z + 6) || this->checkcase(indexXmap - 1, indexZmap + moove, coordonnePlayer.X, coordonnePlayer.Z + 6)) {
                return (false);
            }
        } else if (this->checkcase(indexXmap + 1, indexZmap + moove, coordonnePlayer.X, coordonnePlayer.Z) || this->checkcase(indexXmap, indexZmap + moove, coordonnePlayer.X, coordonnePlayer.Z) || this->checkcase(indexXmap - 1, indexZmap + moove, coordonnePlayer.X, coordonnePlayer.Z)) {
            return (false);
        }
    }
    return (true);
}

bool BasicMap::checkcase(int x, int z, int PlayerX, int PlayerZ)
{
    if (!this->_map[z][x]->BeWall())
        return (false);
    core::vector3df coorBloc = this->_graphic->_nodeMap.find(this->_map[z][x]->GetName())->second->getPosition();
    if (PlayerZ >= coorBloc.Z && PlayerZ <= coorBloc.Z + 10 && PlayerX <= coorBloc.X && PlayerX >= coorBloc.X - 10)
    {
        return (true);
    }
    return (false);
}

int BasicMap::convertZ(int z)
{
    int tab[] = {-70, -60, -50, -40, -30, -20, -10, 0, 10, 20, 30, 40, 50, 60};
    int index = 0;

    while (z + 3 > tab[index])
        index++;
    return (index - 1);
}

int BasicMap::convertX(int x)
{
    int tab[] = {-100, -90, -80, -70, -60, -50, -40, -30, -20, -10, 0, 10, 20, 30, 40, 50, 60, 70, 80};
    int index = 0;

    while (x - 3 > tab[index])
        index++;
    return (index);
}

void BasicMap::initMap(std::vector<std::vector<std::shared_ptr<IBlock>>> map)
{
    this->_map = map;
}

std::string BasicMap::addPlayer(std::vector<core::vector3df> coorPlayer, int z, int x)
{
    std::string letter = " ";
    int index = 0;

    while (index < coorPlayer.size()) {
        if (coorPlayer[index].X == x && coorPlayer[index].Z == z)
            return (std::to_string(index));
        index++;
    }
    return (letter);
}

std::string BasicMap::convertMap(std::vector<core::vector3df> coorPlayer)
{
    std::string letter;
    int index = 0;
    int z = 1;
    int x = 0;
    std::string stringMap;

    stringMap.append("XXXXXXXXXXXXXXXXXXX\n");
    while (z < this->_map.size() - 1) {
        while (x < this->_map[z].size()) {
            if (this->_map[z][x]->BeWall()) {
                if (this->_map[z][x]->BeDestroy())
                    letter = '#';
                else
                    letter = 'R';
            } else
                letter = this->addPlayer(coorPlayer, z, x);
            stringMap.append(letter);
            x++;
        }
        x = 0;
        z++;
        stringMap.append("\n");
    }
    stringMap.append("XXXXXXXXXXXXXXXXXXX\n\n");
    return (stringMap);
}