#pragma once

#include <istream>
#include <string>
#include <chrono>
#include <cstddef>
#include <vector>
#include <array>


struct FecFileRecord {
	 std::string CMTE_ID;
	 std::string ZIP_CODE;
	 struct Date{
		 unsigned int YEAR;
		 unsigned int MONTH;
		 unsigned int DAY;
	 };
	 Date TRANSACTION_DT;
	 uint64_t TRANSACTION_AMT;
};


typedef std::vector<FecFileRecord> FecFileRecordsBlock;

class FecFileParser {

public:
	FecFileParser(std::istream* inputStream, size_t recordsBlockSize = 10);
	~FecFileParser();
	bool isEof() const;
	FecFileRecordsBlock getNextRecordsBlock();

private:
	std::istream& inputStream_;
	bool isEof_ = false;
	size_t recordsBlockSize_;
	std::array<char, 4096> readBuf_;
};

