#include "exceptions.h"


GameError::GameError(const std::string &arg): std::runtime_error(arg){}
WeaponError::WeaponError(const std::string &arg): GameError(arg){}
CurrencyError::CurrencyError(const std::string &arg): GameError(arg){}
