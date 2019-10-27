#include "ParseText.h"
#include <sstream>
#include "Match.h"
#include "Team.h"

using namespace std;

int simpleParse(const std::filesystem::path& the_path, Team & team) {
	ifstream file(the_path);
	string line;
	string buffer;
	//comments are after dots
	string comment_str = ".";
	//league names
	string tr_str = "tr";
	string sp_str = "sp";
	string ita_str = "ita";
	string eng_str = "eng";
	string ger_str = "ger";

	if (file.is_open()) {
		//lines are read line by line
		bool first_line = true;
		unsigned int word_no = 1;
		bool match_found = false;
		bool parse_finished = false;
		bool team_home = true;
		Match a_match;
		bool jump_line = false;
		while ( getline(file, line) && !parse_finished) {
			istringstream stream(line);
			// divide line by empty spaces
			jump_line = false;
			while (getline(stream, buffer, ' ') && !jump_line) {
				//first line always dates
				if (first_line) {
					getline(stream, buffer);
					a_match.date = buffer;
					jump_line = true;
					first_line = false;
				}
				//if it starts with "." it is comment
				else if (!buffer.compare(comment_str)) {
					if (match_found) {
					getline(stream, buffer);
					a_match.comment = buffer;
					team.matches.push_back(a_match);
					parse_finished = true;
					}
				}
				//LEAGUES
				else if (!buffer.compare(tr_str)) {
					//TODO: league statistics maybe lates, just jump over leauge name lines
					jump_line = true;
				}
				else if (!buffer.compare(eng_str)) {
					//TODO: league statistics maybe lates, just jump over leauge name lines
					jump_line = true;
				}
				else if (!buffer.compare(ita_str)) {
					//TODO: league statistics maybe lates, just jump over leauge name lines
					jump_line = true;
				}
				else if (!buffer.compare(sp_str)) {
					//TODO: league statistics maybe lates, just jump over leauge name lines
					jump_line = true;
				}
				else if (!buffer.compare(ger_str)) {
					//TODO: league statistics maybe lates, just jump over leauge name lines
					jump_line = true;
				}
				// Actual match info
				else {
					if (match_found)
						break;
					//first name if not input team
					if (buffer.compare(team.name)) {
						//get second name
						a_match.home_name = buffer;
						
						getline(stream, buffer, ' ');
						if (buffer.compare(team.name)) {
							jump_line = true;
							break;
						}
						else {
							a_match.away_name = buffer;
							team_home = false;
							match_found = true;
						}
					}
					else {
						a_match.home_name = buffer;
						getline(stream, buffer, ' ');
						a_match.away_name = buffer;
						match_found = true;
						team_home = true;
					}
					std::string s1;
					std::string s2;
					getline(stream, s1, ' ');
					getline(stream, s2, ' ');
					evaluateFirstHalf(team, a_match, std::stoi(s1), std::stoi(s2), team_home);
					getline(stream, s1, ' ');
					getline(stream, s2, ' ');
					evaluateSecondHalf(team, a_match, std::stoi(s1), std::stoi(s2), team_home);

				
				}
			}
		}
		file.close();
	}
	else {
		cout << "File did not open!\n";
		return 1;
	}
	return 0;
}
void evaluateFirstHalf(Team& team, Match& match,
	unsigned int home_fh_score,
	unsigned int away_fh_score,
	bool is_team_home) {
	//MODIFY MATCH INFO
	match.home_first_half_goals = home_fh_score;
	match.away_first_half_goals = away_fh_score;
	if (home_fh_score > away_fh_score)
		match.first_half_result = HOME_WIN;
	else if (away_fh_score > home_fh_score)
		match.first_half_result = AWAY_WIN;
	else
		match.first_half_result = DRAW;

	//first half infoes
	if (home_fh_score + away_fh_score > 1)
		team.num_of_above_1_5_half_matches++;
	if (home_fh_score + away_fh_score == 0)
		team.num_of_below_0_5_half_matches++;

	if (is_team_home) {
		team.num_of_first_half_goals += home_fh_score;
		if (home_fh_score > away_fh_score)
			team.num_of_first_half_wins++;
		else if (home_fh_score < away_fh_score)
			team.num_of_first_half_losses++;
	}
	else {
		team.num_of_first_half_goals += away_fh_score;
		if (away_fh_score > home_fh_score)
			team.num_of_first_half_wins++;
		else if (away_fh_score < home_fh_score)
			team.num_of_first_half_losses++;
	}

}
void evaluateSecondHalf(Team& team, Match& match,
	unsigned int home_total_score,
	unsigned int away_total_score,
	bool is_team_home) {
	team.num_of_matches++;
	// to find second half goals, remove first half from total score
	unsigned int home_sh_goals = home_total_score - match.home_first_half_goals;
	unsigned int away_sh_goals = away_total_score - match.away_second_half_goals;

	//MODIFY MATCH INFO
	match.home_second_half_goals = home_sh_goals;
	match.away_second_half_goals = away_sh_goals;
	match.home_total_goals = home_total_score;
	match.away_total_goals = away_total_score;
	if (home_total_score > away_total_score)
		match.final_result = HOME_WIN;
	else if (away_total_score > home_total_score)
		match.final_result = AWAY_WIN;
	else {
		match.final_result = DRAW;
		team.num_of_draws++;
	}

	if (home_sh_goals > away_sh_goals)
		match.second_half_result = HOME_WIN;
	else if (away_sh_goals > home_sh_goals)
		match.second_half_result = AWAY_WIN;
	else
		match.second_half_result = DRAW;

	//Above 2.5 goals
	if (home_total_score + away_total_score > 2)
		team.num_of_above_2_5_matches++;
	if (home_total_score + away_total_score < 4)
		team.num_of_below_3_5_matches++;

	if (is_team_home) {
		//second half infoes
		team.num_of_second_half_goals += home_sh_goals;
		team.num_of_second_half_rec_goals += away_sh_goals;
		if (home_sh_goals > away_sh_goals)
			team.num_of_second_half_wins++;
		else if (away_sh_goals > home_sh_goals)
			team.num_of_second_half_losses++;
		//full match infoes
		team.num_of_goals += home_total_score;
		team.num_of_rec_goals += away_total_score;
		if (away_total_score == 0)
			team.num_of_clean_sheets++;
		if (home_total_score > away_total_score) {
			team.num_of_home_wins++;
			team.num_of_wins++;
		}
		else if (away_total_score > home_total_score)
			team.num_of_loses++;
	}
	else {
		//second half infoes
		team.num_of_second_half_goals += away_sh_goals;
		team.num_of_second_half_rec_goals += home_sh_goals;
		if (away_sh_goals > home_sh_goals)
			team.num_of_second_half_wins++;
		else if (home_sh_goals > away_sh_goals)
			team.num_of_second_half_losses++;
		//full match infoes
		team.num_of_goals += away_total_score;
		team.num_of_rec_goals += home_total_score;
		if (home_total_score == 0)
			team.num_of_clean_sheets++;
		if (away_total_score > home_total_score) {
			team.num_of_away_wins++;
			team.num_of_wins++;
		}
		else if (home_total_score > away_total_score)
			team.num_of_loses++;
	}
}