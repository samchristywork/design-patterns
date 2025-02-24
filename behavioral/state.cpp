// State Pattern
// Allows an object to alter its behavior when its internal state changes.
// The object will appear to change its class.

#include <iostream>
#include <memory>

struct VendingMachine;

struct State {
    virtual void insertCoin(VendingMachine& m) = 0;
    virtual void pressButton(VendingMachine& m) = 0;
    virtual ~State() = default;
};

struct IdleState : State {
    void insertCoin(VendingMachine& m) override;
    void pressButton(VendingMachine& /*m*/) override {
        std::cout << "Insert a coin first.\n";
    }
};

struct HasCoinState : State {
    void insertCoin(VendingMachine& /*m*/) override {
        std::cout << "Coin already inserted.\n";
    }
    void pressButton(VendingMachine& m) override;
};

struct VendingMachine {
    std::unique_ptr<State> state = std::make_unique<IdleState>();
    int stock = 3;

    void setState(std::unique_ptr<State> s) { state = std::move(s); }
    void insertCoin() { state->insertCoin(*this); }
    void pressButton() { state->pressButton(*this); }
};

void IdleState::insertCoin(VendingMachine& m) {
    std::cout << "Coin inserted.\n";
    m.setState(std::make_unique<HasCoinState>());
}

void HasCoinState::pressButton(VendingMachine& m) {
    if (m.stock > 0) {
        std::cout << "Dispensing item. Stock left: " << --m.stock << "\n";
    } else {
        std::cout << "Out of stock! Returning coin.\n";
    }
    m.setState(std::make_unique<IdleState>());
}

int main() {
    VendingMachine machine;

    machine.pressButton();   // no coin
    machine.insertCoin();
    machine.insertCoin();    // already has coin
    machine.pressButton();   // dispense
    machine.pressButton();   // no coin again
    machine.insertCoin();
    machine.pressButton();
    machine.insertCoin();
    machine.pressButton();
    machine.insertCoin();
    machine.pressButton();   // out of stock
}
