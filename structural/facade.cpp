// Facade Pattern
// Provides a simplified interface to a complex subsystem.

#include <iostream>
#include <string>

// Complex subsystem classes
struct CPU {
    void freeze() { std::cout << "CPU: freeze\n"; }
    void jump(long position) { std::cout << "CPU: jump to " << position << "\n"; }
    void execute() { std::cout << "CPU: execute\n"; }
};

struct Memory {
    void load(long position, const std::string& data) {
        std::cout << "Memory: load '" << data << "' at " << position << "\n";
    }
};

struct HardDrive {
    std::string read(long lba, int size) {
        std::cout << "HardDrive: read " << size << " bytes at lba " << lba << "\n";
        return "boot_data";
    }
};

// Facade
struct ComputerFacade {
    CPU cpu;
    Memory memory;
    HardDrive hdd;

    void start() {
        std::cout << "-- Starting computer --\n";
        cpu.freeze();
        memory.load(0, hdd.read(0, 1024));
        cpu.jump(0);
        cpu.execute();
        std::cout << "-- Computer started --\n";
    }
};

int main() {
    ComputerFacade computer;
    computer.start();
}
