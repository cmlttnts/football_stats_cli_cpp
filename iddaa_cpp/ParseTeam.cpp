#include "ParseTeam.h"
#include <sstream>
#include "Match.h"
#include "Team.h"
#include "OneLineInfo.h"
#include "Interface.h"
using namespace std;

std::pair<Team, bool> searchFilesForTeam(const std::vector<std::filesystem::path>& file_names, const std::string& team_name, LEAGUE_SEARCH_OPTION search_opt) {

	std::pair<Team, bool> team_info;
	team_info.first = Team(team_name);
	//boolean failure of finding that team in the search of files
	team_info.second = true;
	// Read files to modify team's properties
	for (const auto& name : file_names) {
		//if we find at least 1 match we say it is success
		std::string file_str = name.string();
		//if only cl, search cl files
		if(search_opt == LEAGUE_SEARCH_OPTION::ONLY_CL && (file_str.find("cl") != std::string::npos))
			team_info.second = searchTeamMatch(name, team_info.first) && team_info.second;
		else if(search_opt == LEAGUE_SEARCH_OPTION::ONLY_LEAGUES && (file_str.find("cl") == std::string::npos))
			team_info.second = searchTeamMatch(name, team_info.first) && team_info.second;
		else if(search_opt == LEAGUE_SEARCH_OPTION::BOTH)// include both cl and leagues
			team_info.second = searchTeamMatch(name, team_info.first) && team_info.second;
	}
	// Preset team's info
	if (team_info.second) {
		std::cout << "Dosyalarda boyle bir takim bilgisi yok!" << "\n";
	}
	return team_info;
}

int searchTeamMatch(const std::filesystem::path& the_path, Team & team) {
	ifstream file(the_path);
	if (file.is_open()) {
		string line;
		bool match_found = false;
		Match a_match;
		//lines are read line by line
		int next_line = 2;
		bool first_line = true;
		bool parse_finished = false;
		bool team_home = true;
		while (getline(file, line) && !parse_finished){
			if (match_found && next_line > 1) {
				parse_finished = true;
				break;
			}
			//first line always dates
			else if (first_line) {
				a_match.date = line.substr(5);
				first_line = false;
			}
			//if it starts with "." it is comment
			else if (line[0] == '.'){
				if (next_line == 1) {
					a_match.comment = line.substr(2);
					parse_finished = true;
					break;
				}
			}
			// Actual match info
			else{
				OneLineData data = getDataFromLine(line);
				//if score not availabe no need to do anything
				if(!data.score_info_available)
					continue;
				if (data.home_name.compare(team.name)){
					//get second name
					if (data.away_name.compare(team.name)){
						//if both not our team's name, jump and parse next line
						continue;
					}
					else {
						a_match.home_name = data.home_name;
						a_match.away_name = data.away_name;
						team_home = false;
					}
				}
				else {
					a_match.home_name = data.home_name;
					a_match.away_name = data.away_name;
					team_home = true;
				}
				match_found = true;
				evaluateFirstHalf(team, a_match, data.home_fh_score, data.away_fh_score, team_home);
				evaluateSecondHalf(team, a_match, data.home_final_score, data.away_final_score, team_home);

				if (data.corner_info_availabe) {
					processFirstHalfCorners(team, a_match, data.home_fh_corners, data.away_fh_corners, team_home);
					processSecondHalfCorners(team, a_match, data.home_sh_corners, data.away_sh_corners, team_home);
				}
				next_line = 0;
				
			}
			//increment line count, if match found it resets 0 to check for comment if exists
			next_line++;
		}
		file.close();
		if (match_found) {
			team.matches.push_back(a_match);
			return 0; // success
		}
	}
	else
		cout << "File did not open!\n";
	return 1; // failure
}

