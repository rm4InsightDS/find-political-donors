
#include "fec_file_parser.h"

#include <stdexcept>
#include <regex>
#include <string>
#include <algorithm>
#include <array>



using std::string;
using std::array;
using std::regex;
using std::smatch;
using std::cmatch;

namespace {
auto const validRecordRegexStr = R"((^[^\|]*)\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|([^\|]*)\|[^\|]*\|[^\|]*\|([^\|]*)\|([\d]*)\|\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*$)";
const regex validRecordRegex( validRecordRegexStr, std::regex_constants::ECMAScript);
const regex validDateRegex( R"(([\d]{2})([\d]{2})([\d]{4}))", std::regex_constants::ECMAScript);

array<int,13> daysInMoth = {0/*dummy*/,31,28,31,30,31,30,31,31,30,31,30,31};

const unsigned short ZIP_LENGTH = 5;
bool checkZip(const string& zip) {
    if (zip.size() < ZIP_LENGTH) return false;
    for (unsigned short i = 0; i < ZIP_LENGTH; ++i) {
        if (!isdigit( zip[i] )) return false;
    }
    return true;
}

} // anonymous namespace


Date parseDate(const string& dateStr) {
    std::smatch dateMatch;
    if (!std::regex_search( dateStr, dateMatch, validDateRegex ) ) {
        return Date({0,0,0});
    }
    Date date;
    date.MONTH = std::stoi( std::string( dateMatch[1].first, dateMatch[1].second ) );
    date.DAY   = std::stoi( std::string( dateMatch[2].first, dateMatch[2].second ) );
    date.YEAR  = std::stoi( std::string( dateMatch[3].first, dateMatch[3].second ) );
    if (!checkDate(date)) return Date({0,0,0});
    return date;
}

FecFileParser::FecFileParser(std::istream* inputStream, size_t recordsBlockSize) :
  inputStream_(*inputStream)
, recordsBlockSize_(recordsBlockSize)
, readBuf_()
{
}

FecFileParser::~FecFileParser() {

}


bool FecFileParser::isEof() const{
	return inputStream_.eof();
}


FecFileRecordsBlock FecFileParser::getNextRecordsBlock(){
	auto recordsNumoberNeeded = recordsBlockSize_;
	FecFileRecordsBlock recordsBlock;
	FecFileRecord record;
	std::cmatch recordMatch;
	while( inputStream_.getline(readBuf_.begin(), readBuf_.size() ) ) {
		readBuf_.back() = '\0';
		if( std::regex_search( &(readBuf_.front()), recordMatch, validRecordRegex ) ) {
			record.CMTE_ID = string( recordMatch[1].first, recordMatch[1].second );
			if (record.CMTE_ID.empty()) continue;
			string zip = string( recordMatch[2].first, recordMatch[2].second );
			if (checkZip(zip)) {
			    record.ZIP_CODE = zip.substr(0,5);
			}
			record.TRANSACTION_DT  = parseDate( string( recordMatch[3].first, recordMatch[3].second ) );
			string transactionAmtStr { recordMatch[4].first, recordMatch[4].second };
			if (transactionAmtStr.empty()) continue;
            record.TRANSACTION_AMT = std::stoull( transactionAmtStr );
			recordsBlock.push_back( record );
		}
	}
	return recordsBlock;
}


