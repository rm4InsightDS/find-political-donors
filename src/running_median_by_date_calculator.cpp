#include "running_median_by_date_calculator.h"

#include <sstream>
#include <algorithm>
#include <cmath>
#include <regex>
#include <iomanip>
#include <tuple>
#include <array>

using sstream = std::stringstream;
using std::setfill;
using std::setw;
using std::make_tuple;
using std::array;


namespace {
Date invalidDate{0,0,0};

} // anunimous namespace

void RunningMedianByDateCalculator::put(const std::string& recipient, const Date& date, uint64_t amount) {
    if (date == invalidDate) return;
    sstream key;
    key << recipient << date.YEAR << setfill('0')<< setw(2) << date.MONTH  << setfill('0') << setw(2) << date.DAY;
    auto& transactions = transactionsByRecipientAndDate_[key.str()];
    auto iter = std::lower_bound( begin(transactions), end(transactions), amount );
    transactions.insert(iter, amount);
}

uint64_t RunningMedianByDateCalculator::calculateMedian(const std::vector<uint64_t>& transactions) {
    uint64_t median;
    auto mid = transactions.size() / 2;
    if (transactions.size() % 2 == 0) {
        median = std::llround( (transactions[mid] + transactions[mid-1]) / 2.0L );
    } else {
        median = transactions[mid];
    }
    return median;
}

const RunningMedianByDateCalculator::ResultsTable&
RunningMedianByDateCalculator::getResults() const {
    return results;
}

void RunningMedianByDateCalculator::prepareResults() {
    extractData();
    size_t maxKeyLength = 0;
    for (auto&& row : results) {
        maxKeyLength = std::max(maxKeyLength, row->key.length());
    }
    for (size_t i = maxKeyLength; i > 0; --i) {
        radixSort(i-1);
    }
}

void RunningMedianByDateCalculator::extractData() {

    results.reserve(transactionsByRecipientAndDate_.size());
    for(auto it = transactionsByRecipientAndDate_.begin(); it != transactionsByRecipientAndDate_.end(); ) {
        auto& transactions = it->second;
        auto row = std::make_unique<ResultsRow>();
        row->key = it->first;
        row->totalAmount = std::accumulate( begin(transactions), end(transactions), 0);
        row->totalNumber = transactions.size();
        row->medianAmount = calculateMedian(transactions);
        results.push_back(std::move(row));
        it = transactionsByRecipientAndDate_.erase(it);
    }
}

void RunningMedianByDateCalculator::radixSort(size_t k){
    if (results.empty()) return;
    array<size_t, 257> counts = {};

    for (size_t i = 0; i < results.size(); ++i) {
        char c = (k < results[i]->key.length()) ? results[i]->key[k] : 0;
        ++counts[c];
    }

    size_t sum = 0;
    size_t tmp;
    for (size_t i = 0; i < counts.size(); ++i) {
        tmp = counts[i];
        counts[i] = sum;
        sum += tmp;
    }

    ResultsTable aux(results.size());
    for (size_t i = 0; i < results.size(); ++i) {
        char c = (k < results[i]->key.length()) ? results[i]->key[k] : 0;
        size_t pos = counts[c]++;
        swap(aux[pos], results[i]);
    }
    results.swap(aux);
}


