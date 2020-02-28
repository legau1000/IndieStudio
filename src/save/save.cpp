/*
** EPITECH PROJECT, 2019
** indi_studio
** File description:
** save
*/

#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include "Error.hpp"
#include "save.hpp"

Save::Save()
{
    DIR * rep = opendir("./DataSave/");
    struct dirent *file = nullptr;

    this->_numbFiles = 0;
    try {
        if (!rep)
            throw(Error(std::cerr, "when opening ./DataSave/ directory"));
        file = readdir(rep);
        while(file) {
            _numbFiles++;
            file = readdir(rep);
        }
    } catch(Error &e) {
        e.where() << "You threw an exception: " << e.what() << std::endl;
    }
    closedir(rep);
}

Save::~Save()
{}

std::string Save::load(std::string &path)
{
    std::string content;
    std::fstream file(path, std::fstream::in);

    try
    {
        if (!file)
            throw(Error(std::cerr, "No such file or directory"));
        while (std::getline(file, content)) {
            this->_mapSave.append(content);
            this->_mapSave.append("\n");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    file.close();
    return(_mapSave);
}

void Save::save(const std::string &map)
{
    std::ofstream fileObject;
    fileObject.open("./DataSave/.sauvegarde_"+ std::to_string(_numbFiles) +".txt", std::ios::app);
    
    try
    {
        if (!fileObject)
            throw(Error(std::cerr, "No such file or directory"));
        fileObject.clear();
        fileObject << map;
        _numbFiles++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    
    fileObject.close();
}