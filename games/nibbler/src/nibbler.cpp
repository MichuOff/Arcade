/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** nibbler
*/

#include "nibbler.hpp"
#include "Nibbler.hpp"
#include "IGames.hpp"

extern "C" IGames *init()
{
    return (new Nibbler);
}

extern "C" void stop(IGames *object)
{
    delete object;
}