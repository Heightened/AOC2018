#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "../tools/file.h"

class ChecksumParser {
	std::map<int, int> matches;

    int value;

public:
	// Check if there is a character in the line which occurs exactly twice
	bool checknletters(int n, std::string line) {
		for (char character : line) {
			if (std::count(line.begin(), line.end(), character) == n) {
				return true;
			}
		}
		return false;
	}

	ChecksumParser(File& file, int startingValue) : value(startingValue) {
		matches[2] = 0;
		matches[3] = 0;

		std::vector<std::string> lines = file.getLines();

		for (std::string line : lines) {
			for (auto it : matches) {
				if (checknletters(it.first, line)) {
					matches[it.first]++;
				}
			}
		}

		value = matches[2] * matches[3];
    }
    
    operator int() const { return value; }
};

int main(int argc, char** args) {
    std::cout << "Day1" << std::endl;
    
	char* fileName = "../input.txt";
    if (argc > 1) {
		fileName = args[1];
	}

    File file(fileName);
    std::cout << "Part 1" << std::endl << std::to_string(ChecksumParser(file, 0)) << std::endl;
}