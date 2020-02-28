/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Game (.cpp)
*/

#include <time.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <thread>
#include "Breakable.hpp"
#include "Ground.hpp"
#include "Metal.hpp"
#include "Rock.hpp"
#include "Menu.hpp"
#include "Credit.hpp"
#include "ChooseMap.hpp"
#include "Config.hpp"
#include "HowToPlay.hpp"
#include "ComputerAi.hpp"
#include "Error.hpp"

Menu::Menu()
{
    this->_ListPart.push_back(std::make_unique<ChooseMap>());
    this->_ListPart.push_back(std::make_unique<Config>());
    this->_ListPart.push_back(std::make_unique<HowToPlay>());
    this->_ListPart.push_back(std::make_unique<Credit>());
}

Menu::~Menu()
{
}

void Menu::SetLib(std::shared_ptr<Graphique> graphic)
{
    int index = 0;

    this->_graphic = graphic;
    while (index < (int)this->_ListPart.size())
    {
        this->_ListPart[index]->init(graphic);
        index++;
    }
}

bool Menu::init(std::vector<std::shared_ptr<IPlayer>> player, std::shared_ptr<BasicMap> map)
{
    this->_Part = false;
    return (false);
}

void Menu::setButton()
{
    irr::gui::IGUIButton *chooseMap = _graphic->_guienv->addButton(
        irr::core::rect<irr::s32>(800, 310, 1055, 420),
        0, CHOOSEMAP_BUTTON);
    chooseMap->setImage(_graphic->_driver->getTexture("media/menu/chooseMapButton.png"));
    irr::gui::IGUIButton *config = _graphic->_guienv->addButton(
        irr::core::rect<irr::s32>(800, 440, 1055, 550),
        0, CONFIG_BUTTON);
    config->setImage(_graphic->_driver->getTexture("media/menu/config.png"));
    irr::gui::IGUIButton *htp = _graphic->_guienv->addButton(
        irr::core::rect<irr::s32>(800, 570, 1055, 680),
        0, HTP_BUTTON);
    htp->setImage(_graphic->_driver->getTexture("media/menu/HTP.png"));
    irr::gui::IGUIButton *credits = _graphic->_guienv->addButton(
        irr::core::rect<irr::s32>(800, 700, 1055, 810),
        0, CREDIT_BUTTON);
    credits->setImage(_graphic->_driver->getTexture("media/menu/creditsButton.png"));
}

bool Menu::manageButton()
{
    if (this->_graphic->_receiver.getIdButton() == "chooseMap") {
        this->_ListPart[0]->loop();
        this->_graphic->_guienv->clear();
        if ((this->_ListPart[0]->GetMap() != 0 && this->_ListPart[0]->GetNbPlayer() != 0) || this->_ListPart[0]->GetSave() != "")
            return (true);
        setButton();
    }
    if (this->_graphic->_receiver.getIdButton() == "config") {
        this->_ListPart[1]->loop();
        this->_graphic->_guienv->clear();
        setButton();
    }
    if (this->_graphic->_receiver.getIdButton() == "htp") {
        this->_ListPart[2]->loop();
        this->_graphic->_guienv->clear();
        setButton();
    }
    if (this->_graphic->_receiver.getIdButton() == "credit") {
        this->_ListPart[3]->loop();
        this->_graphic->_guienv->clear();
        setButton();
    }
    return false;
}

bool Menu::Loop()
{
    this->_graphic->_guienv->clear();
    setButton();
    _graphic->_device->setEventReceiver(&_graphic->_receiver);
    while (_graphic->_device->run())
    {
        this->_graphic->_driver->beginScene(true, true, video::SColor(104, 104, 8, 8));
        this->_graphic->create2dAsset("./media/menu/background.jpg", 0, 0, 1920, 1080);
        if (this->manageButton()) {
            return true;
        }
        this->_graphic->_guienv->drawAll();
        this->_graphic->_smgr->drawAll();
        this->_graphic->_driver->endScene();
    }
    return false;
}

void Menu::checkSound()
{
    this->_graphic->CreateSound("MenuMusic", "Sound/MenuMusic.ogg");
    this->_graphic->PlaySound("MenuMusic", true);
}

void Menu::stopSound()
{
    this->_graphic->StopSound("MenuMusic");
}

bool Menu::Start()
{
    bool ret = false;

    this->checkSound();
    ret = Loop();
    this->_graphic->clear();
    this->stopSound();
    return (ret);
}

void Menu::clear()
{
}

