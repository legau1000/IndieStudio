/*
** EPITECH PROJECT, 2019
** indi_studio
** File description:
** save
*/


#ifndef SAVE_HPP_
#define SAVE_HPP_

#include <iostream>
#include <string>

class Save
{
    public:
        Save();
        ~Save();
        std::string load(std::string &path);
        void save(const std::string &map);
    private:
        std::string _mapSave;
        int _numbFiles;
};

#endif /* !SAVE_HPP_ */