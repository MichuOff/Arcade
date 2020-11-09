/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** MapChar
*/

#ifndef MAPCHAR_HPP_
#define MAPCHAR_HPP_

class MapChar {
    public:
        MapChar() : c(' ') {};
        ~MapChar() {};

        enum Color {
            Black,
            Red,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White,
        };
        char c;
    protected:
    private:
};

#endif /* !MAPCHAR_HPP_ */
