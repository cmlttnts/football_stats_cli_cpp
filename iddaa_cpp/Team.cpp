#include "Team.h"

Team::Team() {
	name = "default";
}

Team::Team(std::string a_name) {
	name = a_name;
}

std::string Team::getName() {
	return name;
}