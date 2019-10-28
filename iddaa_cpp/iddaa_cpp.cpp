// iddaa_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include "Team.h"
#include "Match.h"
#include "ParseText.h"
#include "Files.h"
#include "Presentation.h"


int main(){
	std::string exit_input = "q";
	std::string user_input;
	std::cout << "Press 'q' for exit" << std::endl;
	std::vector<std::filesystem::path> file_names = getFileNames("./weeks");
	while (1) {
		std::cout << "\n\nGive the name of the team: ";
		std::cin >> user_input;
		if (!user_input.compare(exit_input))
			break;
		{
			Team team(user_input);
			bool failure = true;
			// Read files to modify team's properties
			for (const auto& name : file_names) {
				//if we find at least 1 match we say it is success
				failure = simpleParse(name, team) && failure;
				//std::cout << name << "\n";
			}
			// Preset team's info
			if (failure)
				std::cout << "No match found" << "\n";
			else {
				//std::cout << team.matches.size() << "size \n";
				int n = 1;
				for (auto& match : team.matches) {
					std::cout << n << "-) ";
					match.prettyPresent();
					//give some time to read
					Sleep(1500);
					n++;
				}
				presentTeamInfo(team);
			}
		}
	}
}

