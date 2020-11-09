/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFMLMain
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IGraph.hpp"

typedef enum status_e {
    SUCCESS = 0,
    ERROR = 84
} status;

//sfml.cpp
extern "C" IGraph *init();
extern "C" void stop(IGraph *object);

#endif /* !SFML_HPP_ */