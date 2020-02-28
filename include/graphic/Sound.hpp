/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Sound (.hpp)
*/

#ifndef SOUND_HPP__
#define SOUND_HPP__

#include <iostream>
#include <unordered_map>
#include <SFML/Audio.hpp>

class Sound
{
    public:
        Sound();
        ~Sound();
        void CreateSound(const std::string &path, const std::string &name);
        void PlaySound(const std::string &path, bool loop);
        void StopSound(const std::string &path);
        std::string GetName();
        bool GetUse();

    private:
        // Variable
        sf::Music _Music;
        std::string _name;
        std::string _path;
        bool _isUse;

};

#endif