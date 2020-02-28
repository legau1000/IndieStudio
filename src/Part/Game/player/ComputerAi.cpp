/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ComputerAi
*/

#include <time.h>
#include <memory>
#include <thread>
#include <fstream>
#include <vector>
#include "Error.hpp"
#include "ComputerAi.hpp"
#include "Ground.hpp"
#include "IBonus.hpp"
#include "Graphique.hpp"

ComputerAi::ComputerAi(const std::string &skin, const std::string &name, int number)
	: _name(name), _SkinFilePath(skin)
{
	this->InitAsset();
	this->_MOVEMENT_SPEED = 25.f;
	this->_puissance = 1;
	this->_NbMaxBombe = 1;
	this->_number = number;
	this->_alive = true;
	this->directionX.push_back(0);
	this->directionX.push_back(-1);
	this->directionX.push_back(0);
	this->directionX.push_back(1);
	this->directionZ.push_back(-1);
	this->directionZ.push_back(0);
	this->directionZ.push_back(1);
	this->directionZ.push_back(0);
	this->_panicMode = false;
	this->_indexAnimation = 0;
}

ComputerAi::~ComputerAi()
{
}

void ComputerAi::setGraphicLib(std::shared_ptr<Graphique> graphic)
{
	_graphic = graphic;
	nodePosition = _graphic->_Player[_number]->getPosition();
}

