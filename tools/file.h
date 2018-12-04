#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class File {
	std::ifstream fileStream;
	std::vector<std::string> lines;
public:
	File(char* fileName);
	std::vector<std::string> getLines();
};