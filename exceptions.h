#ifndef PROIECTOOP_EXCEPTIONS_H
#define PROIECTOOP_EXCEPTIONS_H
#include<stdexcept>

class GameError: public std::runtime_error
{
public:
    explicit GameError(const std::string &arg);
};

class WeaponError: public GameError
{
public:
    explicit WeaponError(const std::string &arg);
};

class CurrencyError: public GameError
{
public:
    explicit CurrencyError(const std::string &arg);
};

#endif //PROIECTOOP_EXCEPTIONS_H
