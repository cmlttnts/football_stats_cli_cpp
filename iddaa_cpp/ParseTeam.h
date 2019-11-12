#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"
#include "Team.h"
#include <vector>
#include "OneLineInfo.h"
int searchTeamMatch(const std::filesystem::path&, Team&);
std::vector<Team> getAllTeamsStats(const std::vector<std::filesystem::path>& file_paths);

void parseFileForStats(const std::filesystem::path& the_path, std::vector<Team>& teams);
int parseLineForStats(std::vector<Team>&, const OneLineData&);
void evaluateFirstHalf(Team&, Match&, unsigned int, unsigned int, bool);
void evaluateSecondHalf(Team&, Match&, unsigned int, unsigned int, bool);
void processFirstHalfCorners(Team&, Match&, unsigned int, unsigned int, bool);
void processSecondHalfCorners(Team&, Match&, unsigned int, unsigned int, bool);