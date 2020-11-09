/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGraph
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

#include "Map.hpp"

class IGraph {
    public:
        enum key {
            UpArrow,
            DownArrow,
            LeftArrow,
            RightArrow,
            Enter,
            QuitGame,
            ExitArcade,
            UnknownKey,
            NextGame,
            PrevGame,
            NextLib,
            PrevLib,
            Restart,
            NoEvent
        };

        virtual ~IGraph() = default;

        virtual key get_event() = 0;
        virtual void print_map(Map &map) = 0;

        std::vector<key> get_events()
        {
            std::vector<key> event_list;
            key event = get_event();

            while (event != NoEvent && event != QuitGame && event != ExitArcade) {
                event_list.push_back(event);
                event = get_event();
            }
            if (event == QuitGame || event == ExitArcade)
                event_list.push_back(event);
            return (event_list);
        };
    protected:
    private:
};

#endif /* !IGRAPH_HPP_ */
