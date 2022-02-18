#include <algorithm>
#include <cstring>
#include <vector>
#include "../includes/array_functions.h"
#include "../includes/constants.h"
#include "../includes/utilities.h"


namespace KP {
	// compare function headers: used to sort vectors of entries
	bool compareWordAscending(const constants::entry &one, constants::entry &two);
	bool compareWordDescending(const constants::entry &one, constants::entry &two);
	bool compareOccurences(const constants::entry &one, constants::entry &two);

	//remove all elements from vector that tracks words and their occurrences
	void clear(std::vector<constants::entry>  &entries) {
		entries.clear();
	}

	//return how many unique words are in the vector
	int getSize(std::vector<constants::entry>  &entries) {
		return entries.size();
	}

	//get word at location i iff i<size(see above function), otherwise return the last word
	//(this is lazy, should throw an exception instead)
	std::string getWordAt(std::vector<constants::entry>  &entries, int i) {
		if (i >= entries.size()) {
			return entries[entries.size()-1].word;
		}
		return entries[i].word;
	}

	//get number_occurences at location i iff i<size(see above function), otherwise return the last number_occurences
	//(this is lazy, should throw an exception instead)
	int getNumbOccurAt(std::vector<constants::entry>  &entries,int i) {
		if (i >= entries.size()) {
			return entries[entries.size()-1].number_occurences;
		}
		return entries[i].number_occurences;
	}

	/*loop through the entire file, one line at a time
	 * call processLine on each line from the file
	 * returns false: myfstream is not open
	 *         true: otherwise*/
	bool processFile(std::vector<constants::entry>  &entries, std::fstream &myfstream) {
		if ( !myfstream.is_open() ) {
			return false;
		}

		std::string line;
		while ( !myfstream.eof() ) {
			getline(myfstream, line);
			KP::processLine(entries, line);
		}
		return true;
	}

	/*take 1 line and extract all the tokens from it
	feed each token to processToken for recording*/
	void processLine(std::vector<constants::entry>  &entries, std::string &myLine) {
		std::stringstream ss(myLine);
		std::string token;
		while(getline(ss, token, ' ')) {
			KP::processToken(entries, token);
		}
	}

	/*NOTE: first call strip_unwanted_chars from utilities to get rid of rubbish chars in the token
	 * if the token is an empty string after this then return since we are not tracking empty strings
	 *
	 * Keep track of how many times each token seen, in other words look thru the entries vector that
	 * holds entry structs to see if there is a struct that has entry.word==token,
	 * if so increment entry.number_occurences, otherwise create a new entry struct for the token,
	 * set entry.number_occurences=1 and add it to the entries vector*/
	void processToken(std::vector<constants::entry>  &entries, std::string &token) {
		// Strip unwanted characters from the token, and if the result is empty, exit this method.
		if (!strip_unwanted_chars(token)) {
			return;
		}

		// convert token to lowercase
		std::transform(token.begin(), token.end(), token.begin(), ::tolower);

		// Loop through the entries. If we find an entry that matches the token,
		// then increment the number of occurrences for that entry.
		std::vector<constants::entry>::iterator itr;
		for (itr = entries.begin(); itr != entries.end(); ++itr) {
			if ((*itr).word == token) {
				++(*itr).number_occurences;
				return;
			}
		}

		// If we make it through the loop without finding a matching entry, create
		// a new entry. First convert token to lowercase, the uppercase, then increment
		// number of occurrences.
		constants::entry newEntry;
		std::transform(token.begin(), token.end(), token.begin(), ::tolower);
		newEntry.word = token;
		toUpper(token);
		newEntry.word_uppercase = token;
		newEntry.number_occurences = 1;
		entries.push_back(newEntry);
	}

	/*
	 * Sort entries based on so enum value.
	 * Please provide a solution that sorts according to the enum
	 * The presence of the enum implies a switch statement based on its value
	 * See the course lectures and demo projects for how to sort a vector of structs
	 */
	void sort(std::vector<constants::entry>  &entries, constants::sortOrder so) {
		switch (so) {
		case constants::NONE:
			break;
		case constants::ASCENDING:
			std::sort( entries.begin(), entries.end(), KP::compareWordAscending );
			break;
		case constants::DESCENDING:
			std::sort( entries.begin(), entries.end(), KP::compareWordDescending );
			break;
		case constants::NUMBER_OCCURRENCES:
			std::sort( entries.begin(), entries.end(), KP::compareOccurences );
			break;
		}
	}

	bool compareWordAscending(const constants::entry &one, constants::entry &two) {
		return one.word < two.word;
	}

	bool compareWordDescending(const constants::entry &one, constants::entry &two) {
		return one.word > two.word;
	}

	bool compareOccurences(const constants::entry &one, constants::entry &two) {
		return one.number_occurences > two.number_occurences;
	}

}
