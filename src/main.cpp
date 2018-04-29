#include <memory>
#include "keylogger.hpp"

void parse_flags(char **av)
{

}

int main(int ac, char **av)
{
	if (ac == 1) {
		run();
	} else {
		parse_flags(av);
	}
	auto prog = std::unique_ptr<Keylogger>();

}