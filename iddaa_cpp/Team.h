#ifndef _IDDAA_TEAM_H_
#define _IDDAA_TEAM_H_
#include <string>
class Team {
private:
	std::string name;
	unsigned int num_of_matches;
	unsigned int num_of_goals;
	unsigned int num_of_rec_goals;
	unsigned int num_of_wins;
	unsigned int num_of_loses;
	unsigned int num_of_draws;
	unsigned int num_of_home_wins;
	unsigned int num_of_away_wins;
	unsigned int num_of_first_half_goals;
	unsigned int num_of_second_half_goals;
	unsigned int num_of_above_2_5_matches;
	unsigned int num_of_below_2_5_matches;
	unsigned int num_of_first_half_wins;
	unsigned int num_of_second_half_wins;

public:
	Team();
	Team(std::string);
	std::string getName();
};

#endif