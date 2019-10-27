#pragma once
#include <string>
enum MatchResult {
HOME_WIN = 1,
DRAW = 0,
AWAY_WIN = 2
};

class Match {
private:
	std::string full_str;
	std::string home_name;
	std::string away_name;
	std::string comment;
	unsigned int home_first_half_goals;
	unsigned int home_second_half_goals;
	unsigned int home_total_goals;
	unsigned int away_first_half_goals;
	unsigned int away_second_half_goals;
	unsigned int away_total_goals;
	MatchResult first_half_result;
	MatchResult second_half_result;
	MatchResult final_result;
public:
	Match();
	Match(std::string);
};