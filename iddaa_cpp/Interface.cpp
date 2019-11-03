#include <iostream>
#include <boost/format.hpp>
#include "Interface.h"
#include <fstream>
using namespace std;
using boost::format;
void greeting() {
	cout << format("%30s %s\n") % "" % "IDDAA ANALIZ PROGRAMI";
}

INIT_OPTIONS getInitOptions() {
	cout << format("%-25s %s %-4s\n")% "Takim secenekleri icin" % ":" % "1";
	cout << format("%-25s %s %-4s\n") % "Lig secenekleri icin" % ":" % "2";
	cout << format("%-25s %s %-4s\n") % "Takim listesi icin" % ":" % "3";
	cout << format("%-25s %s %-4s\n") % "Cikis icin" % ":" % "q";
	string user_in;
	bool input_valid = false;
	while (!input_valid) {
		cin >> user_in;
		input_valid = true;
		if (!user_in.compare("1"))
			return INIT_OPTIONS::TEAM_OPTION;
		else if (!user_in.compare("2"))
			return INIT_OPTIONS::LEAGUE_OPTION;
		else if (!user_in.compare("3"))
			return INIT_OPTIONS::TEAM_NAMES_OPTION;
		else if (!user_in.compare("q"))
			return INIT_OPTIONS::EXIT_OPTION;
		else {
			cout << "Gecersiz giris, tekrar deneyin...\n";
			input_valid = false;
		}
	}
}

#include <stdlib.h>
TEAM_OPTIONS getTeamOption() {
	system("cls");
	cout << format("%-25s %s %-4s\n") % "1.1)Takim Analizi icin" % ":" % "1";
	cout << format("%-25s %s %-4s\n") % "1.2)En iyi takimlar icin" % ":" % "2";
	cout << format("%-25s %s %-4s\n") % "Bir geri gitmek icin" % ":" % "g";
	cout << format("%-25s %s %-4s\n") % "Cikis icin" % ":" % "q";

	string user_in;
	bool input_valid = false;
	while (!input_valid) {
		cin >> user_in;
		input_valid = true;
		if (!user_in.compare("1"))
			return TEAM_OPTIONS::TEAM_ANALYSIS;
		else if (!user_in.compare("2"))
			return TEAM_OPTIONS::BEST_TEAM;
		else if (!user_in.compare("q"))
			return TEAM_OPTIONS::EXIT_OPTION;
		else if (!user_in.compare("g"))
			return TEAM_OPTIONS::GO_BACK;
		else {
			cout << "Gecersiz giris, tekrar deneyin...\n";
			input_valid = false;
		}
	}


}

LEAGUE_OPTIONS getLeagueOptions() {

}

std::string getTeamNameFromUser() {
	std::string team_name;
	cout << "\nAnaliz icin takim ismi girin(cikmak icin 'q', geri gitmek icin 'g'): ";
	cin >> team_name;
	return team_name;
}

LEAGUE_OPTIONS getLeagueOption() {

}


void printTeamsPerLeague(const std::vector<std::filesystem::path>& file_paths) {
	vector<std::string> tr_teams;
	vector<std::string> eng_teams;
	vector<std::string> ger_teams;
	vector<std::string> ita_teams;
	vector<std::string> sp_teams;
	vector<std::string> cl_teams;
	for (const auto& file_path : file_paths) {
		//get team names from /teams directory
		std::string file_path_str = file_path.string();
		if (file_path_str.find("cl_teams") != std::string::npos)
			cl_teams = _getTeamsFromFile(file_path_str);
		else if (file_path_str.find("tr_teams") != std::string::npos)
			tr_teams = _getTeamsFromFile(file_path_str);
		else if (file_path_str.find("ger_teams") != std::string::npos)
			ger_teams = _getTeamsFromFile(file_path_str);
		else if (file_path_str.find("eng_teams") != std::string::npos)
			eng_teams = _getTeamsFromFile(file_path_str);
		else if (file_path_str.find("ita_teams") != std::string::npos)
			ita_teams = _getTeamsFromFile(file_path_str);
		else if (file_path_str.find("sp_teams") != std::string::npos)
			sp_teams = _getTeamsFromFile(file_path_str);
	}

	//Now lets order them in alphabetical order
	std::sort(cl_teams.begin(), cl_teams.end());
	std::sort(tr_teams.begin(), tr_teams.end());
	std::sort(ger_teams.begin(), ger_teams.end());
	std::sort(eng_teams.begin(), eng_teams.end());
	std::sort(ita_teams.begin(), ita_teams.end());
	std::sort(sp_teams.begin(), sp_teams.end());

	std::string alt_tire = "______________";
	cout << format("|%=14s||%=14s||%=14s||%=14s||%=14s||%=14s|\n") % "CL" % "TURKIYE" % "ALMANYA" % "INGILTERE" % "ITALYA" % "ISPANYA";
	cout << format("|%=14s||%=14s||%=14s||%=14s||%=14s||%=14s|\n") % alt_tire % alt_tire % alt_tire % alt_tire % alt_tire % alt_tire;
	for (size_t i = 0; i < 20; i++) {
		if (i < cl_teams.size() )
			cout << format("|%=14s|") % cl_teams[i];
		else
			cout << format("|%=14s|") % "";
		if (i < tr_teams.size())
			cout << format("|%=14s|") % tr_teams[i];
		else
			cout << format("|%=14s|") % "";
		if (i < ger_teams.size())
			cout << format("|%=14s|") % ger_teams[i];
		else
			cout << format("|%=14s|") % "";
		if (i < eng_teams.size())
			cout << format("|%=14s|") % eng_teams[i];
		else
			cout << format("|%=14s|") % "";
		if (i < ita_teams.size())
			cout << format("|%=14s|") % ita_teams[i];
		else
			cout << format("|%=14s|") % "";
		if (i < sp_teams.size())
			cout << format("|%=14s|") % sp_teams[i];
		else
			cout << format("|%=14s|") % "";
		cout << "\n";
	}
	//cout << "\n";
}

std::vector<std::string> _getTeamsFromFile(const std::string& path) {
	ifstream file(path);
	std::vector<std::string> temp;
	std::string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			temp.push_back(line);
		}
	}
	else
		std::cout << "File Cannot Be Opened\n";
	file.close();
	return temp;
}