/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** PreScene (.cpp)
*/

#include <irrlicht.h>
#include <thread>
#include "PreScene.hpp"

PreScene::PreScene()
{
}

PreScene::~PreScene()
{
}

void PreScene::init(std::shared_ptr<Graphique> graphique)
{
    this->_graphique = graphique;
}

void PreScene::setButton()
{
    irr::gui::IGUIButton *menu = _graphique->_guienv->addButton(
        irr::core::rect<irr::s32>(50, 50, 315, 155),
        0, MENU_BUTTON);
    menu->setImage(_graphique->_driver->getTexture("media/menu/menuButton.png"));
}

bool PreScene::manageButton()
{
    if (this->_graphique->_receiver.getIdButton() == "menu")
        return (true);
    return (false);
}

void PreScene::particuleAnimation()
{
    ps = _graphique->_smgr->addParticleSystemSceneNode(false);
    scene::IParticleEmitter *em = ps->createPointEmitter(
        core::vector3df(0.0f, -0.06f, 0.0f), // initial direction
        3000, 3000,                          // emit rate
        video::SColor(255, 255, 255, 255),   // darkest color
        video::SColor(255, 255, 255, 255),   // brightest color
        800, 2000, 19,                       // min and max age, angle
        core::dimension2df(0.5, 0.5),        // min size
        core::dimension2df(0.5, 0.5));       // max size

    ps->setEmitter(em); // this grabs the emitter
    em->drop();         // so we can drop it here without deleting it

    scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();

    ps->addAffector(paf); // same goes for the affector

    ps->setPosition(core::vector3df(0, 0, 0));
    ps->setScale(core::vector3df(0, 100, 0));
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialTexture(0, _graphique->_driver->getTexture("./media/menu/blood.jpg"));
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    ISceneNodeAnimator *sna = _graphique->_smgr->createDeleteAnimator(30000);
    ps->addAnimator(sna);
    _graphique->_smgr->addCameraSceneNode(0, vector3df(0, 0, 50), vector3df(0, 0, 0), 1, true);
}

void PreScene::checkSound()
{
    this->_graphique->CreateSound("MenuMusic1", "Sound/MenuMusic1.ogg");
    this->_graphique->PlaySound("MenuMusic1", true);
}

bool PreScene::createMonster()
{
    try
    {
        IAnimatedMesh *monster = this->_graphique->_smgr->getMesh("./media/character1/char.b3d");
        node = this->_graphique->_smgr->addAnimatedMeshSceneNode(monster);
        if (node)
        {
            node->setFrameLoop(230, 500);
            node->setMaterialFlag(EMF_LIGHTING, true);
            node->setScale(vector3df(1, 1, 1));
            node->setPosition(vector3df(-40, 0, -10));
            node->setRotation(vector3df(0, 100, 0));
            node->setMaterialTexture(0, _graphique->_driver->getTexture("./media/character1/char.jpg"));
        }
        this->_graphique->_smgr->addCameraSceneNode(0, vector3df(0, 0, 50), vector3df(0, 0, 0), 1, true);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool PreScene::loop()
{
    this->_graphique->_guienv->clear();
    setButton();
    checkSound();
    createMonster();
    particuleAnimation();

    while (_graphique->_device->run())
    {
        _graphique->_driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
        this->_graphique->create2dAsset("./media/menu/beforeGame.png", 0, 0, 1920, 1080);
        if (manageButton()) {
            node->setVisible(false);
            ps->setVisible(false);
            this->_graphique->StopSound("MenuMusic1");
            return (true);
        }
        _graphique->_smgr->drawAll();                        // draw the 3d scene
        _graphique->_device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

        _graphique->_driver->endScene();
    }
    return (false);
}
