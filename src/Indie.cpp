/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Start Indie (.cpp)
*/

#include <thread>
#include <iostream>
#include <memory>
#include <string>
#include "Error.hpp"
#include "Indie.hpp"
#include "IPlayer.hpp"
#include "Human.hpp"
#include "Game.hpp"
#include "Menu.hpp"

Indie::Indie() : _IsMenu(true)
{
    this->_Part.push_back(std::make_unique<Game>());
    this->_Part.push_back(std::make_unique<Menu>());
    this->_Prescene = std::make_unique<PreScene>();
}

Indie::~Indie()
{
}

std::shared_ptr<BasicMap> Indie::GetMap()
{
    return (this->_Part[!_IsMenu]->GetMap());
}

std::vector<std::shared_ptr<IPlayer>> Indie::GetPlayer()
{
    return (this->_Part[!_IsMenu]->GetPlayer());
}

bool Indie::initGraphique()
{
    try
    {
        this->_graphic = std::make_shared<Graphique>();
        if (this->_graphic->GetError())
            throw(Error(std::cerr, "Error When open window"));
        this->_Part[0]->SetLib(this->_graphic);
        this->_Part[1]->SetLib(this->_graphic);
        this->_Prescene->init(this->_graphic);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return (true);
    }
    return (false);
}

bool Indie::ChooseLunch()
{
    if (this->_Part[_IsMenu]->Start())
    {
        this->_IsMenu = !this->_IsMenu;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        this->_Part[_IsMenu]->init(this->GetPlayer(), this->GetMap());
        return (true);
    }
    return (false);
}

int Indie::start()
{
    try
    {

        if (this->initGraphique())
            throw(Error(std::cerr, "Error When init Graphique"));
        this->_Part[_IsMenu]->init(this->GetPlayer(), this->GetMap());
        if (!this->_Prescene->loop())
            return (0);
        while (this->ChooseLunch())
            ;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return (84);
    }
    return (0);
}