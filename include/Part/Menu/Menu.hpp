/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Menu (.hpp)
*/

#ifndef MENU_HPP__
#define MENU_HPP__

#include "IPart.hpp"
#include "IPartMenu.hpp"
#include "Human.hpp"
#include "Arrow.hpp"
#include "IBlock.hpp"
#include "BasicMap.hpp"
#include "ComputerAi.hpp"

class Menu : public IPart
{
public:
    Menu();
    ~Menu();
    void SetLib(std::shared_ptr<Graphique> graphic);
    bool init(std::vector<std::shared_ptr<IPlayer>>, std::shared_ptr<BasicMap>);
    void clear();
    bool Start();
    void setButton();
    bool manageButton();

    std::shared_ptr<BasicMap> GetMap();
    std::vector<std::shared_ptr<IPlayer>> GetPlayer();

private:
    // Functions
    bool Loop();
    void checkSound();
    void stopSound();
    std::vector<std::vector<std::shared_ptr<IBlock>>> InitMap();
    std::vector<std::vector<std::shared_ptr<IBlock>>> InitMapSave(std::string MyMap);

    // Variables
    std::shared_ptr<Graphique> _graphic;
    std::vector<std::unique_ptr<IPartMenu>> _ListPart;
    std::vector<std::shared_ptr<IPlayer>> _Player;
    std::vector<std::vector<std::shared_ptr<IBlock>>> _Map;
    std::shared_ptr<BasicMap> _map;

    bool _Part;
};

#endif