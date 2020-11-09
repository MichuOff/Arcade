/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_test
*/

#include "Libcaca.hpp"

extern "C" IGraph *init()
{
    return (new LibCaca);
}

extern "C" void stop(IGraph *lib)
{
    delete lib;
}