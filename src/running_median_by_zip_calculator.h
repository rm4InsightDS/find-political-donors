#pragma once

#include <unordered_map>
#include <list>
#include <vector>



class RunningMedianByZipCalculator {
public:
    RunningMedianByZipCalculator() = default;
    ~RunningMedianByZipCalculator() = default;

    void put(const std::string& recipient, const std::string& zip, uint64_t amount);
    uint64_t getMedian(const std::string& recipient, const std::string& zip) const;
    uint64_t getTotalAmount(const std::string& recipient, const std::string& zip) const;
    uint64_t getTotalNumber(const std::string& recipient, const std::string& zip) const;


private:
    struct Transactions {
        std::vector<uint64_t> transactions;
        uint64_t totalAmount;

    };
    std::unordered_map<std::string,Transactions> transactionsByZipAndRecipient_;

};

