
#include "FecFileParser.h"

FecFileParser::FecFileParser(std::istream& inputStream) : inputStream_(inputStream) {

}

FecFileParser::~FecFileParser() {

}


bool FecFileParser::isEof(){
	return isEof_;
}
FecFileFields FecFileParser::getNextRecordsBlock(){

}


