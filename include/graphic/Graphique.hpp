/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Graphic (.hpp)
*/

#ifndef GRAPHIQUE_HPP__
#define GRAPHIQUE_HPP__

#include <irrlicht.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Sound.hpp"
#include "driverChoice.h"
#include "Event.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Graphique
{
public:
  Graphique();
  ~Graphique();
  bool GetError();
  int loop();
  void clear();
  void CreateSound(const std::string &path, const std::string &name);
  void PlaySound(const std::string &name, bool loop);
  void StopSound(const std::string &name);
  void event(const f32 MOVEMENT_SPEED);
  bool create3dAsset(std::vector<std::string> typeOfAsset, std::string keyAsset, float x, float y, float z);
  bool create3dAssetPlayer(std::vector<std::string> typeOfAsset, std::string keyAsset, float x, float y, float z);
  bool create2dAsset(const std::string &path, float x, float y, float xScale, float yScale);

  void destroyAsset(std::string keyAsset);
  void destroyAsset(int index);

  bool IsAssetVisible(int index);
  bool IsAssetVisible(std::string key);

  bool create3dMapAsset();

  u32 _then;
  bool _err;
  IGUIEnvironment *_guienv;
  irr::IrrlichtDevice *_device;
  IVideoDriver *_driver;
  ISceneManager *_smgr;
  std::unordered_map<std::string, IGUIStaticText *>
      _text;

  IAnimatedMesh *_mesh;
  IAnimatedMeshSceneNode *_node;
  std::unordered_map<std::string, IAnimatedMesh *> _meshMap;
  std::unordered_map<std::string, IAnimatedMeshSceneNode *> _nodeMap;

  std::vector<IAnimatedMeshSceneNode *> _Player;

  Event _receiver;

private:
  //functions
  bool AlreadySoundExist(const std::string &);

  // Variable
  int _nbSound;
  Sound _Sound[10];
};

#endif