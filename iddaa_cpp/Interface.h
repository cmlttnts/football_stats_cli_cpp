#pragma once
#include <string>
#include <filesystem>
#include <vector>
//inital options
enum class INIT_OPTIONS {
TEAM_OPTION,
LEAGUE_OPTION,
TEAM_NAMES_OPTION,
EXIT_OPTION
};
//if team options selected, those options
enum class TEAM_OPTIONS {
	TEAM_ANALYSIS,
	BEST_TEAM,
	GO_BACK,
	EXIT_OPTION
};
// if league options selected, which league
enum class LEAGUE_OPTIONS {
	TR,
	GER,
	ENG,
	ITA,
	SP
};
void greeting();
INIT_OPTIONS getInitOptions();

TEAM_OPTIONS getTeamOption();
std::string getTeamNameFromUser();

LEAGUE_OPTIONS getLeagueOption();
void printTeamsPerLeague(const std::vector<std::filesystem::path>&);
std::vector<std::string> _getTeamsFromFile(const std::string&);