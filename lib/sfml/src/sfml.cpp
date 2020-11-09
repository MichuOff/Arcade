/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sfml
*/

#include "sfml.hpp"
#include "Sfml.hpp"

extern "C" IGraph *init()
{
    return (new Sfml);
}

extern "C" void stop(IGraph *object)
{
    delete object;
}