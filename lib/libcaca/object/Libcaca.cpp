/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Libcaca
*/

#include "Libcaca.hpp"
#include <stdio.h>
#include <string.h>

LibCaca::LibCaca()
{
    display = caca_create_display(NULL);
    canva = caca_get_canvas(display);
    caca_set_display_title(display, "Arcade libcaca");
    //caca_set_color_ansi(canva, CACA_BLACK, CACA_RED);
}

LibCaca::~LibCaca()
{
    caca_free_display(display);
}

IGraph::key LibCaca::get_event()
{
    caca_get_event(display, CACA_EVENT_ANY, &event, 0);
    switch (caca_get_event_type(&event)) {
        case CACA_EVENT_KEY_PRESS:
            switch (caca_get_event_key_ch(&event)) {
                case CACA_KEY_UP:
                    return (UpArrow);
                case CACA_KEY_DOWN:
                    return (DownArrow);
                case CACA_KEY_LEFT:
                    return (LeftArrow);
                case CACA_KEY_RIGHT:
                    return (RightArrow);
                case 121:
                    return (QuitGame);
                case CACA_KEY_RETURN:
                    return (Enter);
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
                case 117:
                    return (ExitArcade);
                    break;
                default:
                    return (NoEvent);
            }
        case CACA_EVENT_QUIT:
            return (QuitGame);
        case CACA_EVENT_NONE:
            return (NoEvent);
        default:
            return (UnknownKey);
    }
}

void LibCaca::print_map(Map &map)
{
    for (size_t y = 0; y < map.mapData.size(); y++) {
        for (size_t x = 0; x < map.mapData[y].size(); x++) {
            caca_put_char(canva, x, y, map.mapData[y][x].c);
        }
    }
    caca_refresh_display(display);
}
