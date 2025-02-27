// Composite Pattern
// Composes objects into tree structures to represent part-whole hierarchies,
// letting clients treat individual objects and compositions uniformly.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct FileSystemItem {
    std::string name;
    explicit FileSystemItem(const std::string& n) : name(n) {}
    virtual void print(int depth) const = 0;
    virtual int size() const = 0;
    virtual ~FileSystemItem() = default;
};

struct File : FileSystemItem {
    int bytes;
    File(const std::string& n, int b) : FileSystemItem(n), bytes(b) {}

    void print(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << name << " (" << bytes << "B)\n";
    }

    int size() const override { return bytes; }
};

struct Directory : FileSystemItem {
    std::vector<std::unique_ptr<FileSystemItem>> children;

    explicit Directory(const std::string& n) : FileSystemItem(n) {}

    void add(std::unique_ptr<FileSystemItem> item) {
        children.push_back(std::move(item));
    }

    void print(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << name << "/\n";
        for (const auto& c : children) c->print(depth + 1);
    }

    int size() const override {
        int total = 0;
        for (const auto& c : children) total += c->size();
        return total;
    }
};

int main() {
    auto root = std::make_unique<Directory>("root");

    auto src = std::make_unique<Directory>("src");
    src->add(std::make_unique<File>("main.cpp", 1200));
    src->add(std::make_unique<File>("util.cpp", 800));

    auto include = std::make_unique<Directory>("include");
    include->add(std::make_unique<File>("util.h", 300));

    root->add(std::move(src));
    root->add(std::move(include));
    root->add(std::make_unique<File>("README.md", 500));

    root->print(0);
    std::cout << "Total size: " << root->size() << "B\n";
}
