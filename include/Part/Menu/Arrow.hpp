/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Arrow (.hpp)
*/

#ifndef ARROW_HPP__
#define ARROW_HPP__

#include <irrlicht.h>
#include "driverChoice.h"
#include <vector>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Arrow
{
public:
    Arrow();
    ~Arrow();
    std::vector<std::string> GetVector();
    std::string GetName();

private:
    // Functions
    void InitAsset();

    // Variables
    std::string _name;
    std::vector<std::string> _typeOfAsset;
};

#endif