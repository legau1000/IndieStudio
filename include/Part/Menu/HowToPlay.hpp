/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** HowToPlay (.hpp)
*/

#ifndef HOWTOPLAY_HPP__
#define HOWTOPLAY_HPP__

#include "IPartMenu.hpp"

class HowToPlay : public IPartMenu
{
public:
    HowToPlay();
    ~HowToPlay();
    void init(std::shared_ptr<Graphique> graphique);
    bool loop();
    void setButton();
    bool manageButton();
    int GetNbPlayer();
    int GetMap();
    std::string GetSave();

private:
    std::shared_ptr<Graphique> _graphique;
};

#endif