/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** launch_game
*/

#include "arcade.hpp"
#include "ArcadeData.hpp"
#include "IGames.hpp"
#include "IGraph.hpp"
#include "LibLoader.hpp"
#include <unistd.h>

IGames::return_type eventsProcess(std::vector<IGraph::key> events, ArcadeData &data)
{
    for (IGraph::key event : events) {
        switch (event) {
            case IGraph::QuitGame: 
                return IGames::MENU;
            case IGraph::ExitArcade:
                return IGames::EXIT;
            case IGraph::NextGame:
                data.changeGame(1);

                return IGames::NEXT_GAME;
            case IGraph::PrevGame:
                data.changeGame(-1);
                return IGames::PREV_GAME;
            case IGraph::NextLib:
                data.changeLib(1);
                return IGames::NEXT_LIB;
            case IGraph::PrevLib:
                data.changeLib(-1);
                return IGames::PREV_LIB;
            case IGraph::Restart:
                return IGames::RESTART;
            default:
                return IGames::NOTHING;
        }
    }
    return IGames::NOTHING;
}

void launchGame(ArcadeData &data)
{
    LibLoader<IGraph> lib(LIBS_FOLDER + data.getCurrentLib());
    LibLoader<IGames> game(GAMES_FOLDER + data.getCurrentGame());
    IGraph *libData = lib.init();
    IGames *gameData = game.init();
    IGames::return_type status = IGames::NOTHING;
    IGames::return_value_t value;

    data.setCurrentScore(0);
    while (status != IGames::EXIT) {
        usleep(1000);
        std::vector<IGraph::key> events = libData->get_events();
        status = eventsProcess(events, data);
        if (status != IGames::NOTHING)
            break;
        value = gameData->process(events);
        status = value.type;
        if (status != IGames::NOTHING)
            break;
        libData->print_map(gameData->get_map());
    }
    data.setCurrentScore(std::atoi(value.value.c_str()));
    data.addScore();
    lib.stop(libData);
    game.stop(gameData);
    if (status == IGames::MENU) {
        launchMenu(data);
        launchGame(data);
        return;
    }
    if (status >= 1 && status <= 7)
        launchGame(data);
}