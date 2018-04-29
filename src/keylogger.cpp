#include "keylogger.hpp"

/*
** Ctor
*/

Keylogger::Keylogger()
	: keys(NULL)
{

}

/*
** Dtor
*/
Keylogger::~Keylogger()
{

}

/*
** Simply gather the keys from the system and store then locally (var)
**/

void Keylogger::retrieveKeys()
{

}

std::string Keylogger::getKeys() noexcept
{
	return _keys;
}

void saveKeys()
{

}

void pushKeys()
{

}