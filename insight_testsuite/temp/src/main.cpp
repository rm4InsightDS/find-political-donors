#include <iostream>
#include <utility>
#include <string>
#include <experimental/filesystem>
#include <fstream>
#include <string>

#include "fec_file_parser.h"
#include "running_median_by_date_calculator.h"
#include "running_median_by_zip_calculator.h"

using std::cout;
using std::endl;
using std::tuple;
using std::string;
using std::fstream;
using std::ios;
using std::experimental::filesystem::path;
namespace fs = std::experimental::filesystem;
using ResultsRow = RunningMedianByDateCalculator::ResultsRow;


class FecFileProcessor {
public:
    FecFileProcessor( fstream& itcontStream, fstream& medianvalsByZipStream, fstream& medianvalsByDateStream) :
        parser_(&itcontStream)
      , medianvalsByZipStream_(medianvalsByZipStream)
      , medianvalsByDateStream_(medianvalsByDateStream)

    {

    }
    ~FecFileProcessor() = default;

    void run() {
        ///TODO rewrite this function using std::async or boost::asio

        FecFileRecordsBlock recordsBlock;
        while (!parser_.isEof()) {
            recordsBlock = parser_.getNextRecordsBlock();
            for (auto&& record : recordsBlock) {
                if (!record.ZIP_CODE.empty()) {
                    calcByZip_.put (record.CMTE_ID, record.ZIP_CODE, record.TRANSACTION_AMT);
                    medianvalsByZipStream_ << record.CMTE_ID
                                    << "|" << record.ZIP_CODE
                                    << "|" << calcByZip_.getMedian(record.CMTE_ID, record.ZIP_CODE)
                                    << "|" << calcByZip_.getTotalNumber(record.CMTE_ID, record.ZIP_CODE)
                                    << "|" << calcByZip_.getTotalAmount(record.CMTE_ID, record.ZIP_CODE)
                                    << "\n";
                }
                calcByDate_.put(record.CMTE_ID, record.TRANSACTION_DT, record.TRANSACTION_AMT);

            }
            medianvalsByZipStream_.flush();
        }
        calcByDate_.prepareResults();
        auto&& resultsByDateTable = calcByDate_.getResults();
        for (auto&& row : resultsByDateTable) {
            string recipient;
            recipient = row->key.substr(0, row->key.length() - 8);
            Date date;
            date.YEAR  = std::stoul( row->key.substr(row->key.length() - 8, row->key.length() - 4) );
            date.MONTH = std::stoul( row->key.substr(row->key.length() - 4, row->key.length() - 2) );
            date.DAY   = std::stoul( row->key.substr(row->key.length() - 2) );
            medianvalsByDateStream_ << recipient
                            << "|" << date.MONTH << date.DAY << date.YEAR
                            << "|" << row->medianAmount
                            << "|" << row->totalNumber
                            << "|" << row->totalAmount
                            << "\n";
        }
        medianvalsByDateStream_.flush();

    }

private:
    fstream& medianvalsByZipStream_;
    fstream& medianvalsByDateStream_;
    FecFileParser parser_;
    RunningMedianByDateCalculator calcByDate_;
    RunningMedianByZipCalculator  calcByZip_;
};



void
printUsage(const char* progName) {
    cout << "Usage:\n"
         << progName << " path_to_itcont.txt path_to_medianvals_by_zip.txt path_to_medianvals_by_date.txt" << endl;
}

int
main (int argc, char *argv[]) {

	if (argc != 4 ) {
		printUsage(argv[0]);
		return -1;
	}

    path itcontPath(argv[1]);
    fstream itcontStream(itcontPath);
    if (!itcontStream.is_open()) {
        std::cout << "failed to open " << itcontPath << '\n';
        return 1;
    }

    path medianvalsByZipPath(argv[2]);

    fstream medianvalsByZipStream(medianvalsByZipPath, ios::trunc | ios::out);
    if (!medianvalsByZipStream.is_open()) {
        std::cout << "failed to open " << medianvalsByZipPath << '\n';
        return 1;
    }

    path medianvalsByDatePath(argv[3]);
    fstream medianvalsByDateStream(medianvalsByDatePath, ios::trunc | ios::out);
    if (!medianvalsByDateStream.is_open()) {
        std::cout << "failed to open " << medianvalsByDatePath << '\n';
        return 1;
    }

    FecFileProcessor fecFileProcessor{itcontStream, medianvalsByZipStream, medianvalsByDateStream};
    fecFileProcessor.run();

}
