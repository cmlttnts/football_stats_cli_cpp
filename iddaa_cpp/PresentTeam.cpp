#include "PresentTeam.h"
#include "boost/format.hpp"
#include <windows.h>
#include "ParseTeam.h"
#include "MyAlgortihms.h"
#include <algorithm>

#define BET_MATCH_DELAY 500
#define INIT_DELAY 2000
#define BET_PRES_DELAY 1500
#define BET_CHAPTER_DELAY 1000
using namespace std;
using boost::format;


TEAM_ANALYSIS_OPTIONS presentTeam(const std::string& team_name, const std::vector<std::filesystem::path>& file_names ) {
	if (!team_name.compare("q"))
		return TEAM_ANALYSIS_OPTIONS::EXIT;
	else if (!team_name.compare("g"))
		return TEAM_ANALYSIS_OPTIONS::GO_BACK;
	Team team(team_name);
	bool failure = true;
	// Read files to modify team's properties
	for (const auto& name : file_names) {
		//if we find at least 1 match we say it is success
		failure = searchTeamMatch(name, team) && failure;
		//std::cout << name << "\n";
	}
	// Preset team's info
	if (failure) {
		std::cout << "No match found" << "\n";
	}
	else {
		presentMatchHistory(team);
		presentTeamInfo(team);
	}
	return TEAM_ANALYSIS_OPTIONS::TEAM_PICKED;
}

void presentBestTeams(const std::vector<std::filesystem::path>& file_paths, BEST_TEAM_OPTIONS option) {
	//collect all teams
	std::vector<Team> teams;
	for (const auto& file_path : file_paths) {
		//cout << file_path << "\n";
		gatherAllTeamInfos(file_path, teams);
	}
		presentRankedTeams(teams, option);
}

void presentMatchHistory(Team& team) {
	int n = 1;
	std::sort(team.matches.begin(), team.matches.end(), sortMatchesByDate);
	for (auto& match : team.matches) {
		std::cout << n << "-) ";
		match.prettyPresent();
		//give some time to read
		Sleep(BET_MATCH_DELAY);
		n++;
	}
}

void presentTeamInfo(const Team& team) {
	Sleep(INIT_DELAY);
	_presentWinsAndLosses(team);
	Sleep(BET_PRES_DELAY);
	_presentGoals(team);
	Sleep(BET_PRES_DELAY);
	_presentCorners(team);
}

#define WHITE_COL 7
#define CYAN_COL 11
#define READ_COL 12
#define BLUE_COL 9

#define setTitleColor() SetConsoleTextAttribute(h_cons, CYAN_COL)
#define setInfoColor() SetConsoleTextAttribute(h_cons, WHITE_COL)

