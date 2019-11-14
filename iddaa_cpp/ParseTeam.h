#pragma once
#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include "Files.h"
#include "Team.h"
#include <vector>
#include "OneLineInfo.h"
#include "Interface.h"
std::pair<Team, bool> searchFilesForTeam(const std::vector<std::filesystem::path>& , const std::string&, LEAGUE_SEARCH_OPTION);
int searchTeamMatch(const std::filesystem::path&, Team&);
std::vector<Team> getAllTeamsStats(const std::vector<std::filesystem::path>&);

void parseFileForStats(const std::filesystem::path&, std::vector<Team>&);
int parseLineForStats(std::vector<Team>&, const OneLineData&);
void evaluateFirstHalf(Team&, Match&, unsigned int, unsigned int, bool);
void evaluateSecondHalf(Team&, Match&, unsigned int, unsigned int, bool);
void processFirstHalfCorners(Team&, Match&, unsigned int, unsigned int, bool);
void processSecondHalfCorners(Team&, Match&, unsigned int, unsigned int, bool);