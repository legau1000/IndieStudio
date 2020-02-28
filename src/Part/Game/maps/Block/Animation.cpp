/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Animation
*/

#include <fstream>
#include "Animation.hpp"
#include "Error.hpp"

Animation::Animation(int number)
{
	this->_name = "animation" + std::to_string(number);
	this->InitAsset();
}

std::vector<std::string> Animation::GetVector()
{
	return (this->_typeOfAsset);
}

std::string Animation::GetName()
{
	return (this->_name);
}
void Animation::InitAsset()
{
	std::string content;
	std::fstream file("./media/animation/spider.txt", std::fstream::in);

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
Animation::~Animation()
{
}
