#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"
#include "Team.h"
int simpleParse(const std::filesystem::path&, Team&);
void evaluateFirstHalf(Team&, Match&, unsigned int, unsigned int, bool);
void evaluateSecondHalf(Team&, Match&, unsigned int, unsigned int, bool);
void processFirstHalfCorners(Team&, Match&, unsigned int, unsigned int, bool);
void processSecondHalfCorners(Team&, Match&, unsigned int, unsigned int, bool);