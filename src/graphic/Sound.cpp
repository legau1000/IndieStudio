/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Sound (.cpp)
*/

#include "Error.hpp"
#include "Sound.hpp"

Sound::Sound()
{
    _isUse = false;
}

Sound::~Sound()
{}

void Sound::CreateSound(const std::string &name, const std::string &path)
{
    try
    {
        if (!this->_Music.openFromFile(path))
            throw(Error(std::cerr, "Fail load music " + name));
        this->_isUse = true;
        this->_name = name;
        this->_path = path;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Sound::PlaySound(const std::string &name, bool loop)
{
    try
    {
        if (this->_isUse == false)
            throw(Error(std::cerr, "Error when start music " + name));
        this->_Music.play();
        this->_Music.setLoop(loop);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Sound::StopSound(const std::string &name)
{
    try
    {
        if (this->_isUse == false)
            throw(Error(std::cerr, "Error when stop music " + name));
        this->_Music.stop();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

bool Sound::GetUse()
{
    return (this->_isUse);
}

std::string Sound::GetName()
{
    return (this->_name);
}