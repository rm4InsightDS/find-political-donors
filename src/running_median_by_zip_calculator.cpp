
#include "running_median_by_zip_calculator.h"

#include <algorithm>
#include <cmath>

using std::string;

RunningMedianByZipCalculator::RunningMedianByZipCalculator() {

}

void RunningMedianByZipCalculator::put(const string& recipient, const string& zip, uint64_t amount){
    const string key = recipient + zip;
    auto& record = transactionsByZipAndRecipient_[key];
    auto iter = std::lower_bound( begin(record.transactions), end(record.transactions), amount );
    record.transactions.insert(iter, amount);
    record.totalAmount += amount;
}
uint64_t RunningMedianByZipCalculator::getMedian(const string& recipient, const string& zip) const {
    uint64_t median;
    const string key = recipient + zip;
    auto iter = transactionsByZipAndRecipient_.find(key);
    if (iter == transactionsByZipAndRecipient_.end()) return 0;
    const auto& transactions = iter->second.transactions;
    auto mid = transactions.size() / 2;
    if (transactions.size() % 2 == 0) {
        median = std::llround( (transactions[mid] + transactions[mid-1]) / 2.0L );
    } else {
        median = transactions[mid];
    }
    return median;
}

uint64_t RunningMedianByZipCalculator::getTotalAmount(const std::string& recipient, const std::string& zip) const {
    const string key = recipient + zip;
    auto iter = transactionsByZipAndRecipient_.find(key);
    if (iter == transactionsByZipAndRecipient_.end()) return 0;
    return iter->second.totalAmount;
}
uint64_t RunningMedianByZipCalculator::getTotalNumber(const std::string& recipient, const std::string& zip) const {
    const string key = recipient + zip;
    auto iter = transactionsByZipAndRecipient_.find(key);
    if (iter == transactionsByZipAndRecipient_.end()) return 0;
    return iter->second.transactions.size();
}
