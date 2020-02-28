/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Game (.hpp)
*/

#ifndef GAME_HPP__
#define GAME_HPP__

#include "save.hpp"
#include "IPart.hpp"

class Game : public IPart
{
public:
    Game();
    ~Game();
    void SetLib(std::shared_ptr<Graphique> graphic);
    bool init(std::vector<std::shared_ptr<IPlayer>>, std::shared_ptr<BasicMap>);
    void clear();
    bool Start();

    std::shared_ptr<BasicMap> GetMap();
    std::vector<std::shared_ptr<IPlayer>> GetPlayer();

private:
    // Functions
    bool Loop();
    void checkSound();
    void stopSound();
    void PlayerPlay();
    bool endScreenloop();
    void setButton();
    void setButtonInGame();
    void sortWinnerAndLooser();
    bool manageButton();
    std::string addPlayer();

    // Variables
    u32 _then;
    std::shared_ptr<Graphique> _graphic;
    std::unique_ptr<Save> _Save;
    std::vector<std::shared_ptr<IPlayer>> _Player;
    std::shared_ptr<BasicMap> _map;
    int _nbPlayer;
    bool _end;
    int _survivor;
    std::vector<int> _looser;

};

#endif