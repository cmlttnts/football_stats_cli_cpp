#pragma once
#include <string>

//inital options
enum class INIT_OPTIONS {
TEAM_OPTION,
LEAGUE_OPTION,
EXIT_OPTION
};
//if team options selected, those options
enum class TEAM_OPTIONS {
	TEAM_ANALYSIS,
	BEST_TEAM,
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

INIT_OPTIONS getInitOptions();
std::string getTeamNameFromUser();