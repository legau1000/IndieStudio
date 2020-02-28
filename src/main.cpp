/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** main.cpp
*/

#include "../Errors/Error.hpp"
#include "../include/env/env.hpp"
#include "../include/Indie.hpp"
#include "../include/def/def.hpp"

bool checkEnv(char **env);

int main(UNUSED int ac, UNUSED char **av, char **env)
{
    Indie nwGame;
    EnvErr checkenv(env);

    if (checkenv.detectErrorEnv())
        return (84);
    return (nwGame.start());
}