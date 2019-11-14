#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include "Team.h"
#include "Match.h"
#include <filesystem>
#include "Interface.h"

// ONE TEAM PRESENTATION
TEAM_ANALYSIS_OPTIONS presentTeam(const std::string&, const std::vector<std::filesystem::path>&);
void presentMatchHistory(Team&);
void presentTeamInfo(const Team&);
void _presentWinsAndLosses(const Team&);
void _presentGoals(const Team&);
void _presentCorners(const Team&);

// BEST TEAM PRESENTATION
void presentBestTeams(std::vector<Team>&, BEST_TEAM_OPTIONS);
void presentRankedTeams(std::vector<Team>&, BEST_TEAM_OPTIONS);
void presentRankN(size_t ,std::string, std::string, float, unsigned int);
void presentRankN(size_t, std::string, std::string, unsigned int, unsigned int);
void presentRankN(size_t, std::string, std::string, float, unsigned int, unsigned int);
void presentRankTitle(std::string, size_t);

// COMPARISON OF TWO TEAMS
void presentComparison(std::tuple<std::string, std::string, COMPARE_TWO_OPTIONS, LEAGUE_SEARCH_OPTION>, const std::vector<std::filesystem::path>&);
void presentTwoTeamsSideBySide(const Team&, const Team&);

void printTeamsPerLeague(const std::vector<std::filesystem::path>&);