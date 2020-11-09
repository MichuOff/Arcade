/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** menu_name
*/

#include "arcade.hpp"
#include "ArcadeData.hpp"
#include "Error.hpp"
#include "LibLoader.hpp"
#include "IGames.hpp"
#include "NCurses.hpp"
#include <iostream>
#include <string>

Map &reset_tab(Map &map, int nb, std::string character)
{
    int pos = 0;
    Map::pos mpos;
    if (nb == 1)
        pos = 0;
    else if (nb == 2)
        pos = 10;
    else if (nb == 3)
        pos = 20;    

    mpos.x = 11 + pos;
    mpos.y = 7;
    map.fill_str(mpos, character);
    mpos.x = 13 + pos;
    mpos.y = 7;
    map.fill_str(mpos, character);
    mpos.x = 11 + pos;
    mpos.y = 9;
    map.fill_str(mpos, character);
    mpos.x = 13 + pos;
    mpos.y = 9;
    map.fill_str(mpos, character);
    return (map);
}

Map &choosen_letter(Map &map, int let)
{
    map = reset_tab(map, 1, " ");
    map = reset_tab(map, 2, " ");
    map = reset_tab(map, 3, " ");

    if (let == 1)
        return (reset_tab(map, 1, "*"));
    if (let == 2)
        return (reset_tab(map, 2, "*"));
    return (reset_tab(map, 3, "*"));
}

Map &add_name(Map &map, int letter, int up_or_down, arcade_t *arc, ArcadeData &data)
{
    Map::pos mpos;
    std::string letter1;
    letter1 = char(arc->let1);
    std::string letter2;
    letter2 = char(arc->let2);
    std::string letter3;
    letter3 = char(arc->let3);

    if (letter == 1) {
        map = choosen_letter(map, 1);
        if (up_or_down == 1) {
            if (arc->let1 == 90)
                arc->let1 = 65;
            else
                arc->let1++;
        }
        else if (up_or_down == -1) {
            if (arc->let1 == 65)
                arc->let1 = 90;
            else 
                arc->let1--;
        }
        letter1 = char(arc->let1);
    }
    else if (letter == 2) {
        map = choosen_letter(map, 2);
        if (up_or_down == 1) {
            if (arc->let2 == 90)
                arc->let2 = 65;
            else
                arc->let2++;
        }
        else if (up_or_down == -1) {
            if (arc->let2 == 65)
                arc->let2 = 90;
            else 
                arc->let2--;
        }
        letter2 = char(arc->let2);
    }
    else if (letter == 3) {
        map = choosen_letter(map, 3);
        if (up_or_down == 1) {
            if (arc->let3 == 90)
                arc->let3 = 65;
            else
                arc->let3++;
        }
        else if (up_or_down == -1) {
            if (arc->let3 == 65)
                arc->let3 = 90;
            else 
                arc->let3--;
        }
        letter3 = char(arc->let3);
    }
    mpos.x = 12;
    mpos.y = 8;
    map.fill_str(mpos, letter1);
    mpos.x = 22;
    mpos.y = 8;
    map.fill_str(mpos, letter2);
    mpos.x = 32;
    mpos.y = 8;
    map.fill_str(mpos, letter3);
    data.setUserName(std::string(letter1 + letter2 + letter3));
    return (map);
}

void choose_name(IGraph *graph_menu, ArcadeData &data, std::vector<IGraph::key> &keyPressed)
{
    int nb_pos = 1;
    arcade_t *arc = new(arcade_t);
    arc->let1 = 65;
    arc->let2 = 65; 
    arc->let3 = 65;
    Map test(55, 30);
    Map::pos mpos;
    bool tkt = true;

    
    mpos.x = 0;
    mpos.y = 0;
    test.fill_str(mpos, "+--------------------------------------------+");
    mpos.y = 1;
    test.fill_str(mpos, "|                                            |");
    mpos.y = 2;
    test.fill_str(mpos, "|                                            |");
    mpos.y = 3;
    test.fill_str(mpos, "|                                            |");
    mpos.y = 4;
    test.fill_str(mpos, "|              Choose your name:             |");
    mpos.y = 5;
    test.fill_str(mpos, "|                                            |");
    mpos.y = 6;
    test.fill_str(mpos, "|         _____     _____     _____          |");
    mpos.y = 7;
    test.fill_str(mpos, "|        |     |   |     |   |     |         |");
    mpos.y = 8;
    test.fill_str(mpos, "|        |     |   |     |   |     |         |");
    mpos.y = 9;
    test.fill_str(mpos, "|        |_____|   |_____|   |_____|         |");
    mpos.y = 10;
    test.fill_str(mpos, "|                                            |");
    mpos.y = 11;
    test.fill_str(mpos, "|                                            |");
    mpos.y = 12;
    test.fill_str(mpos, "+--------------------------------------------+");
    test = add_name(test, 1, 0, arc, data);
    while (tkt == true) {
        keyPressed = graph_menu->get_events();
        if (keyPressed.size() > 0) {
            if (keyPressed[0] == IGraph::UpArrow) {
                test = add_name(test, nb_pos, 1, arc, data);
            }
            else if (keyPressed[0] == IGraph::DownArrow) {
                test = add_name(test, nb_pos, -1, arc, data);
            }
            else if (keyPressed[0] == IGraph::RightArrow) {
                if (nb_pos == 3)
                    nb_pos = 3;
                else {
                    nb_pos++;
                    test = add_name(test, nb_pos, 0, arc, data);
                }
            }
            else if (keyPressed[0] == IGraph::LeftArrow) {
                if (nb_pos == 1)
                    nb_pos = 1;
                else {
                    nb_pos--;
                    test = add_name(test, nb_pos, 0, arc, data);
                }
            }
            if (keyPressed[0] == IGraph::Enter) {
                tkt = false;
                break;
            }
        }
        graph_menu->print_map(test);
    }
    delete arc;
}