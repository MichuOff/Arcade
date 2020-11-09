/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_OBJECT_
#define NCURSES_HPP_OBJECT_

#include "IGraph.hpp"

class NCurses : public IGraph {
    public:
        NCurses();
        ~NCurses();
        key get_event();
        void print_map(Map &map);
    protected:
    private:
};

#endif /* !NCURSES_HPP_OBJECT_ */
