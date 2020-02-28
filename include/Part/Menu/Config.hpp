/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Config (.hpp)
*/

#ifndef CONFIG_HPP__
#define CONFIG_HPP__

#include "IPartMenu.hpp"

class Config : public IPartMenu
{
public:
    Config();
    ~Config();
    void init(std::shared_ptr<Graphique> graphique);
    bool loop();
    void setButton();
    bool manageButton();
    void configPlayer1(float x, float y, float x2, float y2, std::string keyAsset);
    void configPlayer2(float x, float y, float x2, float y2, std::string keyAsset);
    void configPlayer3(float x, float y, float x2, float y2, std::string keyAsset);
    void configPlayer4(float x, float y, float x2, float y2, std::string keyAsset);
    void setScroll();
    void getPlayer1(std::string keyAsset);
    void getPlayer2(std::string keyAsset);
    void getPlayer3(std::string keyAsset);
    void getPlayer4(std::string keyAsset);
    void manageButtonPlayerConfig();
    void writeInFileForConfigPlayer(const std::string &path, std::string character, std::vector<std::string> player);
    int GetNbPlayer();
    int GetMap();
    std::string GetSave();

private:
    std::shared_ptr<Graphique> _graphique;
    std::unordered_map<std::string, irr::gui::IGUIComboBox *> _box1Map;
    std::unordered_map<std::string, irr::gui::IGUIComboBox *> _box2Map;
    std::unordered_map<std::string, irr::gui::IGUIComboBox *> _box3Map;
    std::unordered_map<std::string, irr::gui::IGUIComboBox *> _box4Map;
    irr::gui::IGUIComboBox *_box1;
    std::vector<std::string>
        _player1;
    std::vector<std::string> _player2;
    std::vector<std::string> _player3;
    std::vector<std::string> _player4;
};

#endif