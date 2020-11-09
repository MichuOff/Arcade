/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Libcaca
*/

#ifndef LIBCACA_HPP_
#define LIBCACA_HPP_

#include <caca.h>
#include "IGraph.hpp"

class LibCaca : public IGraph {
    public:
        LibCaca();
        ~LibCaca();
        key get_event();
        void print_map(Map &map);
        void print_char(MapChar &map_char);

    protected:
        caca_display_t *display;
        caca_canvas_t *canva;
        caca_event_t event;
};

#endif /* !LIBCACA_HPP_ */