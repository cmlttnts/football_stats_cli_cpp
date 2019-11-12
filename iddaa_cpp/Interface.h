#pragma once
#include <string>
#include <filesystem>
#include <vector>
//inital options
enum class INIT_OPTIONS {
TEAM_OPTION,
LEAGUE_OPTION,
TEAM_NAMES_OPTION,
EXIT
};
//if team options selected, those options
enum class TEAM_OPTIONS {
	TEAM_ANALYSIS,
	BEST_TEAM,
	GO_BACK,
	EXIT
};
enum class TEAM_ANALYSIS_OPTIONS {
	TEAM_PICKED,
	GO_BACK,
	EXIT
};

enum class BEST_TEAM_OPTIONS {
	BEST_RESULTS,
	WORST_RESULTS,
	MOST_GOALS_SCORED,
	LEAST_GOALS_SCORED,
	MOST_GOALS_RECEIVED,
	LEAST_GOALS_RECEIVED,
	COMEBACKS,
	CORNERS,
	GO_BACK,
	EXIT
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

BEST_TEAM_OPTIONS getBestTeamOption();

LEAGUE_OPTIONS getLeagueOption();
void printTeamsPerLeague(const std::vector<std::filesystem::path>&);
std::vector<std::string> _getTeamsFromFile(const std::string&);