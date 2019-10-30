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
	bool match_found = false;
	Match a_match;
	if (file.is_open()) {
		//lines are read line by line
		int next_line = 2;
		bool first_line = true;
		bool parse_finished = false;
		bool team_home = true;
		while (getline(file, line) && !parse_finished){
			istringstream stream(line);
			// divide line by empty spaces
			while (getline(stream, buffer, ' ')){
				if (match_found && next_line > 1) {
					parse_finished = true;
					break;
				}
				//first line always dates
				else if (first_line) {
					getline(stream, buffer);
					a_match.date = buffer;
					first_line = false;
					break;
				}
				//if it starts with "." it is comment
				else if (next_line == 1 && !buffer.compare(comment_str)){
					getline(stream, buffer);
					a_match.comment = buffer;
					parse_finished = true;
				}
				//LEAGUES
				else if (!buffer.compare(tr_str)){
					//TODO: league statistics maybe lates, just jump over leauge name lines
					break;
				}
				else if (!buffer.compare(eng_str)){
					//TODO: league statistics maybe lates, just jump over leauge name lines
					break;
				}
				else if (!buffer.compare(ita_str)){
					//TODO: league statistics maybe lates, just jump over leauge name lines
					break;
				}
				else if (!buffer.compare(sp_str)){
					//TODO: league statistics maybe lates, just jump over leauge name lines
					break;
				}
				else if (!buffer.compare(ger_str)){
					//TODO: league statistics maybe lates, just jump over leauge name lines
					break;
				}
				// Actual match info
				else{
					//first word if not input team
					if (buffer.compare(team.name)){
						//get second name
						std::string temp = buffer;
						getline(stream, buffer, ' ');
						if (buffer.compare(team.name)){
							break;
						}
						else {
							a_match.home_name = temp;
							a_match.away_name = buffer;
							team_home = false;
						}
					}
					else {
						a_match.home_name = buffer;
						getline(stream, buffer, ' ');
						a_match.away_name = buffer;
						team_home = true;
					}
					std::string s1;
					std::string s2;
					//get first half result
					getline(stream, s1, ' ');
					getline(stream, s2, ' ');
					if (s1.empty() || s2.empty())
						break;
					evaluateFirstHalf(team, a_match, std::stoi(s1), std::stoi(s2), team_home);
					//get match result
					getline(stream, s1, ' ');
					getline(stream, s2, ' ');
					if (s1.empty() || s2.empty())
						break;
					match_found = true;
					evaluateSecondHalf(team, a_match, std::stoi(s1), std::stoi(s2), team_home);
					//check if corner info is there
					getline(stream, s1, ' ');
					std::string corner_info_exists = "c";
					if (!s1.compare(corner_info_exists)) {
						//cout << "corner info exists\n";
						//get corner values
						getline(stream, s1, ' ');
						getline(stream, s2, ' ');
						processFirstHalfCorners(team, a_match, std::stoi(s1), std::stoi(s2), team_home);
						getline(stream, s1, ' ');
						getline(stream, s2, ' ');
						processSecondHalfCorners(team, a_match, std::stoi(s1), std::stoi(s2), team_home);
					}
					//cout << line << "line printing \n";
					next_line = 0;
				
				}
			}
			//increment line count, if match found it resets 0 to check for comment if exists
			next_line++;
		}
		file.close();
	}
	else {
		cout << "File did not open!\n";
		return 1;
	}
	if (match_found)
		team.matches.push_back(a_match);
	return !match_found;
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
	unsigned int away_sh_goals = away_total_score - match.away_first_half_goals;

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
		match.picked_team_result = TEAM_DRAW;
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
			match.picked_team_result = TEAM_WIN;
		}
		else if (away_total_score > home_total_score) {
			team.num_of_losses++;
			match.picked_team_result = TEAM_LOSS;
		}
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
			match.picked_team_result = TEAM_WIN;
		}
		else if (home_total_score > away_total_score) {
			team.num_of_losses++;
			match.picked_team_result = TEAM_LOSS;
		}
	}
}
// TODO: takimlarin yedigi kornerleri de say
void processFirstHalfCorners(Team& team, Match& match,
					unsigned int home_fh_corners,
					unsigned int away_fh_corners,
					bool team_is_home) {

	match.home_fh_corners = home_fh_corners;
	match.away_fh_corners = away_fh_corners;
	if (team_is_home) {
		team.num_of_first_half_corners += home_fh_corners;
		team.num_of_first_half_corners_rec += away_fh_corners;
	}
	else {
		team.num_of_first_half_corners += away_fh_corners;
		team.num_of_first_half_corners_rec += home_fh_corners;
	}
}

void processSecondHalfCorners(Team& team, Match& match,
								unsigned int home_sh_corners,
								unsigned int away_sh_corners,
								bool team_is_home) {
	match.home_sh_corners = home_sh_corners;
	match.away_sh_corners = away_sh_corners;
	match.home_total_corners = match.home_fh_corners + match.home_sh_corners;
	match.away_total_corners = match.away_fh_corners + match.away_sh_corners;
	match.corner_info_available = true;

	//how many match has corner info
	team.num_of_corner_info_match++;
	if (team_is_home) {
		team.num_of_second_half_corners += home_sh_corners;
		team.num_of_second_half_corners_rec += away_sh_corners;
		team.num_of_corners += (match.home_fh_corners + match.home_sh_corners);
		team.num_of_corners_rec += (match.away_fh_corners + match.away_sh_corners);
	}
	else {
		team.num_of_second_half_corners += away_sh_corners;
		team.num_of_second_half_corners_rec += home_sh_corners;
		team.num_of_corners += (match.away_fh_corners + match.away_sh_corners);
		team.num_of_corners_rec += (match.home_fh_corners + match.home_sh_corners);
	}


}