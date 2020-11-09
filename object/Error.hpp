/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <cerrno>
#include <cstring>
#include <exception>
#include <iostream>

class Error: public std::exception
{
    public:
        Error(std::string const &message = std::string(std::string("Error: ") + std::string(std::strerror(errno)))) throw();
        virtual ~Error() throw();
        const char *what() const noexcept override;

    private:
        std::string _message;
};

#endif /* !ERROR_HPP_ */