void _presentWinsAndLosses(const Team& team) {
	HANDLE h_cons;
	h_cons = GetStdHandle(STD_OUTPUT_HANDLE);

	setTitleColor();
	cout << format("%30s %s") % "" % "MAC SONUCU ISTATISTIKLERI\n";
	setInfoColor();
	//final result info
	cout << format("%s %2u%s") % "Toplam Mac Sayisi:" % team.num_of_matches % "\n";
	cout << format("(W: %2u D: %2u L: %2u)") % team.num_of_wins % team.num_of_draws % team.num_of_losses;
	cout << format(" Yuzdelik: (W: %s%5.2f") % "%" % (team.num_of_wins * 100 / float(team.num_of_matches));
	cout << format(" D: %s%5.2f") % "%" % (team.num_of_draws * 100 / float(team.num_of_matches));
	cout << format(" L: %s%5.2f)\n") % "%" % (team.num_of_losses * 100 / float(team.num_of_matches));
	Sleep(BET_CHAPTER_DELAY);
	//first half info
	setTitleColor();
	cout << format("%30s %s") % "" % "ILK YARI ISTATISTIKLERI\n";
	setInfoColor();
	cout << format("%s %2u%s") % "Toplam Mac Sayisi:" % team.num_of_matches % "\n";
	cout << format("(W: %2u D: %2u L: %2u)") % team.num_of_first_half_wins % (team.num_of_matches - team.num_of_first_half_wins - team.num_of_first_half_losses) % team.num_of_first_half_losses;
	cout << format(" Yuzdelik: (W: %s%5.2f") % "%" % (team.num_of_first_half_wins * 100 / float(team.num_of_matches));
	cout << format(" D: %s%5.2f") % "%" % ((team.num_of_matches - team.num_of_first_half_wins - team.num_of_first_half_losses) * 100 / float(team.num_of_matches));
	cout << format(" L: %s%5.2f)\n") % "%" % (team.num_of_first_half_losses * 100 / float(team.num_of_matches));
	Sleep(BET_CHAPTER_DELAY);
	//second half info
	setTitleColor();
	cout << format("%30s %s") % "" % "IKINCI YARI ISTATISTIKLERI\n";
	setInfoColor();
	cout << format("%s %2u%s") % "Toplam Mac Sayisi:" % team.num_of_matches % "\n";
	cout << format("(W: %2u D: %2u L: %2u)") % team.num_of_second_half_wins % (team.num_of_matches - team.num_of_second_half_wins - team.num_of_second_half_losses) % team.num_of_second_half_losses;
	cout << format(" Yuzdelik: (W: %s%5.2f") % "%" % (team.num_of_second_half_wins * 100 / float(team.num_of_matches));
	cout << format(" D: %s%5.2f") % "%" % ((team.num_of_matches - team.num_of_second_half_wins - team.num_of_second_half_losses) * 100 / float(team.num_of_matches));
	cout << format(" L: %s%5.2f)\n") % "%" % (team.num_of_second_half_losses * 100 / float(team.num_of_matches));
}
// Goals info
void _presentGoals(const Team& team) {
	HANDLE h_cons;
	h_cons = GetStdHandle(STD_OUTPUT_HANDLE);
	//final goals
	setTitleColor();
	cout << format("%30s %s") % "" % "MAC SONU GOL ISTATISTIKLERI\n";
	setInfoColor();
	cout << format("%s %2u%s") % "Toplam Mac Sayisi:" % team.num_of_matches % "\n";
	cout << format("%-12s %2u   %s %5.2f\n") % "Attiklari :" % team.num_of_goals % "Mac basina ort:" % (team.num_of_goals / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Yedikleri :" % team.num_of_rec_goals % "Mac basina ort:" % (team.num_of_rec_goals / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Toplam :" % (team.num_of_goals + team.num_of_rec_goals) % "Mac basina ort:" % ((team.num_of_goals + team.num_of_rec_goals) / float(team.num_of_matches));
	cout << "Gol yemedikleri mac sayisi: " << team.num_of_clean_sheets << "\n";
	cout << "KG VAR biten mac sayisi: " << team.num_of_kg_var_matches << "\n";
	Sleep(BET_CHAPTER_DELAY);
	// first half goals
	setTitleColor();
	cout << format("%30s %s") % "" % "ILK YARI GOL ISTATISTIKLERI\n";
	setInfoColor();
	cout << format("%s %2u%s") % "Toplam Mac Sayisi:" % team.num_of_matches % "\n";
	cout << format("%-12s %2u   %s %5.2f\n") % "Attiklari :" % team.num_of_first_half_goals % "Mac basina ort:" % (team.num_of_first_half_goals / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Yedikleri :" % team.num_of_first_half_rec_goals % "Mac basina ort:" % (team.num_of_first_half_rec_goals / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Toplam :" % (team.num_of_first_half_goals + team.num_of_first_half_rec_goals) % "Mac basina ort:" % ((team.num_of_first_half_goals + team.num_of_first_half_rec_goals) / float(team.num_of_matches));
	Sleep(BET_CHAPTER_DELAY);
	//second half goals
	setTitleColor();
	cout << format("%30s %s") % "" % "IKINCI YARI GOL ISTATISTIKLERI\n";
	setInfoColor();
	cout << format("%s %2u%s") % "Toplam Mac Sayisi:" % team.num_of_matches % "\n";
	cout << format("%-12s %2u   %s %5.2f\n") % "Attiklari :" % team.num_of_second_half_goals % "Mac basina ort:" % (team.num_of_second_half_goals / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Yedikleri :" % team.num_of_second_half_rec_goals % "Mac basina ort:" % (team.num_of_second_half_rec_goals / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Toplam :" % (team.num_of_second_half_goals + team.num_of_second_half_rec_goals) % "Mac basina ort:" % ((team.num_of_second_half_goals + team.num_of_second_half_rec_goals) / float(team.num_of_matches));
	Sleep(BET_CHAPTER_DELAY);
	// ALT UST
	setTitleColor();
	cout << format("%30s %s") % "" % "ALT UST GOL ISTATISTIKLERI\n";
	setInfoColor();
	cout << format("%-10s %3s %2u : (%s%5.2f)\n") % "2.5 UST" % ":" % team.num_of_above_2_5_matches % "%" % (team.num_of_above_2_5_matches / float(team.num_of_matches));
	cout << format("%-10s %3s %2u : (%s%5.2f)\n") % "3.5 ALT" % ":" % team.num_of_below_3_5_matches % "%" % (team.num_of_below_3_5_matches / float(team.num_of_matches));
	cout << format("%-10s %3s %2u : (%s%5.2f)\n") % "1Y 0.5 ALT" % ":" % team.num_of_below_0_5_half_matches % "%" % (team.num_of_below_0_5_half_matches / float(team.num_of_matches));
	cout << format("%-10s %3s %2u : (%s%5.2f)\n") % "1Y 1.5 UST" % ":" % team.num_of_above_1_5_half_matches % "%" % (team.num_of_above_1_5_half_matches / float(team.num_of_matches));
}
//corner info
void _presentCorners(const Team& team){
	HANDLE h_cons;
	h_cons = GetStdHandle(STD_OUTPUT_HANDLE);
	setTitleColor();
	cout << format("%30s %s") % "" % "KORNER ISTATISTIKLERI\n";
	setInfoColor();
	if (team.num_of_corner_info_match > 0) {
		cout << format("korner bilgisi olan mac sayisi: %u\n") % team.num_of_corner_info_match;
		cout << format("%-12s %-8s %5.2f  %-8s %5.2f  %-10s %5.2f)\n") % "Attiklari " % "(1y ort:" % (team.num_of_first_half_corners / float(team.num_of_corner_info_match)) % "2y ort:" % (team.num_of_second_half_corners / float(team.num_of_corner_info_match)) % "Mac sonu ort:" % (team.num_of_corners / float(team.num_of_corner_info_match));
		cout << format("%-12s %-8s %5.2f  %-8s %5.2f  %-10s %5.2f)\n") % "Yedikleri " % "(1y ort:" % (team.num_of_first_half_corners_rec / float(team.num_of_corner_info_match)) % "2y ort:" % (team.num_of_second_half_corners_rec / float(team.num_of_corner_info_match)) % "Mac sonu ort:" % (team.num_of_corners_rec / float(team.num_of_corner_info_match));
		cout << format("%-12s %-8s %5.2f  ") % "Toplam " % "(1y ort:" % ((team.num_of_first_half_corners + team.num_of_first_half_corners_rec) / float(team.num_of_corner_info_match));
		cout << format("%-8s %5.2f  ") % "2y ort:" % ((team.num_of_second_half_corners + team.num_of_second_half_corners_rec) / float(team.num_of_corner_info_match));
		cout << format("%-10s %5.2f)\n") % "Mac sonu ort:" % ((team.num_of_corners + team.num_of_corners_rec) / float(team.num_of_corner_info_match));
	}
	else {
		cout << "Korner bilgisi yok\n";
	}
}

void presentRankedTeams(std::vector<Team>& teams, BEST_TEAM_OPTIONS option) {
	HANDLE h_cons;
	h_cons = GetStdHandle(STD_OUTPUT_HANDLE);
	size_t topHowMany = 5;
	switch (option)
	{
	case BEST_TEAM_OPTIONS::BEST_RESULTS:
		std::sort(teams.begin(), teams.end(), sortByWins);
		system("cls");
		setTitleColor();
		cout << format("%30s %s\n") % "" % "EN COK KAZANANLAR TOP 5";
		setInfoColor();
		for (size_t i = 0; i < topHowMany; i++) {
			cout << format("%u-) %-12s %12s %3u/%3u\n") % (i + 1) % teams[i].name % "Kazandigi/Toplam = " % teams[i].num_of_wins % teams[i].num_of_matches;
		}
		cout << "\n\n";
		break;
	case BEST_TEAM_OPTIONS::WORST_RESULTS:
		std::sort(teams.begin(), teams.end(), sortByLosses);
		system("cls");
		setTitleColor();
		cout << format("%30s %s \n") % "" % "EN COK KAYBEDENLER TOP 5";
		setInfoColor();
		for (size_t i = 0; i < topHowMany; i++) {
			cout << format("%u-) %-12s %12s %3u/%3u\n") % (i + 1) % teams[i].name % "Kaybettigi/Toplam = " % teams[i].num_of_losses % teams[i].num_of_matches;
		}
		cout << "\n\n";

		break;
	case BEST_TEAM_OPTIONS::MOST_GOALS_SCORED:
		break;
	case BEST_TEAM_OPTIONS::LEAST_GOALS_SCORED:
		break;
	case BEST_TEAM_OPTIONS::MOST_GOALS_RECEIVED:
		break;
	case BEST_TEAM_OPTIONS::LEAST_GOALS_RECEIVED:
		break;
	case BEST_TEAM_OPTIONS::COMEBAKCS:
		break;
	case BEST_TEAM_OPTIONS::CORNERS:
		std::sort(teams.begin(), teams.end(), sortByTotalCorners);
		system("cls");
		setTitleColor();
		cout << format("%30s %s \n") % "" % "MACLARINDA ORTALAMA EN COK KORNER OLANLAR";
		setInfoColor();
		for (size_t i = 0; i < topHowMany; i++) {
			cout << format("%u-) %-12s %12s %3u/%3u\n") % (i + 1) % teams[i].name % "Ortalama (Mac Sayisi) = " % (float((teams[i].num_of_corners+teams[i].num_of_corners_rec))/teams[i].num_of_corner_info_match) % teams[i].num_of_corner_info_match;
		}
		cout << "\n\n";
		break;
	case BEST_TEAM_OPTIONS::GO_BACK:
		break;
	case BEST_TEAM_OPTIONS::EXIT:
		break;
	default:
		break;
	}

}