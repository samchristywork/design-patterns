// Singleton Pattern
// Ensures a class has only one instance and provides a global access point to it.

#include <iostream>
#include <string>

class Logger {
public:
    static Logger& instance() {
        static Logger inst;
        return inst;
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << "\n";
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger() { std::cout << "Logger created\n"; }
};

int main() {
    Logger::instance().log("Application started");
    Logger::instance().log("Doing some work");

    Logger& a = Logger::instance();
    Logger& b = Logger::instance();
    std::cout << "Same instance: " << (&a == &b ? "yes" : "no") << "\n";
}
