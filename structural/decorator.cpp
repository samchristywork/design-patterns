// Decorator Pattern
// Attaches additional responsibilities to an object dynamically, providing a
// flexible alternative to subclassing for extending functionality.

#include <iostream>
#include <memory>
#include <string>

struct Coffee {
    virtual std::string description() const = 0;
    virtual double cost() const = 0;
    virtual ~Coffee() = default;
};

struct Espresso : Coffee {
    std::string description() const override { return "Espresso"; }
    double cost() const override { return 1.99; }
};

struct CoffeeDecorator : Coffee {
    std::unique_ptr<Coffee> base;
    explicit CoffeeDecorator(std::unique_ptr<Coffee> b) : base(std::move(b)) {}
};

struct Milk : CoffeeDecorator {
    explicit Milk(std::unique_ptr<Coffee> b) : CoffeeDecorator(std::move(b)) {}
    std::string description() const override { return base->description() + ", Milk"; }
    double cost() const override { return base->cost() + 0.25; }
};

struct Sugar : CoffeeDecorator {
    explicit Sugar(std::unique_ptr<Coffee> b) : CoffeeDecorator(std::move(b)) {}
    std::string description() const override { return base->description() + ", Sugar"; }
    double cost() const override { return base->cost() + 0.10; }
};

struct WhipCream : CoffeeDecorator {
    explicit WhipCream(std::unique_ptr<Coffee> b) : CoffeeDecorator(std::move(b)) {}
    std::string description() const override { return base->description() + ", Whip Cream"; }
    double cost() const override { return base->cost() + 0.50; }
};

int main() {
    std::unique_ptr<Coffee> order = std::make_unique<Espresso>();
    order = std::make_unique<Milk>(std::move(order));
    order = std::make_unique<Sugar>(std::move(order));
    order = std::make_unique<WhipCream>(std::move(order));

    std::cout << order->description() << "\n";
    std::cout << "$" << order->cost() << "\n";
}
