// Builder Pattern
// Separates the construction of a complex object from its representation,
// allowing the same construction process to create different representations.

#include <iostream>
#include <string>
#include <vector>

struct Pizza {
    std::string size;
    std::string crust;
    std::vector<std::string> toppings;

    void print() const {
        std::cout << size << " pizza, " << crust << " crust, toppings:";
        for (const auto& t : toppings) std::cout << " " << t;
        std::cout << "\n";
    }
};

class PizzaBuilder {
public:
    PizzaBuilder& setSize(const std::string& s) { pizza.size = s; return *this; }
    PizzaBuilder& setCrust(const std::string& c) { pizza.crust = c; return *this; }
    PizzaBuilder& addTopping(const std::string& t) { pizza.toppings.push_back(t); return *this; }
    Pizza build() { return pizza; }

private:
    Pizza pizza;
};

int main() {
    Pizza margherita = PizzaBuilder()
        .setSize("medium")
        .setCrust("thin")
        .addTopping("tomato sauce")
        .addTopping("mozzarella")
        .addTopping("basil")
        .build();

    Pizza meatLovers = PizzaBuilder()
        .setSize("large")
        .setCrust("thick")
        .addTopping("pepperoni")
        .addTopping("sausage")
        .addTopping("bacon")
        .build();

    margherita.print();
    meatLovers.print();
}
