/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Start Game (.hpp)
*/

#ifndef IMap_HPP__
#define IMap_HPP__

#include "Graphique.hpp"

class IMap
{
public:
    virtual ~IMap() = default;
    //Include all function for utilisation of map
    virtual void Start() = 0;
    virtual void setGraphicLib(std::shared_ptr<Graphique> graphic) = 0;
    virtual void moove() = 0;

};

#endif