/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** scora_page
*/

#include "arcade.hpp"
#include "ArcadeData.hpp"
#include "Error.hpp"
#include "LibLoader.hpp"
#include "IGames.hpp"
#include "IGraph.hpp"
#include "NCurses.hpp"
#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <chrono>

Map &disp_score(ArcadeData &data, Map &map)
{
    std::vector<std::string> scores = data.sortScores();
    std::vector<std::string>::iterator it = scores.begin();
    Map::pos mpos;

    mpos.x = 18;
    mpos.y = 9;
    map.fill_str(mpos, getSharedLibName(data.getCurrentGame()) + ":");
    mpos.x = 21;
    mpos.y += 2;
    for (int i = 0 ; i < 5 && it != scores.end() ; i++, it++) {
        map.fill_str(mpos, scores[i]);
        mpos.y++;
    }
    return map;
}

void score_page(IGraph *graph_menu, std::vector<IGraph::key> &keyPressed, ArcadeData &data)
{
    Map map(55, 30);
    Map::pos mpos;
    
    mpos.x = 0;
    mpos.y = 0;
    map.fill_str(mpos, "+--------------------------------------------+");
    mpos.y++;
    map.fill_str(mpos, "|                                            |");
    mpos.y++;
    map.fill_str(mpos, "|        ____   ____ ___  ____  _____        |");
    mpos.y++;
    map.fill_str(mpos, "|       / ___| / ___| _ ||  _ || ____|       |");
    mpos.y++;
    map.fill_str(mpos, "|       |___ \\| |  | | | | |_) |  _|         |");
    mpos.y++;
    map.fill_str(mpos, "|        ___) | |__| |_| |  _ <| |___        |");
    mpos.y++;
    map.fill_str(mpos, "|       |____/ |____|___/|_| |_|_____|       |");
    mpos.y++;
    map.fill_str(mpos, "|                                            |");
    mpos.y++;
    map.fill_str(mpos, "|                                            |");
    mpos.y++;
    map.fill_str(mpos, "|                                            |");
    mpos.y++;
    map.fill_str(mpos, "|                                            |");
    mpos.y++;
    map.fill_str(mpos, "|                 1. *** ***                 |");
    mpos.y++;
    map.fill_str(mpos, "|                 2. *** ***                 |");
    mpos.y++;
    map.fill_str(mpos, "|                 3. *** ***                 |");
    mpos.y++;
    map.fill_str(mpos, "|                 4. *** ***                 |");
    mpos.y++;
    map.fill_str(mpos, "|                 5. *** ***                 |");
    mpos.y++;
    map.fill_str(mpos, "|                                            |");
    mpos.y++;
    map.fill_str(mpos, "|                                            |");
    mpos.y++;
    map.fill_str(mpos, "+--------------------------------------------+");
    data.setScores(loadScore(getSharedLibName(data.getCurrentGame())));
    map = disp_score(data, map);
    graph_menu->print_map(map);
    while (true) {
        keyPressed = graph_menu->get_events();
        if (keyPressed.size() > 0) {
            if (keyPressed[0] == IGraph::Enter)
                break;
        }
    }
}