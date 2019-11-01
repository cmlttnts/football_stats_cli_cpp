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

void printTeamOptions() {
}
void printLeagueOptions() {

}

std::string getTeamNameFromUser() {
	std::string team_name;
	cout << "\nAnaliz icin takim ismi girin: ";
	cin >> team_name;
	return team_name;
}