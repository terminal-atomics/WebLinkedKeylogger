#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "keylogger.hpp"

/*
** Ctor
*/

Keylogger::Keylogger(std::string logFile, std::string ftpURL = "example.com")
	: _keys(NULL),
	_logFile(logFile),
	_ftpURL(ftpURL)
{
	const char* env_p = std::getenv("PATH");
	std::string str(env_p);
	_path = str;
}

/*
** Dtor
*/
Keylogger::~Keylogger()
{
	Keylogger::saveKeys();
}

/*
** Simply gather the keys from the system and store then locally (var)
**/

void Keylogger::retrieveKeys()
{
	_keys += "a";
}

/*
** Return the list of keys for some external use I guess
*/

std::string Keylogger::getKeys()
{
	return _keys;
}

std::string randomString(uint len = 15, short loop = 0)
{
	std::string charIndex = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	uint ri[15];
	std::string rs = "";

	for (uint i = 0; i < len; ++i)
		rs += charIndex[rand() % charIndex.length()];
	if (rs.empty() && loop < 5)
		return randomString(len, loop + 1);
	else
		return rs;
}


/*
** Save keys to file
*/

void Keylogger::saveKeys()
{
	_tmpLogFile = "/tmp/keylogger_" + randomString(15, 0);
	int count;

	if (_keys.empty())
		return;

	if (_tmpLogFileStream.is_open() == false) {
		_tmpLogFileStream.open(_tmpLogFile.c_str());
	}
	for (int letter = 'a'; letter <= 'z'; letter++) {
		_tmpLogFileStream << letter << ":";
		count = 0;
		for (int i = 0; i < _keys.length(); i++) {
			if (_keys[i] == letter)
				++count;
		}
		_tmpLogFileStream << count << std::endl;
	}
	_tmpLogFileStream.close();
	if (rename(_tmpLogFile.c_str() , (_path + _logFile).c_str() ) == 0)
		std::cout << "Backup sucessful" << std::endl;
	else
		perror("Error saving backup");
}

/*
** FTP Push the keymaps
** TO BE DONE
*/

void pushKeys()
{

}