/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Start Game (.hpp)
*/

#ifndef IPART_HPP__
#define IPART_HPP__

#include <memory>
#include <vector>
#include "IPlayer.hpp"
#include "BasicMap.hpp"

class IPart
{
    public:
        virtual ~IPart() = default;

        virtual void SetLib(std::shared_ptr<Graphique> graphic) = 0;
        virtual bool init(std::vector<std::shared_ptr<IPlayer>>, std::shared_ptr<BasicMap>) = 0;
        virtual void clear() = 0;
        virtual bool Start() = 0;
        virtual std::shared_ptr<BasicMap> GetMap() = 0;
        virtual std::vector<std::shared_ptr<IPlayer>> GetPlayer() = 0;
};

#endif