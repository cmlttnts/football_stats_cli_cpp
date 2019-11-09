#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Team.h"
#include "Match.h"
#include <filesystem>
#include "Interface.h"

// team name and the match text file paths needed
TEAM_ANALYSIS_OPTIONS presentTeam(const std::string&, const std::vector<std::filesystem::path>&);
void presentBestTeam(const std::vector<std::filesystem::path>& file_paths, BEST_TEAM_OPTIONS option);
std::vector<Team> rankTeamsByBestOption(std::vector<Team>& teams, BEST_TEAM_OPTIONS option);
void presentRankedTeams(std::vector<Team>& ranked_teams, BEST_TEAM_OPTIONS option);
void presentMatchHistory(Team&);
void presentTeamInfo(const Team&);
void _presentWinsAndLosses(const Team&);
void _presentGoals(const Team&);
void _presentCorners(const Team&);
void printTeamsPerLeague(const std::vector<std::filesystem::path>&);