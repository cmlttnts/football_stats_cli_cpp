#include <iostream>
#include <boost/format.hpp>
#include "Interface.h"

using namespace std;
using boost::format;
void greeting() {
	cout << format("%30s %s\n") % "" % "IDDAA ANALIZ PROGRAMI";
}

INIT_OPTIONS getInitOptions() {
	cout << format("%-25s %s %-4s\n")% "Takim secenekleri icin" % ":" % "1";
	cout << format("%-25s %s %-4s\n") % "Lig secenekleri icin" % ":" % "2";
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
		else if (!user_in.compare("q"))
			return INIT_OPTIONS::EXIT_OPTION;
		else {
			cout << "Gecersiz giris, tekrar deneyin...\n";
			input_valid = false;
		}
	}
}

TEAM_OPTIONS getTeamOption() {
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
	cout << "\nAnaliz icin takim ismi girin: ";
	cin >> team_name;
	return team_name;
}