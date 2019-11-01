// iddaa_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include "Team.h"
#include "Match.h"
#include "ParseTeam.h"
#include "Files.h"
#include "PresentTeam.h"
#include <algorithm>
#include <sstream>
#include "Interface.h"




int main(){
	std::string exit_input = "q";
	std::string user_input;
	std::cout << "Press 'q' for exit" << std::endl;
	std::string weeks_path;
	//temporary variables block
	{
		std::string cur_path = std::filesystem::current_path().string();
		std::string iddaa_cpp_part = "\\iddaa_cpp";
		weeks_path = cur_path.substr(0, cur_path.find(iddaa_cpp_part));
	}
	weeks_path += "\\iddaa_cpp\\weeks";
	std::vector<std::filesystem::path> file_names = getFileNames(weeks_path);
	//getInitOptions();
	greeting();

	bool exited = false;
	bool go_back1 = false;
	bool go_back2 = false;
	while (!exited) {
		INIT_OPTIONS first_option = getInitOptions();
		go_back1 = false;
		while (!exited && !go_back1) {
			if (first_option == INIT_OPTIONS::TEAM_OPTION) {
				TEAM_OPTIONS second_option = getTeamOption();
				go_back2 = false;
				while (!exited && !go_back2) {
					if (second_option == TEAM_OPTIONS::TEAM_ANALYSIS) {
						go_back2 = false;
						while (!exited && !go_back2) {
							std::string team_name = getTeamNameFromUser();
							int result = presentTeam(team_name, file_names);
							if (result == 1)
								exited = true;
							else if (result == 2) {
								go_back2 = true;
								break;
							}
						}
					}
					else if (second_option == TEAM_OPTIONS::BEST_TEAM) {
						//doBestTeamSearch();
						std::cout << "Cok Yakinda...\n";
						break;
					}
					else if (second_option == TEAM_OPTIONS::GO_BACK) {
						go_back1 = true;
						break;
					}
					else
						exited = true;
				}
			}
			else if (first_option == INIT_OPTIONS::LEAGUE_OPTION) {
				//LEAGUE_OPTIONS second_option = getLeagueOption();
				std::cout << "Cok Yakinda...\n";
				go_back1 = true;
				
			}
			else
				exited = true;
		}

		//user_input = getTeamNameFromUser();
		//if (!user_input.compare(exit_input))
		//	break;
		//{
		//	Team team(user_input);
		//	bool failure = true;
		//	// Read files to modify team's properties
		//	for (const auto& name : file_names) {
		//		//if we find at least 1 match we say it is success
		//		failure = simpleParse(name, team) && failure;
		//		//std::cout << name << "\n";
		//	}
		//	// Preset team's info
		//	if (failure)
		//		std::cout << "No match found" << "\n";
		//	else {
		//		//std::cout << team.matches.size() << "size \n";
		//		int n = 1;
		//		std::sort(team.matches.begin(), team.matches.end(), sortByDate);
		//		for (auto& match : team.matches) {
		//			std::cout << n << "-) ";
		//			match.prettyPresent();
		//			//give some time to read
		//			Sleep(500);
		//			n++;
		//		}
		//		presentTeamInfo(team);
		//	}
		//}
	}
}

