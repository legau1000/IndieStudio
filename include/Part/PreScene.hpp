/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** PreScene (.hpp)
*/

#ifndef PRESCENE_HPP__
#define PRESCENE_HPP__

#include "Graphique.hpp"

class PreScene
{
    public:
        PreScene();
        ~PreScene();
        void init(std::shared_ptr<Graphique> graphique);
        bool loop();
        void particuleAnimation();
        void checkSound();
        bool createMonster();
        void setButton();
        bool manageButton();

    private:
        std::shared_ptr<Graphique> _graphique;
        float _seconds;
        IAnimatedMeshSceneNode *node;
        scene::IParticleSystemSceneNode *ps;
};

#endif