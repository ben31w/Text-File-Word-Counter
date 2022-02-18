#include <fstream>
#include "../includes/constants.h"
#include "../includes/fileio.h"
#include "../includes/utilities.h"

/* returns True - file opened successfully
          False - file not opened*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {

	myfile.open(myFileName);
	if (myfile.is_open()) {
		return true;
	}
	return false;

}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}

/* serializes all content in entries to file outputfilename
 * check out utils for helpful type conversion functions
 * BTW serialize means the process of translating a data structure
 * into a format that can be stored in a file
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in the vector entries
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writetoFile(std::vector<constants::entry>  &entries, const std::string &outputfilename) {
	// If we cannot open file, return failure.
	if ( !does_file_exist(outputfilename) ) {
			return constants::FAIL_FILE_DID_NOT_OPEN;
		}
	// If there are no entries in the array, return failure.
	if (entries.size() == 0) {
		return constants::FAIL_NO_ARRAY_DATA;
	}

	// Write to file if it opens successfully.
	std::ofstream fout;
	fout.open(outputfilename.c_str());
	for (constants::entry e: entries) {
//		std::string toWrite = e.word + " " + std::to_string(e.number_occurences) + "\n";
//		long int size = toWrite.size();
//		fout.write(toWrite.c_str(), size );
	}
	fout.close();
	return constants::SUCCESS;



}

