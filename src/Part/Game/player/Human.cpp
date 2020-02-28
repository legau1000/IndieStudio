/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** Human class (.cpp)
*/

#include <time.h>
#include <memory>
#include <thread>
#include <fstream>
#include "Error.hpp"
#include "Human.hpp"
#include "Ground.hpp"
#include "Graphique.hpp"

Human::Human(const std::string &skin, std::string name, int number)
	: _name(name), _SkinFilePath(skin)
{
	this->InitAsset();
	this->_MOVEMENT_SPEED = 25.f;
	this->_puissance = 1;
	this->_NbMaxBombe = 1;
	this->_number = number;
	this->_alive = true;
	this->_indexAnimation = 0;
	this->_buttonBombePress = false;
}

Human::~Human()
{
}

void Human::setGraphicLib(std::shared_ptr<Graphique> graphic)
{
	_graphic = graphic;
	nodePosition = _graphic->_Player[_number]->getPosition();
}

void Human::MovementPlayer(const f32 frameDeltaTime)
{
	const u32 now = _graphic->_device->getTimer()->getTime();
	nodePosition = _graphic->_Player[_number]->getPosition();
	_graphic->_then = now;
	MyMoove = "  ";

	if (_graphic->_receiver.IsKeyDown(this->_keys[0]))
	{
		_graphic->_Player[_number]->setRotation(vector3df(0, 150, 0));
		nodePosition.Z -= _MOVEMENT_SPEED * frameDeltaTime;
		MyMoove = "-Z";
	}
	else if (_graphic->_receiver.IsKeyDown(this->_keys[2]))
	{
		_graphic->_Player[_number]->setRotation(vector3df(0, 100, 0));
		nodePosition.X += _MOVEMENT_SPEED * frameDeltaTime;
		MyMoove = "+X";
	}
	else if (_graphic->_receiver.IsKeyDown(this->_keys[1]))
	{
		_graphic->_Player[_number]->setRotation(vector3df(0, 350, 0));
		nodePosition.Z += _MOVEMENT_SPEED * frameDeltaTime;
		MyMoove = "+Z";
	}
	else if (_graphic->_receiver.IsKeyDown(this->_keys[3]))
	{
		_graphic->_Player[_number]->setRotation(vector3df(0, 250, 0));
		nodePosition.X -= _MOVEMENT_SPEED * frameDeltaTime;
		MyMoove = "-X";
	}
	if (_graphic->_receiver.IsKeyDown(this->_keys[4]))
	{
		if (this->_buttonBombePress == false && this->_Bombe.size() < this->_NbMaxBombe)
		{
			this->_Bombe.push_back(std::make_unique<Bombe>(this->_name + std::to_string(this->_Bombe.size()), this->_map->convertX(nodePosition.X), this->_map->convertZ(nodePosition.Z), this->_puissance));
			this->ThreadBombe(this->_name + std::to_string(this->_Bombe.size() - 1));
			this->_buttonBombePress = true;
		}
	}
	else
	{
		this->_buttonBombePress = false;
	}
	if (MyMoove != "  " && this->_map->trymoove(nodePosition, MyMoove))
	{
		this->cheackBonus();
		_graphic->_Player[_number]->setPosition(nodePosition);
	}
}

void Human::cheackBonus()
{
	std::string stock;

	if (this->_map->_map[this->_map->convertZ(nodePosition.Z)][this->_map->convertX(nodePosition.X)]->HaveBonus())
	{
		this->_graphic->destroyAsset(this->_map->_map[this->_map->convertZ(nodePosition.Z)][this->_map->convertX(nodePosition.X)]->GetBonusName());
		stock = this->_map->_map[this->_map->convertZ(nodePosition.Z)][this->_map->convertX(nodePosition.X)]->GetBonus();
		if (stock[0] == '1')
		{
			this->_NbMaxBombe++;
		}
		else if (stock[1] == '1')
		{
			this->_puissance++;
		}
		else
		{
			this->_MOVEMENT_SPEED += 5.f;
		}
	}
}

void Human::ThreadBombe(std::string name)
{
	int x = this->_Bombe[int(this->_Bombe.size() - 1)]->GetX();
	int z = this->_Bombe[int(this->_Bombe.size() - 1)]->GetZ();

	this->_map->_map[z][x]->SetExist(this->_puissance);
	this->_graphic->create3dAsset(this->_Bombe[int(this->_Bombe.size() - 1)]->GetVector(), this->_Bombe[int(this->_Bombe.size() - 1)]->GetName(), nodePosition.X + 15, nodePosition.Y, nodePosition.Z);
}

