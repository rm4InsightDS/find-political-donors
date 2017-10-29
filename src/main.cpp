#include <iostream>
#include <utility>
#include <string>
#include <experimental/filesystem>

using std::cout;
using std::endl;
using std::tuple;
using std::string;
using std::experimental::filesystem::path;



void
printUsage(const char* progName) {
	cout << "Usage:\n"
		 << progName << "-o PREFIX INPUT.txt" <<endl;
}


int
main (int argc, char *argv[]) {

	if (argc != 4 || argv[1] != "-o") {
		printUsage(argv[0]);
		return -1;
	}

	path inputPath(argv[3]);
	path oututPrefixPath(argv[2]);





}
