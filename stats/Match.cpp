#include "Match.h"
#include <iostream>
Match::Match()
:pretty_str(""), home_name(""), away_name(""),
comment(""), date(""),
home_first_half_goals(0),
home_second_half_goals(0),
home_total_goals(0),
away_first_half_goals(0),
away_second_half_goals(0),
away_total_goals(0),
first_half_result(MatchResult::DRAW),
second_half_result(MatchResult::DRAW),
final_result(MatchResult::DRAW)
{
}


#include <windows.h>

void Match::prettyPresent() {

	HANDLE h_cons;
	h_cons = GetStdHandle(STD_OUTPUT_HANDLE);

	if (picked_team_result == TeamsResult::TEAM_WIN)
		SetConsoleTextAttribute(h_cons, 2);
	else if (picked_team_result == TeamsResult::TEAM_LOSS)
		SetConsoleTextAttribute(h_cons, 12);
	else
		SetConsoleTextAttribute(h_cons, 7);
	std::cout << "\t\t\tTarih : " << date << "\n";
	pretty_str = "\t" + home_name + "-" + away_name + " : ";
	pretty_str += "1Y: " + std::to_string(home_first_half_goals) + "-";
	pretty_str += std::to_string(away_first_half_goals) + " / ";
	pretty_str += "2Y: " + std::to_string(home_second_half_goals) + "-";
	pretty_str += std::to_string(away_second_half_goals) + " = MS: ";
	pretty_str += std::to_string(home_total_goals) + "-";
	pretty_str += std::to_string(away_total_goals);
	pretty_str += " (" + std::to_string(static_cast<int>(first_half_result)) + "/" + std::to_string(static_cast<int>(final_result)) + ")";
	std::cout << pretty_str << " ";
	
	if (corner_info_available) {
		std::cout << "Corners: (" << home_fh_corners << "-" << away_fh_corners << "/";
		std::cout << home_sh_corners << "-" << away_sh_corners << "= ";
		std::cout << home_total_corners << "-" << away_total_corners << ")";
	}
	SetConsoleTextAttribute(h_cons, 7);
	std::cout << "\n\n";



	if (comment.compare("")) {
		SetConsoleTextAttribute(h_cons, 14);
		std::cout << "Yorum: " << comment << "\n\n";
	}
	SetConsoleTextAttribute(h_cons, 7);

}










