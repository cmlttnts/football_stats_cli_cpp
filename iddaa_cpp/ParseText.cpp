#include "ParseText.h"

using namespace std;

void simpleParse(std::filesystem::path the_path) {
	ifstream file(the_path);
	string line;
	if (file.is_open()) {
		while ( getline(file, line)) {
			cout << line << "\n";
		}
		file.close();
	}
	else {
		cout << "File did not open!\n";
	}
}
void parseForTeam() {
}

void parseForLeague() {

}