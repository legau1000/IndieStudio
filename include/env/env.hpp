/*
** EPITECH PROJECT, 2019
** Indie Studio
** File description:
** detect env error (.hpp)
*/

#ifndef ENV_HPP__
#define ENV_HPP__

class EnvErr
{
    public:
        EnvErr(char **env);
        ~EnvErr();
        bool detectErrorEnv();
        bool detectPath();

    protected:

    private:
        char **_env;
};

#endif