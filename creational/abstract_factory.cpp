// Abstract Factory Pattern
// Provides an interface for creating families of related objects without
// specifying their concrete classes.

#include <iostream>
#include <memory>

struct Button {
    virtual void paint() = 0;
    virtual ~Button() = default;
};

struct Checkbox {
    virtual void paint() = 0;
    virtual ~Checkbox() = default;
};

struct WindowsButton : Button {
    void paint() override { std::cout << "Windows Button\n"; }
};

struct WindowsCheckbox : Checkbox {
    void paint() override { std::cout << "Windows Checkbox\n"; }
};

struct MacButton : Button {
    void paint() override { std::cout << "Mac Button\n"; }
};

struct MacCheckbox : Checkbox {
    void paint() override { std::cout << "Mac Checkbox\n"; }
};

struct GUIFactory {
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

struct WindowsFactory : GUIFactory {
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

struct MacFactory : GUIFactory {
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};

void buildUI(GUIFactory& factory) {
    auto button = factory.createButton();
    auto checkbox = factory.createCheckbox();
    button->paint();
    checkbox->paint();
}

int main() {
    WindowsFactory winFactory;
    std::cout << "Windows UI:\n";
    buildUI(winFactory);

    MacFactory macFactory;
    std::cout << "Mac UI:\n";
    buildUI(macFactory);
}
