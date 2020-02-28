/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Start Game (.hpp)
*/

#ifndef INDIE_HPP__
#define INDIE_HPP__

#include <vector>
#include <memory>
#include "IPlayer.hpp"
#include "Graphique.hpp"
#include "IMap.hpp"
#include "IPart.hpp"
#include "PreScene.hpp"

class Indie
{
    public:
        Indie();
        ~Indie();
        int start();

    protected:

    private:
        // Functions
        std::vector<std::shared_ptr<IPlayer>> GetPlayer();
        std::shared_ptr<BasicMap> GetMap();
        bool initGraphique();
        bool ChooseLunch();

        // Variables
        bool _IsMenu;
        std::vector<std::unique_ptr<IPart>> _Part;
        std::shared_ptr<Graphique> _graphic;
        std::vector<std::shared_ptr<IPlayer>> _player;
        std::shared_ptr<BasicMap> _map;
        std::unique_ptr<PreScene> _Prescene;

};

#endif