void evaluateFirstHalf(Team& team, Match& match,
						unsigned int home_fh_score,
						unsigned int away_fh_score,
						bool is_team_home) {
	//MODIFY MATCH INFO
	match.home_first_half_goals = home_fh_score;
	match.away_first_half_goals = away_fh_score;
	if (home_fh_score > away_fh_score)
		match.first_half_result = MatchResult::HOME_WIN;
	else if (away_fh_score > home_fh_score)
		match.first_half_result = MatchResult::AWAY_WIN;
	else
		match.first_half_result = MatchResult::DRAW;

	//first half infoes
	if (home_fh_score + away_fh_score > 1)
		team.num_of_above_1_5_half_matches++;
	if (home_fh_score + away_fh_score == 0)
		team.num_of_below_0_5_half_matches++;

	if (is_team_home) {
		team.num_of_first_half_goals += home_fh_score;
		team.num_of_first_half_goals_rec += away_fh_score;
		if (home_fh_score > away_fh_score)
			team.num_of_first_half_wins++;
		else if (home_fh_score < away_fh_score)
			team.num_of_first_half_losses++;
	}
	else {
		team.num_of_first_half_goals += away_fh_score;
		team.num_of_first_half_goals_rec += home_fh_score;
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
		match.final_result = MatchResult::HOME_WIN;
	else if (away_total_score > home_total_score)
		match.final_result = MatchResult::AWAY_WIN;
	else {
		match.final_result = MatchResult::DRAW;
		team.num_of_draws++;

		match.picked_team_result = TeamsResult::TEAM_DRAW;
	}

	if (home_sh_goals > away_sh_goals)
		match.second_half_result = MatchResult::HOME_WIN;
	else if (away_sh_goals > home_sh_goals)
		match.second_half_result = MatchResult::AWAY_WIN;
	else
		match.second_half_result = MatchResult::DRAW;
	//kg var
	if (home_total_score > 0 && away_total_score > 0)
		team.num_of_kg_var_matches++;

	//Above 2.5 goals
	if (home_total_score + away_total_score > 2)
		team.num_of_above_2_5_matches++;
	if (home_total_score + away_total_score < 4)
		team.num_of_below_3_5_matches++;

	if (is_team_home) {
		//second half infoes
		team.num_of_home_goals += home_total_score;
		team.num_of_home_goals_rec += away_total_score;
		team.num_of_home_matches++;
		team.num_of_second_half_goals += home_sh_goals;
		team.num_of_second_half_goals_rec += away_sh_goals;
		if (home_sh_goals > away_sh_goals)
			team.num_of_second_half_wins++;
		else if (away_sh_goals > home_sh_goals)
			team.num_of_second_half_losses++;
		//full match infoes
		team.num_of_goals += home_total_score;
		team.num_of_goals_rec += away_total_score;
		if (away_total_score == 0)
			team.num_of_clean_sheets++;
		if (home_total_score > away_total_score) {
			team.num_of_home_wins++;
			team.num_of_wins++;
			match.picked_team_result =TeamsResult::TEAM_WIN;
		}
		else if (away_total_score > home_total_score) {
			team.num_of_losses++;
			team.num_of_home_losses++;
			match.picked_team_result = TeamsResult::TEAM_LOSS;
		}
		//draws
		else {
			team.num_of_home_draws++;
		}
		//COMEBACKS
		if (match.first_half_result == MatchResult::HOME_WIN && (match.final_result == MatchResult::DRAW || match.final_result == MatchResult::AWAY_WIN))
			team.num_of_gobacks++;
		if (match.first_half_result == MatchResult::AWAY_WIN && (match.final_result == MatchResult::DRAW || match.final_result == MatchResult::HOME_WIN))
			team.num_of_comebacks++;


	}
	else {
		//second half infoes
		team.num_of_away_goals += away_total_score;
		team.num_of_away_goals_rec += home_total_score;
		team.num_of_away_matches++;
		team.num_of_second_half_goals += away_sh_goals;
		team.num_of_second_half_goals_rec += home_sh_goals;
		if (away_sh_goals > home_sh_goals)
			team.num_of_second_half_wins++;
		else if (home_sh_goals > away_sh_goals)
			team.num_of_second_half_losses++;
		//full match infoes
		team.num_of_goals += away_total_score;
		team.num_of_goals_rec += home_total_score;
		if (home_total_score == 0)
			team.num_of_clean_sheets++;
		if (away_total_score > home_total_score) {
			team.num_of_away_wins++;
			team.num_of_wins++;
			match.picked_team_result = TeamsResult::TEAM_WIN;
		}
		else if (home_total_score > away_total_score) {
			team.num_of_losses++;
			team.num_of_away_losses++;
			match.picked_team_result = TeamsResult::TEAM_LOSS;
		}
		else {
			team.num_of_away_draws++;
		}
		//COMEBACKS
		if (match.first_half_result == MatchResult::HOME_WIN && (match.final_result == MatchResult::DRAW || match.final_result == MatchResult::AWAY_WIN))
			team.num_of_comebacks++;
		if (match.first_half_result == MatchResult::AWAY_WIN && (match.final_result == MatchResult::DRAW || match.final_result == MatchResult::HOME_WIN))
			team.num_of_gobacks++;
	}
}
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


std::vector<Team> getAllTeamsStats(const std::vector<std::filesystem::path>& file_paths) {
	std::vector<Team> teams;
	//parse each file in files
	for (const auto& file_path : file_paths) {
		//cout << file_path << "\n";
		std::string file_str = file_path.string();
		//remove cl search, TODO: what if want to seach CL
		if (file_str.find("cl") != std::string::npos)
			continue;
		parseFileForStats(file_path, teams);
	}
	//return all teams with statistics
	return teams;
}

void parseFileForStats(const std::filesystem::path& the_path, std::vector<Team>& teams) {
	ifstream file(the_path);
	string line;
	if (file.is_open()) {
		bool first_line = true;
		while (getline(file, line)) {
			if (first_line) {
				first_line = false;
			}
			else if (line[0] == '.')
				first_line = false;
			else {
				OneLineData data;
				//std::cout << "line:" << line << "\n";
				data = getDataFromLine(line);
				parseLineForStats(teams, data);
			}
		}
	}
	else {
		std::cout << "File cannot be opened\n";
	}
}

int parseLineForStats(std::vector<Team>& teams, const OneLineData& data) {
	if (!data.score_info_available)
		return 1;
	Match dummy_match;
	bool home_team_found = false;
	bool away_team_found = false;
	for (auto& team : teams) {
		//check if team created before
		if (!home_team_found && !data.home_name.compare(team.name)) {
			home_team_found = true;
			evaluateFirstHalf(team, dummy_match, data.home_fh_score, data.away_fh_score, true);
			evaluateSecondHalf(team, dummy_match, data.home_final_score, data.away_final_score, true);
			if (data.corner_info_availabe) {
				processFirstHalfCorners(team, dummy_match, data.home_fh_corners, data.away_fh_corners, true);
				processSecondHalfCorners(team, dummy_match, data.home_sh_corners, data.away_sh_corners, true);
			}

		}
		if (!away_team_found && !data.away_name.compare(team.name)) {
			away_team_found = true;
			evaluateFirstHalf(team, dummy_match, data.home_fh_score, data.away_fh_score, false);
			evaluateSecondHalf(team, dummy_match, data.home_final_score, data.away_final_score, false);
			if (data.corner_info_availabe) {
				processFirstHalfCorners(team, dummy_match, data.home_fh_corners, data.away_fh_corners, false);
				processSecondHalfCorners(team, dummy_match, data.home_sh_corners, data.away_sh_corners, false);
			}
		}
	}
	// if not found, create new team, add stats, push to vector of teams
	if (!home_team_found) {
		Team home_team(data.home_name);
		evaluateFirstHalf(home_team, dummy_match, data.home_fh_score, data.away_fh_score, true);
		evaluateSecondHalf(home_team, dummy_match, data.home_final_score, data.away_final_score, true);
		if (data.corner_info_availabe) {
			processFirstHalfCorners(home_team, dummy_match, data.home_fh_corners, data.away_fh_corners, true);
			processSecondHalfCorners(home_team, dummy_match, data.home_sh_corners, data.away_sh_corners, true);
		}
		teams.push_back(home_team);
	}
	if (!away_team_found) {
		Team away_team(data.away_name);
		evaluateFirstHalf(away_team, dummy_match, data.home_fh_score, data.away_fh_score, false);
		evaluateSecondHalf(away_team, dummy_match, data.home_final_score, data.away_final_score, false);
		if (data.corner_info_availabe) {
			processFirstHalfCorners(away_team, dummy_match, data.home_fh_corners, data.away_fh_corners, false);
			processSecondHalfCorners(away_team, dummy_match, data.home_sh_corners, data.away_sh_corners, false);
		}
		teams.push_back(away_team);
	}
	return 0;
}


