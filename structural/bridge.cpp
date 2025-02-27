// Bridge Pattern
// Decouples an abstraction from its implementation so that the two can vary
// independently.

#include <iostream>
#include <memory>
#include <string>

// Implementation hierarchy
struct Renderer {
    virtual void renderCircle(float x, float y, float r) = 0;
    virtual ~Renderer() = default;
};

struct VectorRenderer : Renderer {
    void renderCircle(float x, float y, float r) override {
        std::cout << "Drawing circle as vector at (" << x << "," << y << ") r=" << r << "\n";
    }
};

struct RasterRenderer : Renderer {
    void renderCircle(float x, float y, float r) override {
        std::cout << "Drawing circle as pixels at (" << x << "," << y << ") r=" << r << "\n";
    }
};

// Abstraction hierarchy
struct Shape {
    Renderer& renderer;
    explicit Shape(Renderer& r) : renderer(r) {}
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
    virtual ~Shape() = default;
};

struct Circle : Shape {
    float x, y, radius;

    Circle(Renderer& r, float x, float y, float radius)
        : Shape(r), x(x), y(y), radius(radius) {}

    void draw() override { renderer.renderCircle(x, y, radius); }
    void resize(float factor) override { radius *= factor; }
};

int main() {
    VectorRenderer vector;
    RasterRenderer raster;

    Circle c1(vector, 1, 2, 3);
    Circle c2(raster, 4, 5, 6);

    c1.draw();
    c2.draw();

    c1.resize(2);
    c1.draw();
}
