#pragma once
#include "Match.h"
#include "Team.h"
#include <vector>
#include "Interface.h"
bool sortMatchesByDate(const Match&, const Match&);
bool sortByWins(const Team& team1, const Team& team2);
bool sortByLosses(const Team& team1, const Team& team2);
bool sortByFHWins(const Team& team1, const Team& team2);
bool sortByFHLosses(const Team& team1, const Team& team2);
bool sortBySHWins(const Team& team1, const Team& team2);
bool sortBySHLosses(const Team& team1, const Team& team2);
bool sortByTotalCorners(const Team&, const Team& team2);

bool sortByMostGoalsScored(const Team& team1, const Team& team2);
bool sortByMostGoalsRec(const Team& team1, const Team& team2);
bool sortByMostGoalsFH(const Team& team1, const Team& team2);
bool sortByMostGoalsSH(const Team& team1, const Team& team2);

bool sortByMostGoalsInMatch(const Team& team1, const Team& team2);


bool sortByComebacksAndGobacks(const Team& team1, const Team& team2);
bool sortByComebacks(const Team& team1, const Team& team2);
bool sortByGobacks(const Team& team1, const Team& team2);
void rankTeamsByOption(std::vector<Team>&, BEST_TEAM_OPTIONS);