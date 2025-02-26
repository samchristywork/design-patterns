// Prototype Pattern
// Creates new objects by copying an existing object (the prototype), avoiding
// the cost of creation from scratch.

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

struct Shape {
    std::string color;

    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

struct Circle : Shape {
    int radius;

    Circle(int r, const std::string& c) : radius(r) { color = c; }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }

    void draw() const override {
        std::cout << "Circle(r=" << radius << ", color=" << color << ")\n";
    }
};

struct Rectangle : Shape {
    int width, height;

    Rectangle(int w, int h, const std::string& c) : width(w), height(h) { color = c; }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }

    void draw() const override {
        std::cout << "Rectangle(" << width << "x" << height << ", color=" << color << ")\n";
    }
};

int main() {
    Circle proto_circle(10, "red");
    Rectangle proto_rect(20, 5, "blue");

    auto c1 = proto_circle.clone();
    auto c2 = proto_circle.clone();
    auto r1 = proto_rect.clone();

    // Modify clone independently of prototype
    static_cast<Circle*>(c2.get())->color = "green";

    c1->draw();
    c2->draw();
    r1->draw();
    proto_circle.draw(); // unchanged
}
