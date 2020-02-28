/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Graphic (.cpp)
*/

#include <fstream>

#include "Error.hpp"
#include "Graphique.hpp"
#include "Event.hpp"

// FULL CANCER
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Graphique::Graphique() : _err(false)
{
    try
    {
        _device = irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, &_receiver);
        if (!this->_device)
        {
            this->_err = true;
            throw(Error(std::cerr, "Irrlicht open window"));
        }
        this->_nbSound = 0;
        this->_then = 0;
        this->_device->setWindowCaption(L"Indie Studio");
        this->_driver = this->_device->getVideoDriver();
        this->_smgr = this->_device->getSceneManager();
        this->_guienv = this->_device->getGUIEnvironment();
        this->_text.emplace("Hello", this->_guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", rect<s32>(100, 10, 260, 22), true));
    }
    catch (Error &e)
    {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
}

bool Graphique::create3dAsset(std::vector<std::string> typeOfAsset, std::string keyAsset, float x, float y, float z)
{
    try
    {
        this->_meshMap.insert(std::pair<std::string, IAnimatedMesh *>(keyAsset, this->_mesh));
        this->_meshMap.find(keyAsset)->second = this->_smgr->getMesh(typeOfAsset[0].data());
        if (!this->_meshMap.find(keyAsset)->second)
        {
            throw(Error(std::cerr, "Error When open a 3d model"));
            this->_device->drop();
        }
        this->_nodeMap.insert(std::pair<std::string, IAnimatedMeshSceneNode *>(keyAsset, this->_node));
        this->_nodeMap.find(keyAsset)->second = this->_smgr->addAnimatedMeshSceneNode(this->_meshMap.find(keyAsset)->second);
        if (this->_nodeMap.find(keyAsset)->second)
        {
            this->_nodeMap.find(keyAsset)->second->setFrameLoop(std::stof(typeOfAsset[8]), std::stof(typeOfAsset[9]));
            this->_nodeMap.find(keyAsset)->second->setMaterialFlag(EMF_LIGHTING, true);
            this->_nodeMap.find(keyAsset)->second->setScale(vector3df(std::stof(typeOfAsset[2]), std::stof(typeOfAsset[3]), std::stof(typeOfAsset[4])));
            this->_nodeMap.find(keyAsset)->second->setPosition(vector3df(x, y, z));
            this->_nodeMap.find(keyAsset)->second->setRotation(vector3df(std::stof(typeOfAsset[5]), std::stof(typeOfAsset[6]), std::stof(typeOfAsset[7])));
            this->_nodeMap.find(keyAsset)->second->setMaterialTexture(0, this->_driver->getTexture(typeOfAsset[1].data()));
        }
        this->_smgr->addCameraSceneNode(0, vector3df(0, 140, 50), vector3df(0, -70, 10), 1, true);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool Graphique::create3dAssetPlayer(std::vector<std::string> typeOfAsset, std::string keyAsset, float x, float y, float z)
{
    try
    {
        this->_meshMap.insert(std::pair<std::string, IAnimatedMesh *>(keyAsset, this->_mesh));
        this->_meshMap.find(keyAsset)->second = this->_smgr->getMesh(typeOfAsset[0].data());
        if (!this->_meshMap.find(keyAsset)->second)
        {
            throw(Error(std::cerr, "Error When open a 3d model"));
            this->_device->drop();
        }
        this->_Player.push_back(this->_node);
        this->_Player[this->_Player.size() - 1] = this->_smgr->addAnimatedMeshSceneNode(this->_meshMap.find(keyAsset)->second);
        if (this->_Player[this->_Player.size() - 1])
        {
            this->_Player[this->_Player.size() - 1]->setFrameLoop(std::stof(typeOfAsset[8]), std::stof(typeOfAsset[9]));
            this->_Player[this->_Player.size() - 1]->setMaterialFlag(EMF_LIGHTING, true);
            this->_Player[this->_Player.size() - 1]->setScale(vector3df(std::stof(typeOfAsset[2]), std::stof(typeOfAsset[3]), std::stof(typeOfAsset[4])));
            this->_Player[this->_Player.size() - 1]->setPosition(vector3df(x, y, z));
            this->_Player[this->_Player.size() - 1]->setRotation(vector3df(std::stof(typeOfAsset[5]), std::stof(typeOfAsset[6]), std::stof(typeOfAsset[7])));
            this->_Player[this->_Player.size() - 1]->setMaterialTexture(0, this->_driver->getTexture(typeOfAsset[1].data()));
        }
        this->_smgr->addCameraSceneNode(0, vector3df(0, 100, 50), vector3df(0, 0, 0), 1, true);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool Graphique::create3dMapAsset()
{
    try
    {

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool Graphique::create2dAsset(const std::string &path, float x, float y, float xScale, float yScale)
{
    try
    {
        video::ITexture *images = _driver->getTexture(path.data());
        _driver->draw2DImage(images, core::position2d<s32>(x, y),
                             core::rect<s32>(0, 0, xScale, yScale), 0,
                             video::SColor(255, 255, 255, 255), true);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

void Graphique::destroyAsset(std::string keyAsset)
{
    _nodeMap.find(keyAsset)->second->setVisible(false);
}

void Graphique::destroyAsset(int index)
{
    this->_Player[index]->setVisible(false);
}

bool Graphique::IsAssetVisible(int index)
{
    return (this->_Player[index]->isVisible());
}

bool Graphique::IsAssetVisible(std::string keyAsset)
{
    return (_nodeMap.find(keyAsset)->second->isVisible());
}

Graphique::~Graphique()
{
    this->_device->drop();
}

bool Graphique::GetError()
{
    return (this->_err);
}

void Graphique::clear()
{
    this->_smgr->clear();
    this->_guienv->clear();
}

bool Graphique::AlreadySoundExist(const std::string &name)
{
    int index = 0;

    while (index < 10)
    {
        if (this->_Sound[index].GetName() == name)
            return (true);
        index++;
    }
    return (false);
}

void Graphique::CreateSound(const std::string &name, const std::string &path)
{
    try
    {
        if (this->_nbSound >= 10)
            throw(Error(std::cerr, "To many sound"));
        if (this->AlreadySoundExist(name))
            throw(Error(std::cerr, name + " Already exist"));
        this->_Sound[this->_nbSound].CreateSound(name, path);
        if (this->_Sound[this->_nbSound].GetUse())
            this->_nbSound++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Graphique::PlaySound(const std::string &name, bool loop)
{
    int index = 0;
    int stock = -1;

    try
    {
        while (index < 10)
        {
            if (this->_Sound[index].GetName() == name)
            {
                stock = index;
            }
            index++;
        }
        if (stock == -1)
            throw(Error(std::cerr, "Sound " + name + " is not initialized"));
        this->_Sound[stock].PlaySound(name, loop);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Graphique::StopSound(const std::string &name)
{
    int index = 0;
    int stock = -1;

    try
    {
        while (index < 10)
        {
            if (this->_Sound[index].GetName() == name)
            {
                stock = index;
            }
            index++;
        }
        if (stock == -1)
            throw(Error(std::cerr, "Sound " + name + " is not initialized"));
        this->_Sound[stock].StopSound(name);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}