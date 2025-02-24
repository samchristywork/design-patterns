// Memento Pattern
// Captures and externalizes an object's internal state so it can be restored
// later, without violating encapsulation.

#include <iostream>
#include <stack>
#include <string>

struct Memento {
    std::string state;
    explicit Memento(std::string s) : state(std::move(s)) {}
};

struct TextEditor {
    std::string text;

    void type(const std::string& words) { text += words; }

    Memento save() const { return Memento{text}; }

    void restore(const Memento& m) { text = m.state; }

    void print() const { std::cout << "Content: \"" << text << "\"\n"; }
};

struct History {
    std::stack<Memento> snapshots;

    void push(Memento m) { snapshots.push(std::move(m)); }

    bool undo(TextEditor& editor) {
        if (snapshots.empty()) return false;
        editor.restore(snapshots.top());
        snapshots.pop();
        return true;
    }
};

int main() {
    TextEditor editor;
    History history;

    editor.type("Hello");
    history.push(editor.save());
    editor.print();

    editor.type(", World");
    history.push(editor.save());
    editor.print();

    editor.type("!!!");
    editor.print();

    std::cout << "-- Undo --\n";
    history.undo(editor);
    editor.print();

    std::cout << "-- Undo --\n";
    history.undo(editor);
    editor.print();
}
