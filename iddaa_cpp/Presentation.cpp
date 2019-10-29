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
	cout << "\t\t\tIlk yarilarda\n";
	cout << "(W: " << team.num_of_first_half_wins;
	cout << " D: " << team.num_of_matches - team.num_of_first_half_wins - team.num_of_first_half_losses;
	cout << " L: " << team.num_of_first_half_losses << ")\n";
//second half info
	cout << "\t\t\tIkinci yarilarda\n";
	cout << "(W: " << team.num_of_second_half_wins;
	cout << " D: " << team.num_of_matches - team.num_of_second_half_wins - team.num_of_second_half_losses;
	cout << " L: " << team.num_of_second_half_losses << ")\n";

// Goals info
	cout << "\t\t\tGOLLER\n";
	cout << "2.5 ust    : " << team.num_of_above_2_5_matches << " / ";
	cout << "3.5 alt    : " << team.num_of_below_3_5_matches << "\n";
	cout << "iy 0.5 alt : " << team.num_of_below_0_5_half_matches << " / ";
	cout << "iy 1.5 ust : " << team.num_of_above_1_5_half_matches << "\n";

//corner info
	cout << "\t\t\tKORNER ISTATISTIKLERI\n";
	if (team.num_of_corner_info_match > 0) {
		cout << "korner bilgisi olan mac sayisi: " << team.num_of_corner_info_match << "\n";
		cout << "1y ort. : " << team.num_of_first_half_corners / float(team.num_of_corner_info_match);
		cout << " / 2y ort. : " << team.num_of_second_half_corners / float(team.num_of_corner_info_match);
		cout << " = Mac sonu ort. : " << team.num_of_corners / float(team.num_of_corner_info_match);
		cout << "\n";
	}
	else {
		cout << "Korner bilgisi yok\n";
	}
}

