// Mediator Pattern
// Defines an object that encapsulates how a set of objects interact, promoting
// loose coupling by preventing objects from referring to each other explicitly.

#include <iostream>
#include <string>
#include <vector>

struct Colleague;

struct ChatRoom {
    std::vector<Colleague*> members;

    void join(Colleague* c) { members.push_back(c); }
    void broadcast(const std::string& from, const std::string& message);
    void sendTo(const std::string& from, const std::string& to, const std::string& message);
};

struct Colleague {
    ChatRoom& room;
    std::string name;

    Colleague(ChatRoom& r, std::string n) : room(r), name(std::move(n)) {
        room.join(this);
    }

    void send(const std::string& message) {
        std::cout << name << " broadcasts: " << message << "\n";
        room.broadcast(name, message);
    }

    void sendTo(const std::string& target, const std::string& message) {
        std::cout << name << " -> " << target << ": " << message << "\n";
        room.sendTo(name, target, message);
    }

    void receive(const std::string& from, const std::string& message) {
        std::cout << "  [" << name << " received from " << from << "]: " << message << "\n";
    }
};

void ChatRoom::broadcast(const std::string& from, const std::string& message) {
    for (auto* m : members)
        if (m->name != from) m->receive(from, message);
}

void ChatRoom::sendTo(const std::string& from, const std::string& to,
                       const std::string& message) {
    for (auto* m : members)
        if (m->name == to) m->receive(from, message);
}

int main() {
    ChatRoom room;
    Colleague alice(room, "Alice");
    Colleague bob(room, "Bob");
    Colleague charlie(room, "Charlie");

    alice.send("Hello everyone!");
    bob.sendTo("Alice", "Hey Alice, nice to meet you!");
}
