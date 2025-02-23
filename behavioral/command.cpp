// Command Pattern
// Encapsulates a request as an object, allowing parameterization, queuing,
// logging, and undo/redo operations.

#include <iostream>
#include <memory>
#include <stack>
#include <string>

struct TextEditor {
    std::string text;
    void append(const std::string& s) { text += s; }
    void eraseLast(int n) { if (n <= (int)text.size()) text.erase(text.size() - n); }
    void print() const { std::cout << "Text: \"" << text << "\"\n"; }
};

struct Command {
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

struct AppendCommand : Command {
    TextEditor& editor;
    std::string added;

    AppendCommand(TextEditor& e, std::string s) : editor(e), added(std::move(s)) {}
    void execute() override { editor.append(added); }
    void undo() override { editor.eraseLast(added.size()); }
};

struct CommandHistory {
    std::stack<std::unique_ptr<Command>> history;

    void execute(std::unique_ptr<Command> cmd) {
        cmd->execute();
        history.push(std::move(cmd));
    }

    void undo() {
        if (!history.empty()) {
            history.top()->undo();
            history.pop();
        }
    }
};

int main() {
    TextEditor editor;
    CommandHistory history;

    history.execute(std::make_unique<AppendCommand>(editor, "Hello"));
    editor.print();

    history.execute(std::make_unique<AppendCommand>(editor, ", World"));
    editor.print();

    history.execute(std::make_unique<AppendCommand>(editor, "!"));
    editor.print();

    std::cout << "-- Undo --\n";
    history.undo();
    editor.print();

    std::cout << "-- Undo --\n";
    history.undo();
    editor.print();
}
