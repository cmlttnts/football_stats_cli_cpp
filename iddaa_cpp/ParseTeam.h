#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"
#include "Team.h"
#include <vector>
#include "OneLineInfo.h"
int searchTeamMatch(const std::filesystem::path&, Team&);
void gatherAllTeamInfos(const std::filesystem::path&, std::vector<Team>&);
int updateTeamsInfo(std::vector<Team>&, const OneLineData&);
void evaluateFirstHalf(Team&, Match&, unsigned int, unsigned int, bool);
void evaluateSecondHalf(Team&, Match&, unsigned int, unsigned int, bool);
void processFirstHalfCorners(Team&, Match&, unsigned int, unsigned int, bool);
void processSecondHalfCorners(Team&, Match&, unsigned int, unsigned int, bool);