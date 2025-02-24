// Template Method Pattern
// Defines the skeleton of an algorithm in a base class, deferring some steps
// to subclasses without changing the algorithm's overall structure.

#include <iostream>
#include <string>

struct DataMiner {
    // Template method: defines the algorithm skeleton
    void mine(const std::string& path) {
        openFile(path);
        auto raw = extractData();
        auto parsed = parseData(raw);
        analyzeData(parsed);
        closeFile();
    }

    virtual ~DataMiner() = default;

protected:
    virtual void openFile(const std::string& path) {
        std::cout << "Opening file: " << path << "\n";
    }
    virtual std::string extractData() = 0;
    virtual std::string parseData(const std::string& raw) {
        return "parsed(" + raw + ")";
    }
    virtual void analyzeData(const std::string& data) {
        std::cout << "Analyzing: " << data << "\n";
    }
    virtual void closeFile() {
        std::cout << "Closing file.\n";
    }
};

struct CSVDataMiner : DataMiner {
protected:
    std::string extractData() override {
        return "csv_raw_data";
    }
    std::string parseData(const std::string& raw) override {
        return "csv_parsed[" + raw + "]";
    }
};

struct JSONDataMiner : DataMiner {
protected:
    std::string extractData() override {
        return "json_raw_data";
    }
};

int main() {
    std::cout << "-- CSV Miner --\n";
    CSVDataMiner csv;
    csv.mine("data.csv");

    std::cout << "\n-- JSON Miner --\n";
    JSONDataMiner json;
    json.mine("data.json");
}
