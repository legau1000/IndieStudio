/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Start Game (.hpp)
*/

#ifndef HUMAN_HPP__
#define HUMAN_HPP__

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include "IPlayer.hpp"
#include "Graphique.hpp"
#include "Bombe.hpp"
#include "Animation.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Human : public IPlayer
{
public:
    Human(const std::string &skin, std::string name, int number);
    ~Human();
    //Include all function for Player (bot or rly player)
    void setGraphicLib(std::shared_ptr<Graphique> graphic);
    bool StartPlay(const f32 frameDeltaTime);
    std::vector<std::string> GetVector();
    std::string GetName();
    void setMap(std::shared_ptr<BasicMap> map);

    void SetPuissance(int);
    void SetBombe(int);
    void SetSpeed(f32 _MOVEMENT_SPEED);
    int GetPuissance();
    int GetBombe();
    f32 GetSpeed();

private:
    void InitAsset();
    void MovementPlayer(const f32 frameDeltaTime);
    void ThreadBombe(std::string name);
    void bombeExplode(int index);
    void deleteOnMap(int, int, int);
    void cheackPlayer(int z, int x);
    void cheackBonus();
    void InitMoove();

    std::vector<std::string> _typeOfAsset;
    std::string _name;
    const std::string _SkinFilePath;
    std::shared_ptr<Graphique> _graphic;
    f32 _MOVEMENT_SPEED;
    core::vector3df nodePosition;
    std::string MyMoove;
    std::shared_ptr<BasicMap> _map;

    std::vector<std::unique_ptr<Bombe>> _Bombe;
    std::vector<std::unique_ptr<Animation>> _Animation;

    std::vector<irr::core::vector3df> _AllPlayerPos;
    int _number;
    int _puissance;
    int _NbMaxBombe;
    int _NbBombe;
    bool _alive;
    bool _buttonBombePress;
    enum irr::EKEY_CODE _keys[5];
    int _indexAnimation;
};

#endif