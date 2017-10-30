

#include "running_median_by_zip_calculator.h"

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

int
main (int argc, char *argv[]) {
    tuple<string,string,uint64_t> t { "11", "11", 11 };
    vector<UnitTest> unittests;
    unittests.push_back( UnitTest {"Simple test", [&]() -> bool {
        RunningMedianByZipCalculator calc;
        vector<tuple<string,string,uint64_t>> data{
                    make_tuple("C00177436", "30004", 384), make_tuple("C00384818", "02895", 250),
                    make_tuple("C00177436", "30750", 230), make_tuple("C00177436", "04105", 384),
                    make_tuple("C00384818", "02895", 333), make_tuple("C00177436", "04105", 384)};
        vector<uint64_t> expectedMedian{     {384, 250, 230, 384, 292, 384}};
        vector<uint64_t> expectedTotalAmount{{384, 250, 230, 384, 583, 768}};
        vector<uint64_t> expectedTotalNumber{{  1,   1,   1,   1,   2,   2}};
        string recip;
        string zip;
        uint64_t amt;
        for (size_t i = 0; i < data.size(); ++i) {
            tie(recip, zip, amt) = data[i];
            calc.put(recip, zip, amt);
            if (calc.getMedian(recip, zip) != expectedMedian[i]) return false;
            if (calc.getTotalAmount(recip, zip) != expectedTotalAmount[i]) return false;
            if (calc.getTotalNumber(recip, zip) != expectedTotalNumber[i]) return false;

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

