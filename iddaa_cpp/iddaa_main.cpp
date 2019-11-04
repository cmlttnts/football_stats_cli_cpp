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




int main() {
	std::string exit_input = "q";
	std::string user_input;
	std::cout << "Press 'q' for exit" << std::endl;
	std::string weeks_path;
	std::string teams_path;
	//temporary variables block
	{
		std::string cur_path = std::filesystem::current_path().string();
		std::string iddaa_cpp_part = "\\iddaa_cpp";
		weeks_path = cur_path.substr(0, cur_path.find(iddaa_cpp_part));
		teams_path = cur_path.substr(0, cur_path.find(iddaa_cpp_part));
	}
	weeks_path += "\\iddaa_cpp\\weeks";
	teams_path += "\\iddaa_cpp\\teams";
	std::vector<std::filesystem::path> match_file_names = getFileNames(weeks_path);
	std::vector<std::filesystem::path> team_file_names = getFileNames(teams_path);
	greeting();
	bool exited = false;
	bool go_back_to_init = false;
	bool go_back_to_team = false;
	bool go_back_to_league = false;
	while (!exited) {
		INIT_OPTIONS first_opt = getInitOptions();
		switch (first_opt) {
			case INIT_OPTIONS::TEAM_OPTION:
				go_back_to_init = false;
				while (!exited && go_back_to_init) {
					TEAM_OPTIONS team_opt = getTeamOption();
					switch (team_opt) {
						case TEAM_OPTIONS::TEAM_ANALYSIS:
							go_back_to_team = false;
							while (!exited && go_back_to_team) {
								std::string team_name = getTeamNameFromUser();
								//TODO
							}
							break;
						case TEAM_OPTIONS::BEST_TEAM:
							go_back_to_team = false;
							while (!exited && go_back_to_team) {
								BEST_TEAM_OPTIONS best_t_opt = getBestTeamOption();
								switch (best_t_opt) {
									case BEST_TEAM_OPTIONS::BEST_RESULTS:
										break;
									case BEST_TEAM_OPTIONS::WORST_RESULTS:
										break;
									case BEST_TEAM_OPTIONS::MOST_GOALS_SCORED:
										break;
									case BEST_TEAM_OPTIONS::LEAST_GOALS_SCORED:
										break;
									case BEST_TEAM_OPTIONS::MOST_GOALS_RECEIVED:
										break;
									case BEST_TEAM_OPTIONS::LEAST_GOALS_RECEIVED:
										break;
									case BEST_TEAM_OPTIONS::COMEBAKCS:
										break;
									case BEST_TEAM_OPTIONS::CORNERS:
										break;
									case BEST_TEAM_OPTIONS::GO_BACK:
										go_back_to_team = true;
										break;
									case BEST_TEAM_OPTIONS::EXIT:
										exited = true;
										break;
								}
							}
							break;
						case TEAM_OPTIONS::GO_BACK:
							go_back_to_init = true;
							break;
						case TEAM_OPTIONS::EXIT:
							exited = true;
					}
				}
				break;
			case INIT_OPTIONS::LEAGUE_OPTION:
				break;
			case INIT_OPTIONS::TEAM_NAMES_OPTION:
				break;
			case INIT_OPTIONS::EXIT:
				break;
		}
	}
}
















//		INIT_OPTIONS first_option = getInitOptions();
//		go_back_to_init = false;
//		while (!exited && !go_back_to_init) {
//			switch (first_option){
//				case INIT_OPTIONS::TEAM_OPTION:
//					TEAM_OPTIONS second_option = getTeamOption();
//					go_back_to_team = false;
//					while (!exited && !go_back_to_team) {
//						switch (second_option){
//							case TEAM_OPTIONS::TEAM_ANALYSIS:{
//								std::string team_name = getTeamNameFromUser();
//								int choice = presentTeam(team_name, match_file_names);
//								exited = choice == 1;
//								go_back_to_team = choice == 2;
//							}
//								break;
//							case TEAM_OPTIONS::BEST_TEAM:
//								while (!exited && !go_back_to_team) {
//									BEST_TEAM_OPTIONS third_option = getBestTeamOption();
//									switch (third_option){
//										case BEST_TEAM_OPTIONS::BEST_RESULTS:
//											break;
//										case BEST_TEAM_OPTIONS::WORST_RESULTS:
//											break;
//										case BEST_TEAM_OPTIONS::MOST_GOALS_SCORED:
//											break;
//										case BEST_TEAM_OPTIONS::LEAST_GOALS_SCORED:
//											break;
//										case BEST_TEAM_OPTIONS::MOST_GOALS_RECEIVED:
//											break;
//										case BEST_TEAM_OPTIONS::LEAST_GOALS_RECEIVED:
//											break;
//										case BEST_TEAM_OPTIONS::COMEBAKCS:
//											break;
//										case BEST_TEAM_OPTIONS::CORNERS:
//											break;
//										case BEST_TEAM_OPTIONS::GO_BACK:
//											go_back_to_team = true;
//											break;
//										case BEST_TEAM_OPTIONS::EXIT:
//											exited = true;
//											break;
//										default:
//											break;
//									}
//								}
//								break;
//							case TEAM_OPTIONS::GO_BACK:
//								go_back_to_init = true;
//								break;
//							case TEAM_OPTIONS::EXIT:
//								exited = true;
//								break;
//							default:
//								break;
//						}
//					}
//				break;
//			case INIT_OPTIONS::LEAGUE_OPTION:
//				std::cout << "Cok Yakinda Geliyor...\n";
//				go_back_to_init = true;
//				break;
//			case INIT_OPTIONS::TEAM_NAMES_OPTION:
//				printTeamsPerLeague(team_file_names);
//				break;
//			case INIT_OPTIONS::EXIT:
//				exited = true;
//			default:
//				break;
//			}
//		}
//	}
//}
