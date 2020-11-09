/*
** EPITECH PROJECT, 2020
** menu
** File description:
** menu
*/

#include "arcade.hpp"
#include "ArcadeData.hpp"
#include "Error.hpp"
#include "LibLoader.hpp"
#include "IGames.hpp"
#include "IGraph.hpp"
#include "NCurses.hpp"
#include <iostream>
#include <string>

std::string format_lib(std::string str)
{   
    int pos = str.find("arcade_");
    str = str.substr(0, str.length() - 3); 
    std::string sub = str.substr(pos + 7);
    
    return sub;
}

IGames::return_type lib_choose(ArcadeData &data, Map::pos &cursor)
{
    if (cursor.x == 10) {
        data.setCurrentGame(data.getGames()[cursor.y - 12]);
        data.setCurrentGame(data.getCurrentGame().substr(data.getCurrentGame().rfind("/") + 1));
        return IGames::CHANGE_GAME;
    }
    if (cursor.x == 30) {
        data.setCurrentLib(data.getLibs()[cursor.y - 12]);
        data.setCurrentLib(data.getCurrentLib().substr(data.getCurrentLib().rfind("/") + 1));
        return IGames::CHANGE_LIB;
    }

    return IGames::NOTHING;
}

int check_line(Map &menu, int b, int a)
{
    if (a < 0 || b < 0)
        return 0;
    if (menu.mapData.size() < (size_t)a)
        return 0;
    if (menu.mapData.at(a).size() < (size_t)b)
        return 0;
    if (menu.mapData.at(a).at(b).c == ' ')
        return 0;
    
    return 1;
}

IGames::return_type gestion_event(Map &menu, Map::pos &cursor, ArcadeData &data, std::vector<IGraph::key> &keyPressed)
{
    if (keyPressed.empty())
        return IGames::NOTHING;
    
    if (keyPressed[0] == IGraph::UpArrow) {
        menu.fill_str(cursor, " ");
        if (check_line(menu, cursor.x + 2, cursor.y - 1))
            cursor.y--;
    }
    else if (keyPressed[0] == IGraph::DownArrow) {
        menu.fill_str(cursor, " ");
        if (check_line(menu, cursor.x + 2, cursor.y + 1))
            cursor.y++;
    }
    else if (keyPressed[0] == IGraph::RightArrow) {
        menu.fill_str(cursor, " ");
        if (check_line(menu, cursor.x + 22, cursor.y))
            cursor.x += 20;
    }
    else if (keyPressed[0] == IGraph::LeftArrow) {
        menu.fill_str(cursor, " ");
        if (check_line(menu, cursor.x - 18, cursor.y))
            cursor.x -= 20;
    }

    if (keyPressed[0] == IGraph::Enter)
        return lib_choose(data, cursor);
    if (keyPressed[0] == IGraph::QuitGame) 
        return IGames::EXIT;
    
    return IGames::NOTHING;
}

Map &init_map(Map &menu, ArcadeData &data)
{
    Map::pos mpos = {8, 2};

    menu.fill_str(Map::pos{0, 0}, "+-----------------------------------------------------+");
    for (int i = 1; i < 29; i++) {
        menu.fill_str(Map::pos{0, i}, "|                                                     |");
    }
    menu.fill_str(mpos, "                             _      ");
    mpos.y++;
    menu.fill_str(mpos, "     /\\                     | |     ");
    mpos.y++;
    menu.fill_str(mpos, "    /  \\   _ __ ___ __ _  __| | ___ ");
    mpos.y++;
    menu.fill_str(mpos, "   / /\\ \\ | '__/ __/ _` |/ _` |/ _ \\");
    mpos.y++;
    menu.fill_str(mpos, "  / ____ \\| | | (_| (_| | (_| |  __/");
    mpos.y++;
    menu.fill_str(mpos, " /_/    \\_\\_|  \\___\\__,_|\\__,_|\\___|");
    mpos.y++;
    menu.fill_str(Map::pos{0, 29}, "+-----------------------------------------------------+");
    
    mpos = Map::pos{12, 10};
    menu.fill_str(mpos, "GAMES:");
    mpos.y += 2;
    for (size_t i = 0; i < data.getGames().size(); i++, mpos.y++)
        menu.fill_str(mpos, format_lib(data.getGames().at(i)));

    mpos = Map::pos{32, 10};
    menu.fill_str(mpos, "LIB:");
    mpos.y += 2;
    for (size_t i = 0; i < data.getLibs().size(); i++, mpos.y++)
        menu.fill_str(mpos, format_lib(data.getLibs().at(i)));
    
    return menu;
}

void display_menu(IGraph **graph_menu, ArcadeData &data, LibLoader<IGraph> &lib)
{
    Map menu(55, 30);
    std::vector<IGraph::key> keyPressed;
    Map::pos cursor = Map::pos{10, 12};
    IGames::return_type value = IGames::NOTHING;

    menu = init_map(menu, data);
    while (value != IGames::EXIT && value != IGames::CHANGE_GAME) {
        keyPressed = (*graph_menu)->get_events();
        value = gestion_event(menu, cursor, data, keyPressed);
        if (value == IGames::CHANGE_LIB) {
            lib.stop(*graph_menu);
            lib.changeLib(LIBS_FOLDER + data.getCurrentLib());
            *graph_menu = lib.init();
        }
        menu.fill_str(cursor, "*");
        (*graph_menu)->print_map(menu);
    }
}