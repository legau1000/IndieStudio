/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** HowToPlay (.cpp)
*/

#include "HowToPlay.hpp"

HowToPlay::HowToPlay()
{
}

HowToPlay::~HowToPlay()
{
}

void HowToPlay::init(std::shared_ptr<Graphique> graphique)
{
    this->_graphique = graphique;
}

void HowToPlay::setButton()
{
    irr::gui::IGUIButton *menu = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(50, 50, 315, 155),
        0, MENU_BUTTON);
    menu->setImage(_graphique->_driver->getTexture("media/menu/menuButton.png"));
}

bool HowToPlay::manageButton()
{
    if (this->_graphique->_receiver.getIdButton() == "menu")
        return (true);
    return (false);
}

bool HowToPlay::loop()
{
    this->_graphique->_guienv->clear();
    setButton();
    while (this->_graphique->_device->run())
    {
        this->_graphique->_driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
        this->_graphique->create2dAsset("./media/menu/HowToPlay.png", 0, 0, 1920, 1080);
        if (manageButton())
            return (true);
        this->_graphique->_guienv->drawAll();
        this->_graphique->_smgr->drawAll();
        this->_graphique->_driver->endScene();
    }
    return (false);
}

int HowToPlay::GetNbPlayer()
{
    return (-1);
}

int HowToPlay::GetMap()
{
    return (-1);
}

std::string HowToPlay::GetSave()
{
    return ("");
}
