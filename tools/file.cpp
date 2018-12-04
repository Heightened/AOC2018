#include "file.h"

#include <vector>

File::File(char* fileName) : fileStream(std::ifstream(fileName)) {
	std::cout << "Opening " << fileName << std::endl;

	std::string line;
	while (true) {
		std::getline(fileStream, line);

		if (line != "") {
			lines.push_back(line);
		}
		else {
			break;
		}
	}
}

std::vector<std::string> File::getLines() {
	return lines;
}