#pragma once

#include <istream>
#include <string>
#include <chrono>
#include <experimental/optional>
#include <cstddef>

struct FecFileFields {
	 std::string CmteId;
	 int ZipCode;
	 unsigned int TRANSACTION_DT;
	 uint64_t TRANSACTION_AMT;
};




class FecFileParser {

public:
	FecFileParser(std::istream& inputStream, size_t recordsBlockSize = 10);
	~FecFileParser();
	bool isEof();
	FecFileFields getNextRecordsBlock();

private:
	std::istream inputStream_;
	bool isEof_ = false;
};