void Human::deleteOnMap(int index, int z, int x)
{
	std::string name = this->_map->_map[z][x]->GetName();
	core::vector3df coorBloc = this->_graphic->_nodeMap.find(this->_map->_map[z][x]->GetName())->second->getPosition();

	std::shared_ptr<Ground> gnd = std::make_shared<Ground>(std::atoi(name.substr(3).data()), true);
	std::shared_ptr<Animation> animation = std::make_shared<Animation>(_indexAnimation);
	this->_graphic->create3dAsset(gnd->GetVector(), gnd->GetName(), coorBloc.X, 0, coorBloc.Z);
	this->_graphic->destroyAsset(this->_map->_map[z][x]->GetName());
	if (gnd->HaveBonus())
		this->_graphic->create3dAsset(gnd->GetBonusVector(), gnd->GetBonusName(), coorBloc.X, 0, coorBloc.Z);
	else
	{
		this->_graphic->create3dAsset(animation->GetVector(), animation->GetName(), coorBloc.X, 0, coorBloc.Z);
		ISceneNodeAnimator *sna = _graphic->_smgr->createDeleteAnimator(1000);
		_graphic->_nodeMap.find(animation->GetName())->second->addAnimator(sna);
		_indexAnimation++;
	}

	this->_map->_map[z][x] = gnd;
}

void Human::cheackPlayer(int z, int x)
{
	int index = 0;

	while (index < this->_graphic->_Player.size())
	{
		if (_AllPlayerPos[index].Z == z && _AllPlayerPos[index].X == x)
		{
			this->_graphic->PlaySound("die", false);
			this->_graphic->destroyAsset(index);
		}
		index++;
	}
}

void Human::bombeExplode(int idx)
{
	bool a = false;
	bool b = false;
	bool c = false;
	bool d = false;
	int index = 1;
	int indexPlayer = 0;
	int z = this->_Bombe[idx]->GetZ();
	int x = this->_Bombe[idx]->GetX();

	std::shared_ptr<Animation> animation = std::make_shared<Animation>(_indexAnimation);

	_AllPlayerPos.clear();
	while (indexPlayer < this->_graphic->_Player.size())
	{
		_AllPlayerPos.push_back(this->_graphic->_Player[indexPlayer]->getPosition());
		_AllPlayerPos[indexPlayer].X = this->_map->convertX(_AllPlayerPos[indexPlayer].X);
		_AllPlayerPos[indexPlayer].Z = this->_map->convertZ(_AllPlayerPos[indexPlayer].Z);
		indexPlayer++;
	}
	while (index <= this->_puissance)
	{
		if (a == false)
		{
			if (this->_map->_map[z + index][x]->BeWall() == true)
			{
				a = true;
				if (this->_map->_map[z + index][x]->BeDestroy() == true)
					deleteOnMap(index, z + index, x);
			}
			else
			{
				this->_graphic->create3dAsset(animation->GetVector(), animation->GetName(), this->_graphic->_nodeMap.find(this->_map->_map[z + index][x]->GetName())->second->getPosition().X, 0, this->_graphic->_nodeMap.find(this->_map->_map[z + index][x]->GetName())->second->getPosition().Z);
				this->_graphic->_nodeMap.find(animation->GetName())->second->setRotation(vector3df(0, 350, 0));
				ISceneNodeAnimator *sna = _graphic->_smgr->createDeleteAnimator(1000);
				_graphic->_nodeMap.find(animation->GetName())->second->addAnimator(sna);
				this->cheackPlayer(z + index, x);
			}
		}
		if (b == false)
		{
			if (this->_map->_map[z - index][x]->BeWall() == true)
			{
				b = true;
				if (this->_map->_map[z - index][x]->BeDestroy() == true)
					deleteOnMap(index, z - index, x);
			}
			else
			{
				this->_graphic->create3dAsset(animation->GetVector(), animation->GetName(), this->_graphic->_nodeMap.find(this->_map->_map[z - index][x]->GetName())->second->getPosition().X, 0, this->_graphic->_nodeMap.find(this->_map->_map[z - index][x]->GetName())->second->getPosition().Z);
				this->_graphic->_nodeMap.find(animation->GetName())->second->setRotation(vector3df(0, -180, 0));
				ISceneNodeAnimator *sna = _graphic->_smgr->createDeleteAnimator(1000);
				_graphic->_nodeMap.find(animation->GetName())->second->addAnimator(sna);
				this->cheackPlayer(z - index, x);
			}
		}
		if (c == false)
		{
			if (this->_map->_map[z][x + index]->BeWall() == true)
			{
				c = true;
				if (this->_map->_map[z][x + index]->BeDestroy() == true)
					deleteOnMap(index, z, x + index);
			}
			else
			{
				this->_graphic->create3dAsset(animation->GetVector(), animation->GetName(), this->_graphic->_nodeMap.find(this->_map->_map[z][x + index]->GetName())->second->getPosition().X, 0, this->_graphic->_nodeMap.find(this->_map->_map[z][x + index]->GetName())->second->getPosition().Z);
				this->_graphic->_nodeMap.find(animation->GetName())->second->setRotation(vector3df(0, 100, 0));
				ISceneNodeAnimator *sna = _graphic->_smgr->createDeleteAnimator(1000);
				_graphic->_nodeMap.find(animation->GetName())->second->addAnimator(sna);
				this->cheackPlayer(z, x + index);
			}
		}
		if (d == false)
		{
			if (this->_map->_map[z][x - index]->BeWall() == true)
			{
				d = true;
				if (this->_map->_map[z][x - index]->BeDestroy() == true)
					deleteOnMap(index, z, x - index);
			}
			else
			{
				this->_graphic->create3dAsset(animation->GetVector(), animation->GetName(), this->_graphic->_nodeMap.find(this->_map->_map[z][x - index]->GetName())->second->getPosition().X, 0, this->_graphic->_nodeMap.find(this->_map->_map[z][x - index]->GetName())->second->getPosition().Z);
				this->_graphic->_nodeMap.find(animation->GetName())->second->setRotation(vector3df(0, -100, 0));
				ISceneNodeAnimator *sna = _graphic->_smgr->createDeleteAnimator(1000);
				_graphic->_nodeMap.find(animation->GetName())->second->addAnimator(sna);
				this->cheackPlayer(z, x - index);
			}
		}
		index++;
	}
}

