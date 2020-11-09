/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NCurses
*/

#include <ncurses.h>
#include "NCurses.hpp"

NCurses::NCurses()
{
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    cbreak();
}

NCurses::~NCurses()
{
    endwin();
}

IGraph::key NCurses::get_event()
{
    switch (getch()) {
        case 27:
            getch();
            switch(getch()) {
                case 65:
                    return (UpArrow);
                    break;
                case 67:
                    return (RightArrow);
                    break;
                case 68:
                    return (LeftArrow);
                    break;
                case 66:
                    return (DownArrow);
                    break;
            }
        break;
        case 10:
            return (Enter);
            break;
        case 97:
            return (PrevLib);
            break;
        case 122:
            return (NextLib);
            break;
        case 101:
            return (PrevGame);
            break;
        case 114:
            return (NextGame);
            break;
        case 116:
            return (Restart);
            break;
        case 121:
            return (QuitGame);
            break;
        case 117:
            return (ExitArcade);
            break;
        case -1:
            return (NoEvent);
            break;
        default:
            return (UnknownKey);
    }
    return (UnknownKey);
}

void NCurses::print_map(Map &map)
{
    for (size_t y = 0; y < map.mapData.size(); y++) {
        for (size_t x = 0; x < map.mapData[y].size(); x++)
            mvprintw(y,x, "%c", map.mapData[y][x].c);
    }
    refresh();
}
