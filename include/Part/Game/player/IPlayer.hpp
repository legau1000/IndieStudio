/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Start Game (.hpp)
*/

#ifndef IPLAYER_HPP__
#define IPLAYER_HPP__

#include <irrlicht.h>
#include "BasicMap.hpp"
#include "Graphique.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class IPlayer
{
    public:
        virtual ~IPlayer() = default;
        //Include all function for Player (bot or rly player)
        virtual void setGraphicLib(std::shared_ptr<Graphique> graphic) = 0;
        virtual bool StartPlay(const f32 frameDeltaTime) = 0;
        virtual std::vector<std::string> GetVector() = 0;
        virtual std::string GetName() = 0;
        virtual void setMap(std::shared_ptr<BasicMap> map) = 0;
        virtual void SetPuissance(int) = 0;
        virtual void SetBombe(int) = 0;
        virtual void SetSpeed(f32 _MOVEMENT_SPEED) = 0;
        virtual int GetPuissance() = 0;
        virtual int GetBombe() = 0;
        virtual f32 GetSpeed() = 0;

};

#endif