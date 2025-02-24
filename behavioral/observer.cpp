// Observer Pattern
// Defines a one-to-many dependency between objects so that when one object
// changes state, all its dependents are notified and updated automatically.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Observer {
    virtual void update(const std::string& event, double value) = 0;
    virtual ~Observer() = default;
};

struct Subject {
    std::vector<Observer*> observers;

    void subscribe(Observer* o) { observers.push_back(o); }

    void unsubscribe(Observer* o) {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    void notify(const std::string& event, double value) {
        for (auto* o : observers) o->update(event, value);
    }
};

struct StockMarket : Subject {
    std::string ticker;
    double price;

    StockMarket(std::string t, double p) : ticker(std::move(t)), price(p) {}

    void setPrice(double newPrice) {
        price = newPrice;
        notify(ticker, price);
    }
};

struct PhoneAlert : Observer {
    std::string owner;
    explicit PhoneAlert(std::string o) : owner(std::move(o)) {}
    void update(const std::string& event, double value) override {
        std::cout << "[Phone:" << owner << "] " << event << " is now $" << value << "\n";
    }
};

struct Dashboard : Observer {
    void update(const std::string& event, double value) override {
        std::cout << "[Dashboard] Updated chart for " << event << ": $" << value << "\n";
    }
};

int main() {
    StockMarket aapl("AAPL", 150.0);

    PhoneAlert alice("Alice");
    PhoneAlert bob("Bob");
    Dashboard dash;

    aapl.subscribe(&alice);
    aapl.subscribe(&bob);
    aapl.subscribe(&dash);

    aapl.setPrice(155.25);

    std::cout << "-- Bob unsubscribes --\n";
    aapl.unsubscribe(&bob);
    aapl.setPrice(148.50);
}
