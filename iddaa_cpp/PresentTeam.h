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
void presentMatchHistory(Team&);
void presentTeamInfo(const Team&);
void _presentWinsAndLosses(const Team&);
void _presentGoals(const Team&);
void _presentCorners(const Team&);
void printTeamsPerLeague(const std::vector<std::filesystem::path>&);