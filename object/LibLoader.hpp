/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibLoader
*/

#ifndef LIBLOADER_HPP_
#define LIBLOADER_HPP_

#include "Error.hpp"
#include <dlfcn.h>
#include <iostream>

template<typename type>
class LibLoader {
    public:
        //Constructor && destructor
        LibLoader(const std::string &sharedLib):
        _name(sharedLib)
        {
            char *textError = NULL;

            dlerror();
            this->_sharedLib = dlopen(sharedLib.c_str(), RTLD_LAZY);
            textError = dlerror();
            if (textError)
                throw(Error(std::string(textError)));
            this->init = (type *(*)())dlsym(this->_sharedLib, "init");
            textError = dlerror();
            if (textError)
                throw(Error(std::string(textError)));
            this->stop = (void(*)(type *))dlsym(this->_sharedLib, "stop");
            textError = dlerror();
            if (textError)
                throw(Error(std::string(textError)));
        };
        ~LibLoader()
        {
            char *textError = NULL;

            if (this->_sharedLib) {
                dlclose(this->_sharedLib);
                textError = dlerror();
                if (textError)
                    std::cerr << "Error: ~LibLoader" << std::endl;
            }
        };
        LibLoader<type> &changeLib(const std::string &sharedLib)
        {
            char *textError = NULL;

            if (this->_sharedLib) {
                dlclose(this->_sharedLib);
                textError = dlerror();
                if (textError)
                    std::cerr << "Error: ~LibLoader" << std::endl;
            }
            _name = sharedLib;
            dlerror();
            this->_sharedLib = dlopen(_name.c_str(), RTLD_LAZY);
            textError = dlerror();
            if (textError)
                throw(Error(std::string(textError)));
            this->init = (type *(*)())dlsym(this->_sharedLib, "init");
            textError = dlerror();
            if (textError)
                throw(Error(std::string(textError)));
            this->stop = (void(*)(type *))dlsym(this->_sharedLib, "stop");
            textError = dlerror();
            if (textError)
                throw(Error(std::string(textError)));
            return (*this);
        };

        //Var
        type *(*init)();
        void (*stop)(type *);

    protected:
    private:
        void *_sharedLib;
        std::string _name;
};

#endif /* !LIBLOADER_HPP_ */
