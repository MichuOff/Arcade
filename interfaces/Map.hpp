/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <iostream>
#include "MapChar.hpp"

class Map {
    public:
        struct pos {
            int x;
            int y;
        };

        Map(int width, int heigth) {
            for (int y = 0; y < heigth; y++) {
                std::vector<MapChar> line;
                for (int x = 0; x  < width; x++)
                    line.push_back(MapChar());
                mapData.push_back(line);
            }
        };
        ~Map() {};

        std::vector<std::vector<MapChar>> mapData;

        void fill_str(pos mpos, std::string str)
        {
            for (size_t x = 0; str[x] != '\0' && x < mapData[mpos.y].size(); x++)
                mapData[mpos.y][mpos.x + x].c = str[x];
        }
    protected:
    private:
};

#endif /* !MAP_HPP_ */
