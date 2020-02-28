/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Credit (.hpp)
*/

#ifndef CREDIT_HPP__
#define CREDIT_HPP__

#include "IPartMenu.hpp"

class Credit : public IPartMenu
{
public:
    Credit();
    ~Credit();
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