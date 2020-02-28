/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Game (.cpp)
*/

#include <time.h>
#include <memory>
#include <thread>
#include "BasicMap.hpp"
#include "Game.hpp"

Game::Game()
{
    this->_Save = std::make_unique<Save>();
}

Game::~Game()
{
}

void Game::SetLib(std::shared_ptr<Graphique> graphic)
{
    this->_graphic = graphic;
}

bool Game::init(std::vector<std::shared_ptr<IPlayer>> player, std::shared_ptr<BasicMap> map)
{
    int index = 0;

    this->_Player.clear();
    this->_Player = player;
    this->_map = nullptr;
    this->_map = map;
    while (index != int(this->_Player.size())) {
        this->_Player[index]->setGraphicLib(this->_graphic);
        this->_Player[index]->setMap(this->_map);
        index++;
    }
    this->_nbPlayer = this->_Player.size();
    this->_end = false;
    return (true);
}

void Game::PlayerPlay()
{
    const f32 frameDeltaTime = (f32)(this->_graphic->_device->getTimer()->getTime() - _graphic->_then) / 1000.f;
    int index = 0;
    int stockNbPlayer = this->_nbPlayer;

    while (index < this->_Player.size()) {
        if (this->_Player[index]->StartPlay(frameDeltaTime) == false)
            stockNbPlayer--;
        index++;
    }
    if (stockNbPlayer <= 1) {
        this->_end = true;
    }
}

bool Game::Loop()
{
    _then = _graphic->_device->getTimer()->getTime();
    setButtonInGame();

    while (this->_graphic->_device->run())
    {
        if (this->_end)
            return (this->endScreenloop());
        else
            this->PlayerPlay();
        this->_graphic->_driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
        if (manageButton()) {
            this->_graphic->_guienv->clear();
            this->_graphic->_smgr->clear();
            this->_graphic->_nodeMap.clear();
            this->_graphic->_Player.clear();
            return true;
        }
        this->_graphic->_guienv->drawAll();
        this->_graphic->_smgr->drawAll();
        this->_graphic->_driver->endScene();
    }
    return (false);
}

bool Game::Start()
{
    bool ret = false;

    this->checkSound();
    ret = this->Loop();
    this->_graphic->clear();
    this->stopSound();
    return (ret);
}

void Game::checkSound()
{
    this->_graphic->CreateSound("GameMusic", "Sound/gameMusic.ogg");
    this->_graphic->PlaySound("GameMusic", false);
    this->_graphic->CreateSound("Gam", "Sound/game.ogg");
    this->_graphic->PlaySound("Gam", true);
    this->_graphic->CreateSound("die", "Sound/die.ogg");
    this->_graphic->CreateSound("bombe", "Sound/bombe.ogg");
}

void Game::stopSound()
{
    this->_graphic->StopSound("GameMusic");
    this->_graphic->StopSound("Gam");
}

void Game::clear()
{
}

std::shared_ptr<BasicMap> Game::GetMap()
{
    return (nullptr);
}

std::vector<std::shared_ptr<IPlayer>> Game::GetPlayer()
{
    std::vector<std::shared_ptr<IPlayer>> tmp;

    return (tmp);
}

void Game::setButton()
{
    irr::gui::IGUIButton *menu = _graphic->_guienv->addButton(
        irr::core::rect<irr::s32>(800, 100, 1065, 205),
        0, MENU_BUTTON);
    menu->setImage(_graphic->_driver->getTexture("media/menu/menuButton.png"));
}

void Game::setButtonInGame()
{
    irr::gui::IGUIButton *exitGame = _graphic->_guienv->addButton(
        irr::core::rect<irr::s32>(900, 700, 1165, 805),
        0, MENU_BUTTON);
    exitGame->setImage(_graphic->_driver->getTexture("media/game/exit.png"));

    irr::gui::IGUIButton *save = _graphic->_guienv->addButton(
        irr::core::rect<irr::s32>(900, 850, 1165, 955),
        0, SAVE_BUTTON);
    save->setImage(_graphic->_driver->getTexture("media/game/save.png"));
}

void Game::sortWinnerAndLooser()
{
    this->_graphic->create2dAsset("./media/end/" + std::to_string(_survivor + 1) + ".png", 250, 350, 250, 190);
    this->_graphic->create2dAsset("./media/end/" + std::to_string(_looser[0] + 1) + ".png", 1400, 350, 250, 190);
    this->_graphic->create2dAsset("./media/end/" + std::to_string(_looser[1] + 1) + ".png", 1400, 550, 250, 190);
    this->_graphic->create2dAsset("./media/end/" + std::to_string(_looser[2] + 1) + ".png", 1400, 750, 250, 190);
}

std::string Game::addPlayer()
{
    std::string Play;
    int index = 0;

    while (index < this->_Player.size()) {
        if (this->_graphic->IsAssetVisible(index)) {
            Play.append(std::to_string(this->_Player[index]->GetPuissance()));
            Play.append("\n");
            Play.append(std::to_string(this->_Player[index]->GetBombe()));
            Play.append("\n");
            Play.append(std::to_string(this->_Player[index]->GetSpeed()));
            Play.append("\n");
        }
        index++;
    }
    return (Play);
}

bool Game::manageButton()
{
    std::string map;
    std::vector<core::vector3df> coorPlayer;
    core::vector3df data;
    int index = 0;

    if (this->_graphic->_receiver.getIdButton() == "menu")
        return true;
    if (this->_graphic->_receiver.getIdButton() == "save") {
        while (index < this->_Player.size()) {
            if (this->_graphic->IsAssetVisible(index)) {
                data.X = this->_map->convertX(this->_graphic->_Player[index]->getPosition().X);
                data.Z = this->_map->convertZ(this->_graphic->_Player[index]->getPosition().Z);
                coorPlayer.push_back(data);
            }
            index++;
        }
        map = this->_map->convertMap(coorPlayer);
        map.append(this->addPlayer());
        this->_Save->save(map);
        return  (true);
    }
    return false;
}

bool Game::endScreenloop()
{
    int index = 0;

    while (index != this->_Player.size()) {
        if (this->_graphic->IsAssetVisible(index))
            _survivor = index;
        else
            _looser.push_back(index);
        index++;
    }
    this->_graphic->_guienv->clear();
    this->_graphic->_smgr->clear();
    this->_graphic->_nodeMap.clear();
    this->setButton();

    while (this->_graphic->_device->run()) {
        this->_graphic->_driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
        this->_graphic->create2dAsset("./media/end/end.png", 0, 0, 1920, 1080);
        sortWinnerAndLooser();
        if (this->_graphic->_receiver.getIdButton() == "menu") {
            this->_graphic->_Player.clear();
            return (true);
        }
        this->_graphic->_guienv->drawAll();
        this->_graphic->_smgr->drawAll();
        this->_graphic->_driver->endScene();
    }
    return (false);
}