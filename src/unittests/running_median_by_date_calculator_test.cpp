#include "running_median_by_date_calculator.h"


#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <tuple>
#include <utility>

#include "fec_file_parser.h"

using std::cout;
using std::endl;
using std::vector;
using std::function;
using std::string;
using std::pair;
using std::tie;
using std::tuple;
using std::make_tuple;



struct UnitTest {
    string name;
    function<bool()> testBody;
};

using ResultsRow = RunningMedianByDateCalculator::ResultsRow;

int
main (int argc, char *argv[]) {
    tuple<string,string,uint64_t> t { "11", "11", 11 };
    vector<UnitTest> unittests;
    unittests.push_back( UnitTest {"Simple test", [&]() -> bool {
        RunningMedianByDateCalculator calc;
        vector<tuple<string,Date,uint64_t>> data{
            make_tuple("C00177436", Date({2017,01,31}), 384),
            make_tuple("C00384818", Date({2017,01,12}), 250),
            make_tuple("C00177436", Date({2017,01,31}), 230),
            make_tuple("C00177436", Date({2017,01,31}), 384),
            make_tuple("C00384818", Date({2017,01,12}), 333),
            make_tuple("C00177436", Date({2017,01,31}), 384)};

        vector<ResultsRow> expectedResults{
            ResultsRow( {"C0017743620170131", 384, 4, 1382} ),
            ResultsRow( {"C0038481820170112", 292, 2, 583} )
        };
        string recip;
        Date date;
        uint64_t amt;
        for (size_t i = 0; i < data.size(); ++i) {
            tie(recip, date, amt) = data[i];
            calc.put(recip, date, amt);
        }
        calc.prepareResults();
        auto&& results = calc.getResults();
        if (results.size() != expectedResults.size()) return false;
        for (size_t i = 0; i < results.size(); ++i) {
            if (results[i]->key          != expectedResults[i].key)          return false;
            if (results[i]->medianAmount != expectedResults[i].medianAmount) return false;
            if (results[i]->totalAmount  != expectedResults[i].totalAmount)  return false;
            if (results[i]->totalNumber  != expectedResults[i].totalNumber)  return false;
        }
        return true;
    }});

    unittests.push_back( UnitTest {"Data contains invalid date", [&]() -> bool {
        RunningMedianByDateCalculator calc;
        vector<tuple<string,Date,uint64_t>> data{
            make_tuple("C00177436", Date({2017,01,31}), 384),
            make_tuple("C00384818", Date({2017,01,12}), 250),
            make_tuple("C00177436", Date({2017,01,31}), 230),
            make_tuple("C00177436", Date({2017,01,31}), 384),
            make_tuple("C00384818", Date({2017,01,12}), 333),
            make_tuple("C00384818", Date({0000,00,00}), 333),
            make_tuple("C00177436", Date({2017,01,31}), 384)};

        vector<ResultsRow> expectedResults{
            ResultsRow( {"C0017743620170131", 384, 4, 1382} ),
            ResultsRow( {"C0038481820170112", 292, 2, 583} )
        };
        string recip;
        Date date;
        uint64_t amt;
        for (size_t i = 0; i < data.size(); ++i) {
            tie(recip, date, amt) = data[i];
            calc.put(recip, date, amt);
        }
        calc.prepareResults();
        auto&& results = calc.getResults();
        if (results.size() != expectedResults.size()) return false;
        for (size_t i = 0; i < results.size(); ++i) {
            if (results[i]->key          != expectedResults[i].key)          return false;
            if (results[i]->medianAmount != expectedResults[i].medianAmount) return false;
            if (results[i]->totalAmount  != expectedResults[i].totalAmount)  return false;
            if (results[i]->totalNumber  != expectedResults[i].totalNumber)  return false;
        }
        return true;
    }});


    cout << "1.." << unittests.size() << endl;
    int retcode = 0;
    for (size_t i = 0; i < unittests.size(); ++i) {
        if (unittests[i].testBody()) {
            cout << "ok " << i+1 << " - " << unittests[i].name << endl;
        } else {
            cout << "not ok " << i+1 << " - " << unittests[i].name << endl;
            retcode = 1;
        }

    }
    exit( retcode );


}


