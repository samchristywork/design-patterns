// Factory Method Pattern
// Defines an interface for creating an object, but lets subclasses decide which
// class to instantiate.

#include <iostream>
#include <memory>
#include <string>

struct Button {
    virtual void render() = 0;
    virtual ~Button() = default;
};

struct WindowsButton : Button {
    void render() override { std::cout << "Rendering Windows button\n"; }
};

struct MacButton : Button {
    void render() override { std::cout << "Rendering Mac button\n"; }
};

struct Dialog {
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual ~Dialog() = default;

    void renderDialog() {
        auto button = createButton();
        button->render();
    }
};

struct WindowsDialog : Dialog {
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
};

struct MacDialog : Dialog {
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
};

int main() {
    std::unique_ptr<Dialog> dialog;

    std::string platform = "mac";
    if (platform == "windows") {
        dialog = std::make_unique<WindowsDialog>();
    } else {
        dialog = std::make_unique<MacDialog>();
    }

    dialog->renderDialog();
}
