// Chain of Responsibility Pattern
// Passes a request along a chain of handlers, where each handler decides to
// process the request or pass it to the next handler.

#include <iostream>
#include <memory>
#include <string>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

struct Logger {
    LogLevel level;
    std::unique_ptr<Logger> next;

    explicit Logger(LogLevel l) : level(l) {}

    Logger& setNext(std::unique_ptr<Logger> n) {
        next = std::move(n);
        return *next;
    }

    void log(LogLevel msgLevel, const std::string& message) {
        if (msgLevel >= level) {
            write(message);
        }
        if (next) {
            next->log(msgLevel, message);
        }
    }

    virtual void write(const std::string& message) = 0;
    virtual ~Logger() = default;
};

struct ConsoleLogger : Logger {
    explicit ConsoleLogger(LogLevel l) : Logger(l) {}
    void write(const std::string& msg) override {
        std::cout << "[CONSOLE] " << msg << "\n";
    }
};

struct FileLogger : Logger {
    explicit FileLogger(LogLevel l) : Logger(l) {}
    void write(const std::string& msg) override {
        std::cout << "[FILE]    " << msg << "\n";
    }
};

struct EmailLogger : Logger {
    explicit EmailLogger(LogLevel l) : Logger(l) {}
    void write(const std::string& msg) override {
        std::cout << "[EMAIL]   " << msg << "\n";
    }
};

int main() {
    auto console = std::make_unique<ConsoleLogger>(LogLevel::DEBUG);
    auto file    = std::make_unique<FileLogger>(LogLevel::WARNING);
    auto email   = std::make_unique<EmailLogger>(LogLevel::ERROR);

    // Build chain: console -> file -> email
    file->setNext(std::move(email));
    console->setNext(std::move(file));

    std::cout << "-- DEBUG message --\n";
    console->log(LogLevel::DEBUG, "Entering function foo()");

    std::cout << "-- WARNING message --\n";
    console->log(LogLevel::WARNING, "Disk usage above 80%");

    std::cout << "-- ERROR message --\n";
    console->log(LogLevel::ERROR, "Database connection lost");
}
