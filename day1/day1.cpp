#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class File {
    std::ifstream fileStream;
public:
    File(char* fileName) : fileStream(std::ifstream(fileName)) {
        std::cout << "Opening " << fileName << std::endl;
    }

	std::vector<std::string> getLines() {
		std::vector<std::string> list;

		std::string line;
		while (true) {
			std::getline(fileStream, line);

			if (line != "") {
				list.push_back(line);
			}
			else {
				break;
			}
		}

		return list;
	}
};

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

int main(int argc, char** args) {
    std::cout << "Day1" << std::endl;
    
	char* fileName = "../input.txt";
    if (argc > 1) {
		fileName = args[1];
	}

    File file(fileName);
    std::cout << std::to_string(Parser1(file, 0)) << std::endl;
}