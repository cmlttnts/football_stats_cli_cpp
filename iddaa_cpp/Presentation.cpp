#include "Presentation.h"

using namespace std;

void presentTeamInfo(const Team& team) {
	_presentWinsAndLosses(team);
}

void _presentWinsAndLosses(const Team& team) {

	cout << "\t\t\tWIN LOS INFORMATION" << "\n";
//final result info
	cout << "Total Matches: " << team.num_of_matches << "\n(W: " << team.num_of_wins;
	cout << " D: " << team.num_of_draws << " L: " << team.num_of_losses << ")";
	cout << " Percentage: (W%: " << team.num_of_wins * 100 / float(team.num_of_matches);
	cout << " D%: " << team.num_of_draws * 100 / float(team.num_of_matches);
	cout << " L%: " << team.num_of_losses * 100 / float(team.num_of_matches) << ")\n";
//first half info
	cout << "\t\t\tFirst Half Info\n";
	cout << "(W: " << team.num_of_first_half_wins;
	cout << " D: " << team.num_of_matches - team.num_of_first_half_wins - team.num_of_first_half_losses;
	cout << " L: " << team.num_of_first_half_losses << ")\n";
//second half info
	cout << "\t\t\tSecond Half Info\n";
	cout << "(W: " << team.num_of_second_half_wins;
	cout << " D: " << team.num_of_matches - team.num_of_second_half_wins - team.num_of_second_half_losses;
	cout << " L: " << team.num_of_second_half_losses << ")\n";

// Goals info
	cout << "\t\t\tGOALS INFORMATION\n";
	cout << "over 2.5       : " << team.num_of_above_2_5_matches << "\n";
	cout << "below 3.5      : " << team.num_of_below_3_5_matches << "\n";
	cout << "half below 0.5 : " << team.num_of_below_0_5_half_matches << "\n";
	cout << "half above 1.5 : " << team.num_of_above_1_5_half_matches << "\n";
}

