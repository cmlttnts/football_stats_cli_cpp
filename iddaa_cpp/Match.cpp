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
first_half_result(DRAW),
second_half_result(DRAW),
final_result(DRAW)
{
}



void Match::prettyPresent() {

	std::cout << "\t\t\tTarih : " << date << "\n";
	pretty_str = "\t" + home_name + "-" + away_name + " : ";
	pretty_str += "1Y: " + std::to_string(home_first_half_goals) + "-";
	pretty_str += std::to_string(away_first_half_goals) + " / ";
	pretty_str += "2Y: " + std::to_string(home_second_half_goals) + "-";
	pretty_str += std::to_string(away_second_half_goals) + " = MS: ";
	pretty_str += std::to_string(home_total_goals) + "-";
	pretty_str += std::to_string(away_total_goals);
	pretty_str += " (" + std::to_string(first_half_result) + "/" + std::to_string(final_result) + ")";
	std::cout << pretty_str << " ";
	
	if (corner_info_available) {
		std::cout << "Corners: (" << home_fh_corners << "-" << away_fh_corners << "/";
		std::cout << home_sh_corners << "-" << away_sh_corners << "= ";
		std::cout << home_total_corners << "-" << away_total_corners << ")";
	}

	std::cout << "\n\n";



	if(comment.compare(""))
		std::cout << "macin yorumu: " << comment << "\n\n";
}










