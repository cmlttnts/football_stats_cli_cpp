#include <string>
#include <sstream>
#include "MyAlgortihms.h"

bool sortMatchesByDate(const Match& m1, const Match& m2) {

	std::istringstream date1(m1.date);
	std::istringstream date2(m2.date);

	std::string day1;
	std::getline(date1, day1, '.');
	int i_day1 = std::stoi(day1);

	std::string month1;
	std::getline(date1, month1, '.');
	int i_month1 = std::stoi(month1);

	std::string year1;
	std::getline(date1, year1);
	int i_year1 = std::stoi(year1);

	std::string day2;
	std::getline(date2, day2, '.');
	int i_day2 = std::stoi(day2);

	std::string month2;
	std::getline(date2, month2, '.');
	int i_month2 = std::stoi(month2);

	std::string year2;
	std::getline(date2, year2);
	int i_year2 = std::stoi(year2);

	if (i_year1 < i_year2)
		return true;
	else if (i_year1 == i_year2 && i_month1 < i_month2)
		return true;
	else if (i_year1 == i_year2 && i_month1 == i_month2 && i_day1 < i_day2)
		return true;
	else
		return false;
}

void rankTeamsByOption(std::vector<Team>& teams, BEST_TEAM_OPTIONS option) {
	switch (option)
	{
	case BEST_TEAM_OPTIONS::BEST_RESULTS:
		break;
	case BEST_TEAM_OPTIONS::WORST_RESULTS:
		break;
	case BEST_TEAM_OPTIONS::MOST_GOALS_SCORED:
		break;
	case BEST_TEAM_OPTIONS::LEAST_GOALS_SCORED:
		break;
	case BEST_TEAM_OPTIONS::MOST_GOALS_RECEIVED:
		break;
	case BEST_TEAM_OPTIONS::LEAST_GOALS_RECEIVED:
		break;
	case BEST_TEAM_OPTIONS::COMEBAKCS:
		break;
	case BEST_TEAM_OPTIONS::CORNERS:
		break;
	case BEST_TEAM_OPTIONS::GO_BACK:
		break;
	case BEST_TEAM_OPTIONS::EXIT:
		break;
	default:
		break;
	}
}

bool sortByWins(const Team& team1, const Team& team2) {
	if (team1.num_of_wins > team2.num_of_wins)
		return true;
	else
		return false;
}

bool sortByLosses(const Team& team1, const Team& team2) {
	if (team1.num_of_losses > team2.num_of_losses)
		return true;
	else
		return false;
}

bool sortByFHWins(const Team& team1, const Team& team2) {
	if (team1.num_of_first_half_wins > team2.num_of_first_half_wins)
		return true;
	else
		return false;
}

bool sortByFHLosses(const Team& team1, const Team& team2) {
	if (team1.num_of_first_half_losses > team2.num_of_first_half_losses)
		return true;
	else
		return false;
}

bool sortBySHWins(const Team& team1, const Team& team2) {
	if (team1.num_of_second_half_wins > team2.num_of_second_half_wins)
		return true;
	else
		return false;
}

bool sortBySHLosses(const Team& team1, const Team& team2) {
	if (team1.num_of_second_half_losses > team2.num_of_second_half_losses)
		return true;
	else
		return false;
}

bool sortByTotalCorners(const Team& team1, const Team& team2) {
	if (team1.num_of_corner_info_match < 1)
		return false;
	if (team2.num_of_corner_info_match < 1)
		return true;
	if (((team1.num_of_corners + team1.num_of_corners_rec)/ (float)team1.num_of_corner_info_match)  > ((team2.num_of_corners + team2.num_of_corners_rec)/ (float)team2.num_of_corner_info_match)) 
		return true;
	else
		return false;
}

