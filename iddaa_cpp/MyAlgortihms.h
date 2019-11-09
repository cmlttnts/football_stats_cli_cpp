#pragma once
#include "Match.h"
#include "Team.h"
bool sortMatchesByDate(const Match&, const Match&);
bool sortByWins(const Team& team1, const Team& team2);
bool sortByLosses(const Team& team1, const Team& team2);
bool sortByFHWins(const Team& team1, const Team& team2);
bool sortByFHLosses(const Team& team1, const Team& team2);
bool sortBySHWins(const Team& team1, const Team& team2);
bool sortBySHLosses(const Team& team1, const Team& team2);
bool sortByTotalCorners(const Team& team1, const Team& team2);