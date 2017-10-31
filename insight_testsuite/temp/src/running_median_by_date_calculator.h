#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "date.h"

class RunningMedianByDateCalculator {
    using string = std::string;
public:
    struct ResultsRow{
        string   key; //< key formed as '<recipient>    <year><month><day>'
        uint64_t medianAmount;
        uint64_t totalNumber;
        uint64_t totalAmount;
    };
    RunningMedianByDateCalculator()  = default;
    ~RunningMedianByDateCalculator() = default;
    void put(const string& recipient, const Date& date, uint64_t amount);
    void prepareResults();
    using ResultsTable = std::vector<std::unique_ptr<ResultsRow>>;
    const ResultsTable& getResults() const;

private:
    static uint64_t calculateMedian(const std::vector<uint64_t>& transactions);
    void radixSort(size_t k);
    void sortResultsByRecipient();
    void sortResultsByDate();
    void sortResultsByYear();
    void sortResultsByMonth();
    void sortResultsByDay();
    void extractData();
private:
    std::unordered_map<string,std::vector<uint64_t>> transactionsByRecipientAndDate_;

    ResultsTable results;


};