std::vector<std::vector<std::shared_ptr<IBlock>>> Menu::InitMap()
{
    std::ifstream fileName("media/map/map" + std::to_string(this->_ListPart[0]->GetMap()) + ".txt", std::ios::in);
    std::string content;
    std::string cnt;
    int index = 0;
    int player = 0;
    int x = -100;
    int z = -70;
    std::string name;
    int nb_Player = this->_ListPart[0]->GetNbPlayer();
    std::vector<std::shared_ptr<IBlock>> LineMap;

    try {
        if (!fileName)
            throw(Error(std::cerr, "Uh-oh"));
    } catch(Error &e) {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
    while (getline(fileName, cnt)) {
        content.append(cnt);
        content.append("\n");
    }
    fileName.close();
    while (content[index] != '\0') {
        if (content[index] == '\n') {
            this->_Map.push_back(LineMap);
            LineMap.clear();
            z += 10;
            x = -100;
        } else {
            if (content[index] == '#') {
                LineMap.push_back(std::make_shared<Breakable>(index));
            } else if (content[index] == 'X') {
                LineMap.push_back(std::make_shared<Metal>(index));
            } else if (content[index] == 'R') {
                LineMap.push_back(std::make_shared<Rock>(index));
            } else {
                LineMap.push_back(std::make_shared<Ground>(index));
                if (content[index] != ' '
                && (content[index] == '1' || content[index] == '2' || content[index] == '3' || content[index] == '4')) {
                    switch (content[index]) {
                    case '1':
                        name = "character1"; break;
                    case '2':
                        name = "character2"; break;
                    case '3':
                        name = "character3"; break;
                    case '4':
                        name = "character4"; break;
                    }
                    if (content[index] - 48 <= nb_Player) {
                        this->_Player.push_back(std::make_shared<Human>("./media/" + name + "/char.txt", name, player));
                    } else {
                        this->_Player.push_back(std::make_shared<ComputerAi>("./media/" + name + "/char.txt", name, player));
                    }
                    this->_graphic->create3dAssetPlayer(this->_Player[int(this->_Player.size() - 1)]->GetVector(), this->_Player[int(this->_Player.size() - 1)]->GetName(), x, 0, z);
                    player++;
                }
            }
            this->_graphic->create3dAsset(LineMap[int(LineMap.size() - 1)]->GetVector(), LineMap[int(LineMap.size() - 1)]->GetName(), x, 0, z);
            x += 10;
        }
        index++;
    }
    return (this->_Map);
}

std::vector<std::vector<std::shared_ptr<IBlock>>> Menu::InitMapSave(std::string path)
{
    std::ifstream fileName("./DataSave/" + path, std::ios::in);
    std::string cnt;
    std::string content;
    int index = 0;
    int idx = 0;
    int nbBack = 0;
    int player = 0;
    int x = -100;
    int z = -70;
    std::string name;
    std::vector<std::shared_ptr<IBlock>> LineMap;

    try {
        if (!fileName)
            throw(Error(std::cerr, "Uh-oh"));
    } catch(Error &e) {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
    while (std::getline(fileName, cnt) && cnt.size() != 0) {
        content.append(cnt);
        content.append("\n");
    }
    while (nbBack != 13) {
        if (content[index] == '\n') {
            nbBack++;
            this->_Map.push_back(LineMap);
            LineMap.clear();
            z += 10;
            x = -100;
        } else {
            if (content[index] == '#') {
                LineMap.push_back(std::make_shared<Breakable>(index));
            } else if (content[index] == 'X') {
                LineMap.push_back(std::make_shared<Metal>(index));
            } else if (content[index] == 'R') {
                LineMap.push_back(std::make_shared<Rock>(index));
            } else {
                LineMap.push_back(std::make_shared<Ground>(index));
                if (content[index] != ' '
                && (content[index] == '1' || content[index] == '2' || content[index] == '3' || content[index] == '4')) {
                    switch (content[index]) {
                    case '1':
                        name = "character1"; break;
                    case '2':
                        name = "character2"; break;
                    case '3':
                        name = "character3"; break;
                    case '4':
                        name = "character4"; break;
                    }
                    this->_Player.push_back(std::make_shared<Human>("./media/" + name + "/char.txt", name, player));
                    this->_graphic->create3dAssetPlayer(this->_Player[int(this->_Player.size() - 1)]->GetVector(), this->_Player[int(this->_Player.size() - 1)]->GetName(), x, 0, z);
                    player++;
                }
            }
            this->_graphic->create3dAsset(LineMap[int(LineMap.size() - 1)]->GetVector(), LineMap[int(LineMap.size() - 1)]->GetName(), x, 0, z);
            x += 10;
        }
        index++;
    }
    while (idx < this->_Player.size()) {
        getline(fileName, cnt);
        try {
            if (cnt.size() == 0)
                throw(Error(std::cerr, "Uh-oh"));
        } catch(Error &e) {
            e.where() << "You threw an exception: " << e.what() << std::endl;
        }
        this->_Player[idx]->SetPuissance(std::stoi(cnt));
        getline(fileName, cnt);
        try {
            if (cnt.size() == 0)
                throw(Error(std::cerr, "Uh-oh"));
        } catch(Error &e) {
            e.where() << "You threw an exception: " << e.what() << std::endl;
        }
        this->_Player[idx]->SetBombe(std::stoi(cnt));
        getline(fileName, cnt);
        try {
            if (cnt.size() == 0)
                throw(Error(std::cerr, "Uh-oh"));
        } catch(Error &e) {
            e.where() << "You threw an exception: " << e.what() << std::endl;
        }
        this->_Player[idx]->SetSpeed(std::stoi(cnt));
        idx++;
    }
    fileName.close();
    return (this->_Map);
}

std::shared_ptr<BasicMap> Menu::GetMap()
{
    std::string MyMap = this->_ListPart[0]->GetSave();
    
    this->_map = std::make_shared<BasicMap>();
    this->_map->setGraphicLib(this->_graphic);
    this->_Map.clear();
    this->_Player.clear();
    if (MyMap == "") {
        this->_map->initMap(this->InitMap());
    } else {
        this->_map->initMap(this->InitMapSave(MyMap));
    }
    return (this->_map);
}

std::vector<std::shared_ptr<IPlayer>> Menu::GetPlayer()
{
    return (this->_Player);
}