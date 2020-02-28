/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ComputerAi
*/

#ifndef COMPUTERAI_HPP_
#define COMPUTERAI_HPP_

#include <iostream>
#include <memory>
#include <vector>
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

class ComputerAi : public IPlayer
{
public:
        ComputerAi(const std::string &skin, const std::string &name, int number);
        ~ComputerAi();
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

protected:
private:
        void InitAsset();
        void MovementPlayer(const f32 frameDeltaTime, int n, int bomb_proba);
        void SetNewGoal(const f32 frameDeltaTime);
        bool IsDangerous(int x, int z);
        void FindAWayOut(int x, int z);
        bool CheckPositionAroundXAndZ(int x, int z);
        void OffensivGoal(const f32 frameDeltatime, int direction, int x, int z);
        void ThreadBombe(std::string name);
        void bombeExplode(int index);
        void deleteOnMap(int, int, int);
        void cheackPlayer(int z, int x);
        void cheackBonus();

        std::vector<std::string> _typeOfAsset;
        std::string _name;
        const std::string _SkinFilePath;
        std::shared_ptr<Graphique> _graphic;
        f32 _MOVEMENT_SPEED;
        core::vector3df nodePosition;
        core::vector3df objPosition;
        std::vector<int> directionZ;
        std::vector<int> directionX;
        std::string MyMoove;
        std::shared_ptr<BasicMap> _map;
        bool _panicMode;

        std::vector<std::unique_ptr<Bombe>> _Bombe;
        std::vector<std::unique_ptr<Animation>> _Animation;

        std::vector<irr::core::vector3df> _AllPlayerPos;
        int _number;
        int _puissance;
        int _NbMaxBombe;
        int _NbBombe;
        bool _alive;
        bool _buttonBombePress;
        int _indexAnimation;
};

#endif /* !COMPUTERAI_HPP_ */
