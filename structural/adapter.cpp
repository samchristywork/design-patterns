// Adapter Pattern
// Converts the interface of a class into another interface that clients expect,
// enabling incompatible interfaces to work together.

#include <iostream>
#include <string>
#include <cmath>

// Target interface expected by client
struct RoundHole {
    double radius;
    bool fits(double r) const { return r <= radius; }
};

// Incompatible existing class
struct SquarePeg {
    double width;
    explicit SquarePeg(double w) : width(w) {}
};

// Adapter: makes SquarePeg compatible with RoundHole
struct SquarePegAdapter {
    const SquarePeg& peg;
    explicit SquarePegAdapter(const SquarePeg& p) : peg(p) {}

    double getRadius() const {
        // Circumscribed circle radius of the square peg
        return peg.width * std::sqrt(2.0) / 2.0;
    }
};

int main() {
    RoundHole hole{5.0};

    SquarePeg smallPeg{5.0};
    SquarePeg largePeg{10.0};

    SquarePegAdapter smallAdapter(smallPeg);
    SquarePegAdapter largeAdapter(largePeg);

    std::cout << "Small peg fits: " << (hole.fits(smallAdapter.getRadius()) ? "yes" : "no") << "\n";
    std::cout << "Large peg fits: " << (hole.fits(largeAdapter.getRadius()) ? "yes" : "no") << "\n";
}
