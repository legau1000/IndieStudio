/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** ChooseMap (.hpp)
*/

#ifndef CHOOSEMAP_HPP__
#define CHOOSEMAP_HPP__

#include "IPartMenu.hpp"

class ChooseMap : public IPartMenu
{
    public:
        ChooseMap();
        ~ChooseMap();
        void init(std::shared_ptr<Graphique> graphique);
        bool loop();
        void setButton();
        bool manageButton();
        int GetNbPlayer();
        int GetMap();
        void catchAllLib();
        std::string GetSave();

    private:
        void configSave();
        void getSaved();

        irr::gui::IGUIComboBox *_box;
        std::shared_ptr<Graphique> _graphique;
        int _nbPlayer;
        int _nbMap;
        std::vector<std::string> _scrollSave;
        std::string _load;
};

#endif