void ComputerAi::MovementPlayer(const f32 frameDeltaTime, int n, int bomb_proba)
{
	const u32 now = _graphic->_device->getTimer()->getTime();
	nodePosition = _graphic->_Player[_number]->getPosition();
	_graphic->_then = now;
	irr::core::vector3df infos = nodePosition;
	MyMoove = "  ";

	infos.X = this->_map->convertX(infos.X);
	infos.Z = this->_map->convertZ(infos.Z);
	if (n == 0 && this->CheckPositionAroundXAndZ(infos.X, infos.Z - 1) || (this->objPosition.Z > infos.Z && this->_panicMode))
	{
		_graphic->_Player[_number]->setRotation(vector3df(0, 150, 0));
		nodePosition.Z -= _MOVEMENT_SPEED * frameDeltaTime;
		MyMoove = "-Z";
	}
	else if (n == 1 && this->CheckPositionAroundXAndZ(infos.X + 1, infos.Z) || (this->objPosition.X < infos.X && this->_panicMode))
	{
		_graphic->_Player[_number]->setRotation(vector3df(0, 100, 0));
		nodePosition.X += _MOVEMENT_SPEED * frameDeltaTime;
		MyMoove = "+X";
	}
	else if (n == 2 && this->CheckPositionAroundXAndZ(infos.X, infos.Z + 1) || (this->objPosition.Z < infos.Z && this->_panicMode))
	{
		_graphic->_Player[_number]->setRotation(vector3df(0, 350, 0));
		nodePosition.Z += _MOVEMENT_SPEED * frameDeltaTime;
		MyMoove = "+Z";
	}
	else if (n == 3 && this->CheckPositionAroundXAndZ(infos.X - 1, infos.Z) || (this->objPosition.X > infos.X && this->_panicMode))
	{
		_graphic->_Player[_number]->setRotation(vector3df(0, 250, 0));
		nodePosition.X -= _MOVEMENT_SPEED * frameDeltaTime;
		MyMoove = "-X";
	}
	if (bomb_proba == 7)
	{
		if (this->_buttonBombePress == false && this->_Bombe.size() < this->_NbMaxBombe)
		{
			this->_Bombe.push_back(std::make_unique<Bombe>(this->_name + std::to_string(this->_Bombe.size()), this->_map->convertX(nodePosition.X), this->_map->convertZ(nodePosition.Z), this->_puissance));
			this->ThreadBombe(this->_name + std::to_string(this->_Bombe.size() - 1));
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
	if (nodePosition.X == this->objPosition.X && nodePosition.Z == this->objPosition.Z)
	{
		this->objPosition.X = 0;
		this->objPosition.Z = 0;
		_panicMode = false;
	}
}

void ComputerAi::SetNewGoal(const f32 frameDeltaTime)
{
	int direction = rand() % 4;
	irr::core::vector3df infos = nodePosition;

	infos.X = this->_map->convertX(infos.X);
	infos.Z = this->_map->convertZ(infos.Z);

	if (this->_panicMode && IsDangerous(infos.X, infos.Z))
	{
		MovementPlayer(frameDeltaTime, direction, 0);
	}
	else if (IsDangerous(infos.X, infos.Z))
	{
		this->_panicMode = true;
		FindAWayOut(infos.X, infos.Z);
		SetNewGoal(frameDeltaTime);
	}
	else
	{
		this->_panicMode = false;
		OffensivGoal(frameDeltaTime, direction, infos.X, infos.Z);
	}
}

bool ComputerAi::IsDangerous(int x, int z)
{
	if (CheckPositionAroundXAndZ(x, z))
	{
		return (true);
	}
	return (false);
}

void ComputerAi::FindAWayOut(int x, int z)
{
	if (!CheckPositionAroundXAndZ(x - 1, z))
	{
		this->objPosition.X = x - 1;
		this->objPosition.Z = z;
	}
	else if (!CheckPositionAroundXAndZ(x + 1, z))
	{
		this->objPosition.X = x + 1;
		this->objPosition.Z = z;
	}
	else if (!CheckPositionAroundXAndZ(x, z - 1))
	{
		this->objPosition.X = x;
		this->objPosition.Z = z - 1;
	}
	else if (!CheckPositionAroundXAndZ(x, z + 1))
	{
		this->objPosition.X = x;
		this->objPosition.Z = z + 1;
	}
}

bool ComputerAi::CheckPositionAroundXAndZ(int x, int z)
{
	int tmp_x = x;
	int tmp_z = z;

	while (!this->_map->_map[z][x]->BeWall())
	{
		if (this->_map->_map[z][x]->BombeExist() > 0)
			return (true);
		x -= 1;
	}
	x = tmp_x;
	while (!this->_map->_map[z][x]->BeWall())
	{
		if (this->_map->_map[z][x]->BombeExist() > 0)
			return (true);
		z -= 1;
	}
	z = tmp_z;
	while (!this->_map->_map[z][x]->BeWall())
	{
		if (this->_map->_map[z][x]->BombeExist() > 0)
			return (true);
		z += 1;
	}
	z = tmp_z;
	while (!this->_map->_map[z][x]->BeWall())
	{
		if (this->_map->_map[z][x]->BombeExist() > 0)
			return (true);
		x += 1;
	}
	return (false);
}

void ComputerAi::OffensivGoal(const f32 frameDeltatime, int direction, int x, int z)
{
	int bomb_proba = rand() % 50 + 1;

	if (!IsDangerous(x + this->directionX[direction], z + this->directionZ[direction]))
	{
		MovementPlayer(frameDeltatime, direction, bomb_proba);
	}
}

bool ComputerAi::StartPlay(const f32 frameDeltaTime)
{
	int index = 0;

	if (!this->_graphic->IsAssetVisible(this->_number)) {
		return (false);
	}
	while (index < this->_Bombe.size())
	{
		if (this->_Bombe[index]->Explose())
		{
			this->bombeExplode(index);
			this->_map->_map[this->_Bombe[index]->GetZ()][this->_Bombe[index]->GetX()]->SetExist(0);
			this->_graphic->destroyAsset(this->_Bombe[index]->GetName());
			this->_Bombe[index] = nullptr;
			this->_Bombe.erase(this->_Bombe.begin() + index);
		}
		index++;
	}
	SetNewGoal(frameDeltaTime);
	return (true);
}

std::vector<std::string> ComputerAi::GetVector()
{
	return (this->_typeOfAsset);
}

std::string ComputerAi::GetName()
{
	return (this->_name);
}

void ComputerAi::setMap(std::shared_ptr<BasicMap> map)
{
	this->_map = map;
}

void ComputerAi::InitAsset()
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
}

void ComputerAi::cheackPlayer(int z, int x)
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

void ComputerAi::ThreadBombe(std::string name)
{
	int x = this->_Bombe[int(this->_Bombe.size() - 1)]->GetX();
	int z = this->_Bombe[int(this->_Bombe.size() - 1)]->GetZ();

	this->_map->_map[z][x]->SetExist(this->_puissance);
	this->_graphic->create3dAsset(this->_Bombe[int(this->_Bombe.size() - 1)]->GetVector(), this->_Bombe[int(this->_Bombe.size() - 1)]->GetName(), nodePosition.X + 15, nodePosition.Y, nodePosition.Z);
}

void ComputerAi::cheackBonus()
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

void ComputerAi::deleteOnMap(int index, int z, int x)
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

void ComputerAi::bombeExplode(int idx)
{
	bool a = false;
	bool b = false;
	bool c = false;
	bool d = false;
	int index = 1;
	int indexPlayer = 0;
	int z = this->_Bombe[idx]->GetZ();
	int x = this->_Bombe[idx]->GetX();
	this->_graphic->PlaySound("bombe", false);

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

void ComputerAi::SetPuissance(int puissance)
{
	this->_puissance;
}

void ComputerAi::SetBombe(int nbBombe)
{
	this->_NbMaxBombe = nbBombe;
}

void ComputerAi::SetSpeed(f32 MOVEMENT_SPEED)
{
	this->_MOVEMENT_SPEED = MOVEMENT_SPEED;
}

int ComputerAi::GetPuissance()
{
	return (this->_puissance);
}

int ComputerAi::GetBombe()
{
	return (this->_NbMaxBombe);
}

f32 ComputerAi::GetSpeed()
{
	return (this->_MOVEMENT_SPEED);
}