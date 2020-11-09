/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** pacman
*/

#include "pacman.hpp"
#include "Pacman.hpp"

extern "C" IGames *init()
{   
    return (new Pacman);
}

extern "C" void stop(IGames *object)
{
    delete object;
}