/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NCurseMain
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IGraph.hpp"

typedef enum status_e {
    SUCCESS = 0,
    ERROR = 84
} status;

//ncurses.cpp
extern "C" IGraph *init();
extern "C" void stop(IGraph *object);

#endif /* !NCURSES_HPP_ */