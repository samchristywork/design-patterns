// Interpreter Pattern
// Defines a grammar for a language and provides an interpreter to deal with
// that grammar.

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

using Context = std::unordered_map<std::string, int>;

struct Expression {
    virtual int evaluate(const Context& ctx) const = 0;
    virtual ~Expression() = default;
};

struct Number : Expression {
    int value;
    explicit Number(int v) : value(v) {}
    int evaluate(const Context&) const override { return value; }
};

struct Variable : Expression {
    std::string name;
    explicit Variable(std::string n) : name(std::move(n)) {}
    int evaluate(const Context& ctx) const override {
        auto it = ctx.find(name);
        return it != ctx.end() ? it->second : 0;
    }
};

struct Add : Expression {
    std::unique_ptr<Expression> left, right;
    Add(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}
    int evaluate(const Context& ctx) const override {
        return left->evaluate(ctx) + right->evaluate(ctx);
    }
};

struct Multiply : Expression {
    std::unique_ptr<Expression> left, right;
    Multiply(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}
    int evaluate(const Context& ctx) const override {
        return left->evaluate(ctx) * right->evaluate(ctx);
    }
};

int main() {
    // Build AST for: (x + 5) * (y + 2)
    auto expr = std::make_unique<Multiply>(
        std::make_unique<Add>(
            std::make_unique<Variable>("x"),
            std::make_unique<Number>(5)
        ),
        std::make_unique<Add>(
            std::make_unique<Variable>("y"),
            std::make_unique<Number>(2)
        )
    );

    Context ctx = {{"x", 3}, {"y", 4}};
    // (3 + 5) * (4 + 2) = 8 * 6 = 48
    std::cout << "(x + 5) * (y + 2) = " << expr->evaluate(ctx) << "\n";

    ctx["x"] = 10;
    ctx["y"] = 0;
    // (10 + 5) * (0 + 2) = 15 * 2 = 30
    std::cout << "(x + 5) * (y + 2) = " << expr->evaluate(ctx) << "\n";
}
