// Visitor Pattern
// Lets you add further operations to objects without modifying them, by
// separating the algorithm from the object structure.

#include <iostream>
#include <memory>
#include <vector>

struct Circle;
struct Rectangle;
struct Triangle;

struct Visitor {
    virtual void visit(const Circle& c) = 0;
    virtual void visit(const Rectangle& r) = 0;
    virtual void visit(const Triangle& t) = 0;
    virtual ~Visitor() = default;
};

struct Shape {
    virtual void accept(Visitor& v) const = 0;
    virtual ~Shape() = default;
};

struct Circle : Shape {
    double radius;
    explicit Circle(double r) : radius(r) {}
    void accept(Visitor& v) const override { v.visit(*this); }
};

struct Rectangle : Shape {
    double width, height;
    Rectangle(double w, double h) : width(w), height(h) {}
    void accept(Visitor& v) const override { v.visit(*this); }
};

struct Triangle : Shape {
    double base, height;
    Triangle(double b, double h) : base(b), height(h) {}
    void accept(Visitor& v) const override { v.visit(*this); }
};

struct AreaCalculator : Visitor {
    double total = 0;

    void visit(const Circle& c) override {
        double area = 3.14159 * c.radius * c.radius;
        std::cout << "Circle area: " << area << "\n";
        total += area;
    }
    void visit(const Rectangle& r) override {
        double area = r.width * r.height;
        std::cout << "Rectangle area: " << area << "\n";
        total += area;
    }
    void visit(const Triangle& t) override {
        double area = 0.5 * t.base * t.height;
        std::cout << "Triangle area: " << area << "\n";
        total += area;
    }
};

struct XMLExporter : Visitor {
    void visit(const Circle& c) override {
        std::cout << "<circle radius=\"" << c.radius << "\"/>\n";
    }
    void visit(const Rectangle& r) override {
        std::cout << "<rectangle width=\"" << r.width << "\" height=\"" << r.height << "\"/>\n";
    }
    void visit(const Triangle& t) override {
        std::cout << "<triangle base=\"" << t.base << "\" height=\"" << t.height << "\"/>\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(4, 6));
    shapes.push_back(std::make_unique<Triangle>(3, 8));

    AreaCalculator calc;
    for (const auto& s : shapes) s->accept(calc);
    std::cout << "Total area: " << calc.total << "\n\n";

    XMLExporter xml;
    for (const auto& s : shapes) s->accept(xml);
}
