/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <vector>
#include <iostream>

class Animation
{
public:
	Animation(int number);
	~Animation();

	std::vector<std::string> GetVector();
	std::string GetName();

protected:
private:
	void InitAsset();

	std::string _name;
	std::vector<std::string> _typeOfAsset;
};

#endif /* !ANIMATION_HPP_ */
