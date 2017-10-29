
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
auto const validRecordRegexStr = R"((^[^\|]*)\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|([\d]{5})[^\|]*\|[^\|]*\|[^\|]*\|(.*)\|([\d]*)\|\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*\|[^\|]*$)";
const regex validRecordRegex( validRecordRegexStr, std::regex_constants::ECMAScript);
const regex validDateRegex( R"(([\d]{2})([\d]{2})([\d]{4}))", std::regex_constants::ECMAScript);

array<int,13> daysInMoth = {0/*dummy*/,31,28,31,30,31,30,31,31,30,31,30,31};

bool isLeepYear(unsigned year) {
    if (year % 4 != 0) return false;
    else if (year % 100 != 0) return true;
    else if (year % 400 != 0) return false;
    return true;
}

bool checkDate(FecFileRecord::Date date) {
    if (date.MONTH < 1 || date.MONTH > 12 || date.DAY < 1) return false;
    int maxDay = daysInMoth[ date.MONTH ];
    if (date.MONTH == 2 && isLeepYear(date.YEAR)) {
        maxDay = 29;
    }
    return date.DAY <= maxDay;
}
} // anonymous namespace


FecFileRecord::Date parseDate(const string& dateStr) {
    std::smatch dateMatch;
    if (!std::regex_search( dateStr, dateMatch, validDateRegex ) ) {
        return FecFileRecord::Date({0,0,0});
    }
    FecFileRecord::Date date;
    date.MONTH = std::stoi( std::string( dateMatch[1].first, dateMatch[1].second ) );
    date.DAY   = std::stoi( std::string( dateMatch[2].first, dateMatch[2].second ) );
    date.YEAR  = std::stoi( std::string( dateMatch[3].first, dateMatch[3].second ) );
    if (!checkDate(date)) return FecFileRecord::Date({0,0,0});
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
			record.CMTE_ID         = string( recordMatch[1].first, recordMatch[1].second );
			if (record.CMTE_ID.empty()) continue;
			record.ZIP_CODE        = string( recordMatch[2].first, recordMatch[2].second );
			record.TRANSACTION_DT  = parseDate( string( recordMatch[3].first, recordMatch[3].second ) );
			string transactionAmtStr { recordMatch[4].first, recordMatch[4].second };
			if (transactionAmtStr.empty()) continue;
            record.TRANSACTION_AMT = std::stoull( transactionAmtStr );
			recordsBlock.push_back( record );
		}
	}
	return recordsBlock;
}


