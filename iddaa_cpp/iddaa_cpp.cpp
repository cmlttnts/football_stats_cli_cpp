// iddaa_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Team.h"
#include "Match.h"
#include "ParseText.h"
#include "Files.h"

int main(){
	std::string exit_input = "q";
	std::string user_input;
	std::cout << "Press 'q' for exit" << std::endl;
	std::vector<std::filesystem::path> file_names = getFileNames("./weeks");
	while (user_input.compare(exit_input)) {
		std::cout << "Give the name of the team: ";
		std::cin >> user_input;
		Team team(user_input);
		// Read files to modify team's properties
		for (const auto& name : file_names)
			simpleParse(name, team);
		// Preset team's info
		//TODO: nice presentation here
		for (auto& match : team.matches)
			match.prettyPresent();
	}
}

