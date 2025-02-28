// Proxy Pattern
// Provides a surrogate or placeholder for another object to control access to it.

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

struct Image {
    virtual void display() = 0;
    virtual ~Image() = default;
};

struct RealImage : Image {
    std::string filename;

    explicit RealImage(const std::string& f) : filename(f) {
        std::cout << "Loading image from disk: " << filename << "\n";
    }

    void display() override {
        std::cout << "Displaying: " << filename << "\n";
    }
};

// Proxy: lazy-loads the real image and caches it
struct ImageProxy : Image {
    std::string filename;
    std::unique_ptr<RealImage> real;

    explicit ImageProxy(const std::string& f) : filename(f) {}

    void display() override {
        if (!real) {
            real = std::make_unique<RealImage>(filename);
        }
        real->display();
    }
};

int main() {
    ImageProxy img1("photo1.jpg");
    ImageProxy img2("photo2.jpg");

    std::cout << "-- First display of img1 --\n";
    img1.display(); // loads from disk

    std::cout << "-- Second display of img1 --\n";
    img1.display(); // uses cached copy

    std::cout << "-- img2 never displayed --\n";
    // img2 is never loaded from disk
}
