/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** IPartMenu (.hpp)
*/

#ifndef IPARTMENU_HPP__
#define IPARTMENU_HPP__

#include <iostream>
#include "Graphique.hpp"

class IPartMenu
{
    public:
        virtual ~IPartMenu() = default;
        virtual void init(std::shared_ptr<Graphique> graphique) = 0;
        virtual bool loop() = 0;
        virtual int GetNbPlayer() = 0;
        virtual int GetMap() = 0;
        virtual std::string GetSave() = 0;

    private:

};

#endif