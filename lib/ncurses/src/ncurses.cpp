/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ncurses
*/

#include "ncurses.hpp"
#include "NCurses.hpp"

extern "C" IGraph *init()
{
    return (new NCurses);
}

extern "C" void stop(IGraph *object)
{
    delete object;
}