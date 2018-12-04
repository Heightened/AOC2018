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

	ChecksumParser(File& file) {
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

class PackageFinder {
	std::string value;

public:
	std::string commonCharacters(std::string linea, std::string lineb) {
		std::string common = "";
		for (auto ita = linea.begin(), itb = lineb.begin(); ita != linea.end() && itb != lineb.end(); ) {
			if (*ita == *itb) {
				common += *ita;
			}
			ita++;
			itb++;
		}
		return common;
	}

	// Check if there is a character in the line which occurs exactly twice
	bool almostequal(std::string linea, std::string lineb) {
		int differences = 0;
		for (auto ita = linea.begin(), itb = lineb.begin(); ita != linea.end() && itb != lineb.end(); ) {
			if (*ita++ != *itb++) {
				differences++;
			}

			if (differences > 1) {
				return false;
			}
		}
		if (differences == 0) {
			return false;
		} 
		return true;
	}

	PackageFinder(File& file) {
		std::vector<std::string> lines = file.getLines();

		for (std::string linea : lines) {
			for (std::string lineb : lines) {
				if (almostequal(linea, lineb)) {
					value = commonCharacters(linea, lineb);
					return;
				}
			}
		}
	}

	operator std::string() const { return value; }
};


int main(int argc, char** args) {
    std::cout << "Day1" << std::endl;
    
	char* fileName = "../input.txt";
    if (argc > 1) {
		fileName = args[1];
	}

    File file(fileName);
    std::cout << "Part 1" << std::endl << std::to_string(ChecksumParser(file)) << std::endl;
	std::string package = PackageFinder(file);
	std::cout << "Part 2" << std::endl << package << std::endl;
}