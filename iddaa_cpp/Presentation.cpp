#include "Presentation.h"

using namespace std;

void presentTeamInfo(const Team& team) {
	_presentWinsAndLosses(team);
}

void _presentWinsAndLosses(const Team& team) {
	cout << "\t\t\tWIN LOS INFORMATION" << "\n\n";
	cout << "Total Matches: " << team.num_of_matches << " (W: " << team.num_of_wins;
	cout << " D: " << team.num_of_draws << " L: " << team.num_of_losses << ")";
	cout << " Percentage: (W%: " << team.num_of_wins * 100 / float(team.num_of_matches);
	cout << " D%: " << team.num_of_draws * 100 / float(team.num_of_matches);
	cout << " L%: " << team.num_of_losses * 100 / float(team.num_of_matches) << ")\n\n";

}