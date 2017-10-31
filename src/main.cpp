#include <iostream>
#include <utility>
#include <string>
#include <experimental/filesystem>
#include <fstream>

using std::cout;
using std::endl;
using std::tuple;
using std::string;
using std::fstream;
using std::experimental::filesystem::path;



void
printUsage(const char* progName) {
	cout << "Usage:\n"
		 << progName << " path_to/itcont.txt path_to/medianvals_by_zip.txt path_to/medianvals_by_date.txt" << endl;
}


int
main (int argc, char *argv[]) {

	if (argc != 4 ) {
		printUsage(argv[0]);
		return -1;
	}

    path itcontPath(argv[1]);
    fstream itcontStream(itcontPath | itcontStream.in);
    if (!itcontStream.is_open()) {
        std::cout << "failed to open " << itcontPath << '\n';
        exit(1);
    }

    path medianvalsByZipPath(argv[2]);
    fstream medianvalsByZipStream(medianvalsByZipPath | medianvalsByZipStream.out);
    if (!medianvalsByZipStream.is_open()) {
        std::cout << "failed to open " << medianvalsByZipPath << '\n';
        exit(1);
    }

    path medianvalsByDatePath(argv[1]);
    fstream medianvalsByDateStream(medianvalsByDatePath | medianvalsByDateStream.out);
    if (!medianvalsByDateStream.is_open()) {
        std::cout << "failed to open " << medianvalsByDatePath << '\n';
        exit(1);
    }








}
