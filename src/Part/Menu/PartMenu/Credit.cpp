/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Credit (.cpp)
*/

#include "Credit.hpp"

Credit::Credit()
{
}

Credit::~Credit()
{
}

void Credit::setButton()
{
    irr::gui::IGUIButton *menu = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(50, 50, 315, 155),
        0, MENU_BUTTON);
    menu->setImage(_graphique->_driver->getTexture("media/menu/menuButton.png"));
}

bool Credit::manageButton()
{
    if (this->_graphique->_receiver.getIdButton() == "menu")
        return (true);
    return (false);
}

void Credit::init(std::shared_ptr<Graphique> graphique)
{
    this->_graphique = graphique;
}

bool Credit::loop()
{
    this->_graphique->_guienv->clear();
    setButton();
    while (this->_graphique->_device->run())
    {
        this->_graphique->_driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
        this->_graphique->create2dAsset("./media/menu/credits.png", 0, 0, 1920, 1080);
        if (manageButton())
            return (true);
        this->_graphique->_guienv->drawAll();
        this->_graphique->_smgr->drawAll();
        this->_graphique->_driver->endScene();
    }
    return (true);
}

int Credit::GetNbPlayer()
{
    return (-1);
}

int Credit::GetMap()
{
    return (-1);
}

std::string Credit::GetSave()
{
    return ("");
}
