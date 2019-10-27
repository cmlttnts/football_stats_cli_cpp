// iddaa_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Team.h"
#include "Match.h"
#include "ParseText.h"
#include "Files.h"

int main(){
	std::vector<std::filesystem::path> file_names = getFileNames("./weeks");
	for (const auto& name : file_names)
		simpleParse(name);
}

