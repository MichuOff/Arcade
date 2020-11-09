/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(std::string const &message) throw()
{
    if (!message.c_str())
        _message = std::string("Error!");
    else
        _message = message;
}

Error::~Error() throw()
{
}

const char *Error::what() const noexcept
{
    return _message.c_str();
}