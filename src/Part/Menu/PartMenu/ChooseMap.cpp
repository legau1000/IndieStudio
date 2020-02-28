/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** ChooseMap (.cpp)
*/

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <dlfcn.h>
#include <dirent.h>
#include "ChooseMap.hpp"

ChooseMap::ChooseMap()
{
    this->_nbMap = 0;
    this->_nbPlayer = 0;
    this->_load = "";
}

ChooseMap::~ChooseMap()
{
}

void ChooseMap::setButton()
{
    irr::gui::IGUIButton *menu = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(50, 50, 315, 155),
        0, MENU_BUTTON);
    menu->setImage(_graphique->_driver->getTexture("media/menu/menuButton.png"));

    irr::gui::IGUIButton *play = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(800, 310, 1055, 420),
        0, PLAY_BUTTON);
    play->setImage(_graphique->_driver->getTexture("media/menu/play.png"));

    irr::gui::IGUIButton *player1 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(1250, 500, 1300, 550),
        0, PLAYER1_BUTTON);
    player1->setImage(_graphique->_driver->getTexture("media/menu/1.png"));

    irr::gui::IGUIButton *player2 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(1350, 500, 1400, 550),
        0, PLAYER2_BUTTON);
    player2->setImage(_graphique->_driver->getTexture("media/menu/2.png"));

    irr::gui::IGUIButton *player3 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(1450, 500, 1500, 550),
        0, PLAYER3_BUTTON);
    player3->setImage(_graphique->_driver->getTexture("media/menu/3.png"));

    irr::gui::IGUIButton *player4 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(1550, 500, 1600, 550),
        0, PLAYER4_BUTTON);
    player4->setImage(_graphique->_driver->getTexture("media/menu/4.png"));

    irr::gui::IGUIButton *map1 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(300, 500, 350, 550),
        0, MAP1_BUTTON);
    map1->setImage(_graphique->_driver->getTexture("media/menu/1.png"));

    irr::gui::IGUIButton *map2 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(400, 500, 450, 550),
        0, MAP2_BUTTON);
    map2->setImage(_graphique->_driver->getTexture("media/menu/2.png"));

    irr::gui::IGUIButton *map3 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(500, 500, 550, 550),
        0, MAP3_BUTTON);
    map3->setImage(_graphique->_driver->getTexture("media/menu/3.png"));

    irr::gui::IGUIButton *load = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(1000, 760, 1255, 870),
        0, LOAD_BUTTON);
    load->setImage(_graphique->_driver->getTexture("media/menu/load.png"));
}

void ChooseMap::configSave()
{
    wchar_t message[100] = L"Indie Studio";
    int index = 0;

    catchAllLib();
    _graphique->_device->setWindowCaption(message);
    _box = _graphique->_guienv->addComboBox(irr::core::rect<irr::s32>(600, 800, 920, 850));
    if (_scrollSave.size() == 0) {
        swprintf(message, 100, L"NO SAVE");
        _box->addItem(message);
    } else {
        while (index < _scrollSave.size()) {
            swprintf(message, 100, L"%s", _scrollSave[index].c_str());
            _box->addItem(message);
            index++;
        }
    }
}

void ChooseMap::getSaved()
{
    int ide = _box->getSelected();
    std::wstring ws(_box->getItem(ide));
    std::string str(ws.begin(), ws.end());
    _load = str;
}

void ChooseMap::catchAllLib()
{
    DIR *rep = opendir("./DataSave/");
    struct dirent *file = nullptr;
    std::string name;

    if (rep) {
        file = readdir(rep);
        while (file) {
            name = file->d_name;
            if (name.size() > 3)
                this->_scrollSave.push_back(name);
            file = readdir(rep);
        }
        closedir(rep);
    }
}

bool ChooseMap::manageButton()
{
    if (this->_graphique->_receiver.getIdButton() == "menu")
        return (true);
    if (this->_graphique->_receiver.getIdButton() == "player1")
        _nbPlayer = 1;
    if (this->_graphique->_receiver.getIdButton() == "player2")
        _nbPlayer = 2;
    if (this->_graphique->_receiver.getIdButton() == "player3")
        _nbPlayer = 3;
    if (this->_graphique->_receiver.getIdButton() == "player4")
        _nbPlayer = 4;
    if (this->_graphique->_receiver.getIdButton() == "map1")
        _nbMap = 1;
    if (this->_graphique->_receiver.getIdButton() == "map2")
        _nbMap = 2;
    if (this->_graphique->_receiver.getIdButton() == "map3")
        _nbMap = 3;
    if (this->_graphique->_receiver.getIdButton() == "load") {
        getSaved();
        return (true);
    }
    return (false);
}

void ChooseMap::init(std::shared_ptr<Graphique> graphique)
{
    this->_graphique = graphique;
}

bool ChooseMap::loop()
{
    this->_graphique->_guienv->clear();
    setButton();
    configSave();

    this->_nbPlayer = 0;
    this->_nbMap = 0;
    this->_load = "";
    while (_graphique->_device->run()) {

        _graphique->_driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
        this->_graphique->create2dAsset("./media/menu/chooseMap.png", 0, 0, 1920, 1080);
        if (manageButton()) {
            this->_nbMap = 0;
            this->_nbPlayer = 0;
            return (true);
        }
        if (this->_graphique->_receiver.getIdButton() == "play")
            return (true);
        _graphique->_smgr->drawAll();
        _graphique->_device->getGUIEnvironment()->drawAll();

        _graphique->_driver->endScene();
    }
    return (false);
}

int ChooseMap::GetNbPlayer()
{
    int nb = this->_nbPlayer;

    return (nb);
}

int ChooseMap::GetMap()
{
    int nb = this->_nbMap;

    return (nb);
}

std::string ChooseMap::GetSave()
{
    std::string MyMap = this->_load;

    return (MyMap);
}