bool Human::StartPlay(const f32 frameDeltaTime)
{
	int index = 0;

	if (!this->_graphic->IsAssetVisible(this->_number))
		return (false);
	while (index < this->_Bombe.size())
	{
		if (this->_Bombe[index]->Explose())
		{
			this->bombeExplode(index);
			this->_graphic->PlaySound("bombe", false);
			this->_map->_map[this->_Bombe[index]->GetZ()][this->_Bombe[index]->GetX()]->SetExist(0);
			this->_graphic->destroyAsset(this->_Bombe[index]->GetName());
			this->_Bombe[index] = nullptr;
			this->_Bombe.erase(this->_Bombe.begin() + index);
		}
		index++;
	}
	MovementPlayer(frameDeltaTime);
	return (true);
}

void Human::InitAsset()
{
	std::string content;
	std::fstream file("./media/" + this->_name + "/char.txt", std::fstream::in);

	try
	{
		if (!file)
			throw(Error(std::cerr, "No such file or directory"));
		while (std::getline(file, content))
			this->_typeOfAsset.push_back(content);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	file.close();
	this->InitMoove();
}

void Human::InitMoove()
{
	std::string content;
	int index = 0;
	std::fstream file("./media/" + this->_name + "/config.txt", std::fstream::in);

	try
	{
		if (!file)
			throw(Error(std::cerr, "No such file or directory"));
		while (std::getline(file, content))
		{
			if (content[0] && content[0] == ' ')
			{
				this->_keys[index] = irr::KEY_SPACE;
			}
			else
			{
				this->_keys[index] = irr::EKEY_CODE(content[0]);
			}
			index++;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	file.close();
}

std::vector<std::string> Human::GetVector()
{
	return (this->_typeOfAsset);
}

std::string Human::GetName()
{
	return (this->_name);
}

void Human::setMap(std::shared_ptr<BasicMap> map)
{
	this->_map = map;
}

void Human::SetPuissance(int puissance)
{
	this->_puissance;
}

void Human::SetBombe(int nbBombe)
{
	this->_NbMaxBombe = nbBombe;
}

void Human::SetSpeed(f32 MOVEMENT_SPEED)
{
	this->_MOVEMENT_SPEED = MOVEMENT_SPEED;
}

int Human::GetPuissance()
{
	return (this->_puissance);
}

int Human::GetBombe()
{
	return (this->_NbMaxBombe);
}

f32 Human::GetSpeed()
{
	return (this->_MOVEMENT_SPEED);
}
