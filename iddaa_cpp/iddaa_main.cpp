// iddaa_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include "Team.h"
#include "Match.h"
#include "ParseText.h"
#include "Files.h"
#include "Presentation.h"
#include <algorithm>
#include <sstream>


bool sortByDate(const Match& m1, const Match& m2) {
	
	std::istringstream date1(m1.date);
	std::istringstream date2(m2.date);

	std::string day1;
	std::getline(date1, day1, '.');
	int i_day1 = std::stoi(day1);
	
	std::string month1;
	std::getline(date1, month1, '.');
	int i_month1 = std::stoi(month1);

	std::string year1;
	std::getline(date1, year1);
	int i_year1 = std::stoi(year1);

	std::string day2;
	std::getline(date2, day2, '.');
	int i_day2 = std::stoi(day2);

	std::string month2;
	std::getline(date2, month2, '.');
	int i_month2 = std::stoi(month2);

	std::string year2;
	std::getline(date2, year2);
	int i_year2 = std::stoi(year2);

	if (i_year1 < i_year2)
		return true;
	else if (i_year1 == i_year2 && i_month1 < i_month2)
		return true;
	else if (i_year1 == i_year2 && i_month1 == i_month2 && i_day1 < i_day2)
		return true;
	else
		return false;
}


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
				std::sort(team.matches.begin(), team.matches.end(), sortByDate);
				for (auto& match : team.matches) {
					std::cout << n << "-) ";
					match.prettyPresent();
					//give some time to read
					Sleep(500);
					n++;
				}
				presentTeamInfo(team);
			}
		}
	}
}

