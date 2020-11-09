/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sfml
*/

#ifndef SFML_HPP_OBJECT_
#define SFML_HPP_OBJECT_

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "IGraph.hpp"

static const int CHARACTER_H = 20;
static const int CHARACTER_W = 15;
static const int FONT_SIZE = 15;
static const int WIDTH = 55;
static const int HEIGTH = 30;

class Sfml : public IGraph {
    public:
        Sfml();
        ~Sfml();
        key get_event();
        void print_map(Map &map);
        void print_text(Map &map);
    protected:
    private:
        sf::RenderWindow _window;
        sf::Font _font;
};

#endif /* !SFML_HPP_OBJECT_ */