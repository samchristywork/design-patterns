// Flyweight Pattern
// Uses sharing to efficiently support a large number of fine-grained objects
// by separating intrinsic (shared) state from extrinsic (unique) state.

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Intrinsic (shared) state
struct TreeType {
    std::string name;
    std::string color;
    std::string texture;

    TreeType(std::string n, std::string c, std::string t)
        : name(std::move(n)), color(std::move(c)), texture(std::move(t)) {}

    void draw(int x, int y) const {
        std::cout << "Drawing " << name << " (" << color << ") at (" << x << "," << y << ")\n";
    }
};

// Flyweight factory
struct TreeTypeFactory {
    std::unordered_map<std::string, TreeType> cache;

    const TreeType& getTreeType(const std::string& name, const std::string& color,
                                 const std::string& texture) {
        std::string key = name + "_" + color;
        if (cache.find(key) == cache.end()) {
            std::cout << "Creating new TreeType: " << key << "\n";
            cache.emplace(key, TreeType{name, color, texture});
        }
        return cache.at(key);
    }
};

// Extrinsic (unique) state per tree instance
struct Tree {
    int x, y;
    const TreeType& type;

    Tree(int x, int y, const TreeType& t) : x(x), y(y), type(t) {}
    void draw() const { type.draw(x, y); }
};

int main() {
    TreeTypeFactory factory;
    std::vector<Tree> forest;

    for (int i = 0; i < 3; ++i)
        forest.emplace_back(i * 10, i * 5, factory.getTreeType("Oak", "green", "rough"));
    for (int i = 0; i < 3; ++i)
        forest.emplace_back(i * 7, i * 3, factory.getTreeType("Pine", "dark-green", "smooth"));

    std::cout << "\nDrawing forest (" << forest.size() << " trees, "
              << factory.cache.size() << " unique types):\n";
    for (const auto& tree : forest) tree.draw();
}
