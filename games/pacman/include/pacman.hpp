/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGames.hpp"

typedef enum status_e {
    SUCCESS = 0,
    ERROR = 84
} status;

//pacman.cpp
extern "C" IGames *init();
extern "C" void stop(IGames *object);

#endif /* !PACMAN_HPP_ */
