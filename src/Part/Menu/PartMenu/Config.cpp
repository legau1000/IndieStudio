/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Config (.cpp)
*/

#include <irrlicht.h>
#include "Config.hpp"
#include <thread>
#include <iostream>
#include <fstream>
#include <string>

Config::Config()
{
}

Config::~Config()
{
}

void Config::init(std::shared_ptr<Graphique> graphique)
{
    this->_graphique = graphique;
}

void Config::setButton()
{
    irr::gui::IGUIButton *menu = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(50, 50, 315, 155),
        0, MENU_BUTTON);
    menu->setImage(_graphique->_driver->getTexture("media/menu/menuButton.png"));

    irr::gui::IGUIButton *playerOk1 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(400, 900, 450, 950),
        0, PLAYER1OK_BUTTON);
    playerOk1->setImage(_graphique->_driver->getTexture("media/menu/ok.png"));

    irr::gui::IGUIButton *playerOk2 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(800, 900, 850, 950),
        0, PLAYER2OK_BUTTON);
    playerOk2->setImage(_graphique->_driver->getTexture("media/menu/ok.png"));

    irr::gui::IGUIButton *playerOk3 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(1250, 900, 1300, 950),
        0, PLAYER3OK_BUTTON);
    playerOk3->setImage(_graphique->_driver->getTexture("media/menu/ok.png"));

    irr::gui::IGUIButton *playerOk4 = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(1650, 900, 1700, 950),
        0, PLAYER4OK_BUTTON);
    playerOk4->setImage(_graphique->_driver->getTexture("media/menu/ok.png"));
}

bool Config::manageButton()
{
    if (this->_graphique->_receiver.getIdButton() == "menu")
        return (true);
    return (false);
}

void Config::manageButtonPlayerConfig()
{
    if (this->_graphique->_receiver.getIdButton() == "player1ok")
    {
        getPlayer1("character1");
        writeInFileForConfigPlayer("./media/", "character1", _player1);
    }
    if (this->_graphique->_receiver.getIdButton() == "player2ok")
    {
        getPlayer2("character2");
        writeInFileForConfigPlayer("./media/", "character2", _player2);
    }
    if (this->_graphique->_receiver.getIdButton() == "player3ok")
    {
        getPlayer3("character3");
        writeInFileForConfigPlayer("./media/", "character3", _player3);
    }
    if (this->_graphique->_receiver.getIdButton() == "player4ok")
    {
        getPlayer4("character4");
        writeInFileForConfigPlayer("./media/", "character4", _player4);
    }
}

void Config::configPlayer1(float x, float y, float x2, float y2, std::string keyAsset)
{
    wchar_t message[100] = L"Indie Studio";
    int index = 1;
    int endAlphabet = 27;

    _graphique->_device->setWindowCaption(message);

    this->_box1Map.insert(std::pair<std::string, irr::gui::IGUIComboBox *>(keyAsset, this->_box1));
    this->_box1Map.find(keyAsset)->second =
        _graphique->_guienv->addComboBox(irr::core::rect<irr::s32>(x, y, x2, y2));
    while (index != endAlphabet)
    {
        swprintf(message, 100, L"%c", index + 64);
        this->_box1Map.find(keyAsset)->second->addItem(message);
        index++;
    }
}

void Config::configPlayer2(float x, float y, float x2, float y2, std::string keyAsset)
{
    wchar_t message[100] = L"Indie Studio";
    int index = 1;
    int endAlphabet = 27;

    _graphique->_device->setWindowCaption(message);
    this->_box2Map.insert(std::pair<std::string, irr::gui::IGUIComboBox *>(keyAsset, this->_box1));
    this->_box2Map.find(keyAsset)->second =
        _graphique->_guienv->addComboBox(irr::core::rect<irr::s32>(x, y, x2, y2));
    while (index != endAlphabet)
    {
        swprintf(message, 100, L"%c", index + 64);
        this->_box2Map.find(keyAsset)->second->addItem(message);
        index++;
    }
}

void Config::configPlayer3(float x, float y, float x2, float y2, std::string keyAsset)
{
    wchar_t message[100] = L"Indie Studio";
    int index = 1;
    int endAlphabet = 27;

    _graphique->_device->setWindowCaption(message);
    this->_box3Map.insert(std::pair<std::string, irr::gui::IGUIComboBox *>(keyAsset, this->_box1));
    this->_box3Map.find(keyAsset)->second =
        _graphique->_guienv->addComboBox(irr::core::rect<irr::s32>(x, y, x2, y2));
    while (index != endAlphabet)
    {
        swprintf(message, 100, L"%c", index + 64);
        this->_box3Map.find(keyAsset)->second->addItem(message);
        index++;
    }
}

