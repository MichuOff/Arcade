/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sfml
*/

#include "Sfml.hpp"

Sfml::Sfml() : _window(sf::VideoMode(WIDTH * CHARACTER_W, HEIGTH * CHARACTER_H), "Arcade SFML")
{
    _window.setFramerateLimit(60);
    _font.loadFromFile("./ressource/Hack-Regular.ttf");
}

Sfml::~Sfml()
{
    this->_window.close();
}

IGraph::key Sfml::get_event()
{
    static int val = 0;
    val++;
    sf::Event event;
    if (!_window.isOpen())
        return (ExitArcade);
    if (!_window.pollEvent(event))
        return (NoEvent);
    if (event.type == sf::Event::Closed)
        _window.close();
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Return:
                return (Enter);
            case sf::Keyboard::Left:
                return (LeftArrow);
            case sf::Keyboard::Right:
                return (RightArrow);
            case sf::Keyboard::Up:
                return (UpArrow);
            case sf::Keyboard::Down:
                return (DownArrow);
            case sf::Keyboard::A:
                return (PrevLib);
            case sf::Keyboard::Z:
                return (NextLib);
            case sf::Keyboard::E:
                return (PrevGame);
            case sf::Keyboard::R:
                return (NextGame);
            case sf::Keyboard::T:
                return (Restart);
            case sf::Keyboard::Y:
                return (QuitGame);
            case sf::Keyboard::U:
                return (ExitArcade);
            default:
                return (NoEvent);
        }
    }
    return (NoEvent);
}

void Sfml::print_text(Map &map)
{
    sf::Text text;
    std::string str("");

    for (size_t y = 0; y < map.mapData.size(); y++) {
        for (size_t x = 0 ; x < map.mapData[y].size() ; x++)
            str += map.mapData[y][x].c;
        str += "\n";
    }
    text.setFont(_font);
    text.setString(str);
    text.setCharacterSize(FONT_SIZE);
    text.setFillColor(sf::Color::White);
    _window.draw(text);
}

void Sfml::print_map(Map &map)
{
    _window.clear();
    print_text(map);
    _window.display();
}
