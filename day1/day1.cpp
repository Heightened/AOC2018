#include <iostream>
#include <vector>
#include <string>

#include "../tools/file.h"

class Parser1 {
    int value;

public:
	int getValue(std::string line) {
		return std::stoi(line);
	}

    Parser1(File& file, int startingValue) : value(startingValue) {
		std::vector<std::string> lines = file.getLines();

		for (std::string line : lines) {
			value += getValue(line);
		}
    }
    
    operator int() const { return value; }
};

class Parser2 {
	int value;

public:
	int getValue(std::string line) {
		return std::stoi(line);
	}

	Parser2(File& file, int startingValue) : value(startingValue) {
		std::vector<std::string> lines = file.getLines();

		std::vector<int> intermediates;
		intermediates.push_back(0);

		int i = 0;
		while (true) {
			std::string line = lines[i++ % lines.size()];

			int newValue = intermediates.back() + getValue(line);

			if (std::find(intermediates.begin(), intermediates.end(), newValue) != intermediates.end()) {
				value = newValue;
				break;
			}

			intermediates.push_back(newValue);
		}
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
    std::cout << "Part 1" << std::endl << std::to_string(Parser1(file, 0)) << std::endl;
	std::cout << "Part 2" << std::endl << std::to_string(Parser2(file, 0)) << std::endl;
}