void Config::configPlayer4(float x, float y, float x2, float y2, std::string keyAsset)
{
    wchar_t message[100] = L"Indie Studio";
    int index = 1;
    int endAlphabet = 27;

    _graphique->_device->setWindowCaption(message);
    this->_box4Map.insert(std::pair<std::string, irr::gui::IGUIComboBox *>(keyAsset, this->_box1));
    this->_box4Map.find(keyAsset)->second =
        _graphique->_guienv->addComboBox(irr::core::rect<irr::s32>(x, y, x2, y2));
    while (index != endAlphabet)
    {
        swprintf(message, 100, L"%c", index + 64);
        this->_box4Map.find(keyAsset)->second->addItem(message);
        index++;
    }
}

void Config::getPlayer1(std::string keyAsset)
{
    int index = 0;
    int end = 5;

    while (index != end)
    {
        int ide = this->_box1Map.find(keyAsset + std::to_string(index))->second->getSelected();
        std::wstring ws(this->_box1Map.find(keyAsset + std::to_string(index))->second->getItem(ide));
        std::string str(ws.begin(), ws.end());
        _player1.push_back(str);
        index++;
    }
}

void Config::getPlayer2(std::string keyAsset)
{
    int index = 0;
    int end = 5;

    while (index != end)
    {
        int ide = this->_box2Map.find(keyAsset + std::to_string(index))->second->getSelected();
        std::wstring ws(this->_box2Map.find(keyAsset + std::to_string(index))->second->getItem(ide));
        std::string str(ws.begin(), ws.end());
        _player2.push_back(str);
        index++;
    }
}

void Config::getPlayer3(std::string keyAsset)
{
    int index = 0;
    int end = 5;

    while (index != end)
    {
        int ide = this->_box3Map.find(keyAsset + std::to_string(index))->second->getSelected();
        std::wstring ws(this->_box3Map.find(keyAsset + std::to_string(index))->second->getItem(ide));
        std::string str(ws.begin(), ws.end());
        _player3.push_back(str);
        index++;
    }
}

void Config::getPlayer4(std::string keyAsset)
{
    int index = 0;
    int end = 5;

    while (index != end)
    {
        int ide = this->_box4Map.find(keyAsset + std::to_string(index))->second->getSelected();
        std::wstring ws(this->_box4Map.find(keyAsset + std::to_string(index))->second->getItem(ide));
        std::string str(ws.begin(), ws.end());
        _player4.push_back(str);
        index++;
    }
}

void Config::writeInFileForConfigPlayer(const std::string &path, std::string character, std::vector<std::string> player)
{
    std::string const file(path + character + "/config.txt");
    std::ofstream content(file.c_str());

    content << player[0] << std::endl;
    content << player[1] << std::endl;
    content << player[2] << std::endl;
    content << player[3] << std::endl;
    content << player[4] << std::endl;
}

void Config::setScroll()
{
    configPlayer1(400, 500, 450, 550, "character10");
    configPlayer1(400, 580, 450, 630, "character11");
    configPlayer1(400, 670, 450, 720, "character12");
    configPlayer1(400, 760, 450, 810, "character13");
    configPlayer1(400, 850, 450, 900, "character14");
    configPlayer2(800, 500, 850, 550, "character20");
    configPlayer2(800, 580, 850, 630, "character21");
    configPlayer2(800, 670, 850, 720, "character22");
    configPlayer2(800, 760, 850, 810, "character23");
    configPlayer2(800, 850, 850, 900, "character24");
    configPlayer3(1250, 500, 1300, 550, "character30");
    configPlayer3(1250, 580, 1300, 630, "character31");
    configPlayer3(1250, 670, 1300, 720, "character32");
    configPlayer3(1250, 760, 1300, 810, "character33");
    configPlayer3(1250, 850, 1300, 900, "character34");
    configPlayer4(1650, 500, 1700, 550, "character40");
    configPlayer4(1650, 580, 1700, 630, "character41");
    configPlayer4(1650, 670, 1700, 720, "character42");
    configPlayer4(1650, 760, 1700, 810, "character43");
    configPlayer4(1650, 850, 1700, 900, "character44");
}

bool Config::loop()
{
    this->_graphique->_guienv->clear();
    setButton();
    setScroll();

    while (_graphique->_device->run())
    {

        _graphique->_driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
        this->_graphique->create2dAsset("./media/menu/configScene.png", 0, 0, 1920, 1080);
        if (manageButton())
            return (true);
        manageButtonPlayerConfig();
        _graphique->_smgr->drawAll();
        _graphique->_device->getGUIEnvironment()->drawAll();

        _graphique->_driver->endScene();
    }
    return (false);
}

int Config::GetNbPlayer()
{
    return (-1);
}

int Config::GetMap()
{
    return (-1);
}

std::string Config::GetSave()
{
    return ("");
}
