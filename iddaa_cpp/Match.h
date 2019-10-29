#pragma once
#include <string>
enum MatchResult {
HOME_WIN = 1,
DRAW = 0,
AWAY_WIN = 2
};

enum TeamsResult {
TEAM_WIN = 1,
TEAM_DRAW = 0,
TEAM_LOSS = -1
};

class Match {
private:
public:
	std::string pretty_str;
	std::string home_name;
	std::string away_name;
	std::string comment;
	std::string date;
	//goals
	unsigned int home_first_half_goals = 0;
	unsigned int home_second_half_goals = 0;
	unsigned int home_total_goals = 0;
	unsigned int away_first_half_goals = 0;
	unsigned int away_second_half_goals = 0;
	unsigned int away_total_goals = 0;
	//corners
	bool corner_info_available = false;
	unsigned int home_fh_corners= 0;
	unsigned int home_sh_corners= 0;
	unsigned int away_fh_corners=0;
	unsigned int away_sh_corners = 0;
	unsigned int home_total_corners = 0;
	unsigned int away_total_corners = 0;

	//results
	TeamsResult picked_team_result;
	MatchResult first_half_result;
	MatchResult second_half_result;
	MatchResult final_result;
	Match();
	void prettyPresent();
};

