// Strategy Pattern
// Defines a family of algorithms, encapsulates each one, and makes them
// interchangeable. Lets the algorithm vary independently from clients that use it.

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>

struct SortStrategy {
    virtual void sort(std::vector<int>& data) = 0;
    virtual std::string name() const = 0;
    virtual ~SortStrategy() = default;
};

struct BubbleSort : SortStrategy {
    void sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; ++i)
            for (int j = 0; j < n - i - 1; ++j)
                if (data[j] > data[j + 1]) std::swap(data[j], data[j + 1]);
    }
    std::string name() const override { return "BubbleSort"; }
};

struct StdSort : SortStrategy {
    void sort(std::vector<int>& data) override { std::sort(data.begin(), data.end()); }
    std::string name() const override { return "StdSort"; }
};

struct Sorter {
    SortStrategy* strategy;
    explicit Sorter(SortStrategy* s) : strategy(s) {}

    void setStrategy(SortStrategy* s) { strategy = s; }

    void sort(std::vector<int>& data) {
        std::cout << "Using " << strategy->name() << ": ";
        strategy->sort(data);
        for (int x : data) std::cout << x << " ";
        std::cout << "\n";
    }
};

int main() {
    BubbleSort bubble;
    StdSort stdSort;

    std::vector<int> data1 = {5, 2, 8, 1, 9, 3};
    std::vector<int> data2 = {5, 2, 8, 1, 9, 3};

    Sorter sorter(&bubble);
    sorter.sort(data1);

    sorter.setStrategy(&stdSort);
    sorter.sort(data2);
}
