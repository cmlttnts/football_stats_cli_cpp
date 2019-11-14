#include <iostream>
#include <boost/format.hpp>
#include "Interface.h"
#include <fstream>
using namespace std;
using boost::format;
void greeting() {
	cout << format("%30s %s\n") % "" % "IDDAA ANALIZ PROGRAMI";
}
// TODO: Add comparison of two teams, (karsilastirmali goruntu secenegi, iki takim ismi girip yanyana ozllik)
INIT_OPTIONS getInitOptions() {
	cout << format("%s%-40T-%s %-4s\n")% "1.Takim secenekleri icin" % ":" % "1";
	cout << format("%s%-40T-%s %-4s\n") % "2.Iki takim karsilastirmak icin" % ":" % "2";
	cout << format("%s%-40T-%s %-4s\n") % "3.Lig secenekleri icin" % ":" % "3";
	cout << format("%s%-40T-%s %-4s\n") % "4.Takim listesi icin" % ":" % "4";
	cout << format("%s%-40T-%s %-4s\n") % "5.Cikis icin" % ":" % "q";
	string user_in;
	while (1) {
		cin >> user_in;
		if (!user_in.compare("1"))
			return INIT_OPTIONS::TEAM_OPTION;
		else if (!user_in.compare("2"))
			return INIT_OPTIONS::COMPARE_TWO;
		else if (!user_in.compare("3"))
			return INIT_OPTIONS::LEAGUE_OPTION;
		else if (!user_in.compare("4"))
			return INIT_OPTIONS::TEAM_NAMES_OPTION;
		else if (!user_in.compare("q"))
			return INIT_OPTIONS::EXIT;
		else {
			cout << "Gecersiz giris, tekrar deneyin...\n";
		}
	}
}

#include <stdlib.h>
TEAM_OPTIONS getTeamOption() {
	system("cls");
	cout << format("%s%-40T-%s %-4s\n") % "1.1)Takim Analizi icin" % ":" % "1";
	cout << format("%s%-40T-%s %-4s\n") % "1.2)En iyi takimlar icin" % ":" % "2";
	cout << format("%s%-40T-%s %-4s\n") % "Bir geri gitmek icin" % ":" % "g";
	cout << format("%s%-40T-%s %-4s\n") % "Cikis icin" % ":" % "q";

	string user_in;
	while (1) {
		cin >> user_in;
		if (!user_in.compare("1"))
			return TEAM_OPTIONS::TEAM_ANALYSIS;
		else if (!user_in.compare("2"))
			return TEAM_OPTIONS::BEST_TEAM;
		else if (!user_in.compare("q"))
			return TEAM_OPTIONS::EXIT;
		else if (!user_in.compare("g"))
			return TEAM_OPTIONS::GO_BACK;
		else {
			cout << "Gecersiz giris, tekrar deneyin...\n";
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

std::tuple<std::string, std::string, COMPARE_TWO_OPTIONS> getTwoTeamNamesForCompare() {
	std::tuple<std::string, std::string, COMPARE_TWO_OPTIONS> team_names;
	cout << "\nKarsilastirmak icin iki takim ismi girin(cikmak icin 'q', geri gitmek icin 'g')\n";
	cout << "Ev Sahibi: ";
	std::string name;
	cin >> name;
	if (!name.compare("q")) {
		std::get<2>(team_names) = COMPARE_TWO_OPTIONS::EXIT;
		return team_names;
	}
	else if (!name.compare("g")) {
		std::get<2>(team_names) = COMPARE_TWO_OPTIONS::GO_BACK;
		return team_names;
	}
	std::get<0>(team_names) = name;

	cout << "Deplasman: ";
	cin >> name;
	if (!name.compare("q")) {
		std::get<2>(team_names) = COMPARE_TWO_OPTIONS::EXIT;
		return team_names;
	}
	else if (!name.compare("g")) {
		std::get<2>(team_names) = COMPARE_TWO_OPTIONS::GO_BACK;
		return team_names;
	}
	std::get<1>(team_names) = name;
	std::get<2>(team_names) = COMPARE_TWO_OPTIONS::TEAMS_PICKED;
	return team_names;
}

BEST_TEAM_OPTIONS getBestTeamOption() {
	//system("cls");
	cout << format("%s%-40T-%s %-4s\n") % "1.2.1)En iyi sonuc alanlar" % ":" % "1";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.2)En kotu sonuc alanlar" % ":" % "2";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.3)En cok gol atanlar" % ":" % "3";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.4)En az gol atanlar" % ":" % "4";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.5)En cok gol yiyenler" % ":" % "5";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.6)En az gol yiyenler" % ":" % "6";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.7)Maclarinda en cok gol olanlar" % ":" % "7";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.8)Maclarinda en az gol olanlar" % ":" % "8";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.9)Geri donuslerde enler" % ":" % "9";
	cout << format("%s%-40T-%s %-4s\n") % "1.2.10)Kornerlerde enler" % ":" % "10";

	cout << format("%s%-40T-%s %-4s\n") % "Bir geri gitmek icin" % ":" % "g";
	cout << format("%s%-40T-%s %-4s\n") % "Cikis icin" % ":" % "q";

	std::string user_in;
	while (1) {
		cin >> user_in;
		if (!user_in.compare("1"))
			return BEST_TEAM_OPTIONS::BEST_RESULTS;
		else if (!user_in.compare("2"))
			return BEST_TEAM_OPTIONS::WORST_RESULTS;
		else if (!user_in.compare("3"))
			return BEST_TEAM_OPTIONS::MOST_GOALS_SCORED;
		else if (!user_in.compare("4"))
			return BEST_TEAM_OPTIONS::LEAST_GOALS_SCORED;
		else if (!user_in.compare("5"))
			return BEST_TEAM_OPTIONS::MOST_GOALS_RECEIVED;
		else if (!user_in.compare("6"))
			return BEST_TEAM_OPTIONS::LEAST_GOALS_RECEIVED;
		else if (!user_in.compare("7"))
			return BEST_TEAM_OPTIONS::MOST_GOALS_IN_MATCHES;
		else if (!user_in.compare("8"))
			return BEST_TEAM_OPTIONS::LEAST_GOALS_IN_MATCHES;
		else if (!user_in.compare("9"))
			return BEST_TEAM_OPTIONS::COMEBACKS;
		else if (!user_in.compare("10"))
			return BEST_TEAM_OPTIONS::CORNERS;
		else if (!user_in.compare("g"))
			return BEST_TEAM_OPTIONS::GO_BACK;
		else if (!user_in.compare("q"))
			return BEST_TEAM_OPTIONS::EXIT;
		else {
			cout << "Gecersiz giris, tekrar deneyin...\n";
		}
	}
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