#include "PresentTeam.h"
#include "boost/format.hpp"
#include <windows.h>
#include "ParseTeam.h"
#include "MyAlgortihms.h"
#include <algorithm>

#define topHowMany 15
#define BET_MATCH_DELAY 500
#define INIT_DELAY 500
#define BET_PRES_DELAY 500
#define BET_CHAPTER_DELAY 500
#define WHITE_COL 7
#define BLUE_COL 9
#define CYAN_COL 11
#define RED_COL 12
#define YELLOW_COL 14
#define setTitleColor() SetConsoleTextAttribute(h_cons, CYAN_COL)
#define setInfoColor() SetConsoleTextAttribute(h_cons, WHITE_COL)
#define setCommentColor() SetConsoleTextAttribute(h_cons, YELLOW_COL)
using namespace std;
using boost::format;


TEAM_ANALYSIS_OPTIONS presentTeam(const std::string& team_name, const std::vector<std::filesystem::path>& file_names ) {
	if (!team_name.compare("q"))
		return TEAM_ANALYSIS_OPTIONS::EXIT;
	else if (!team_name.compare("g"))
		return TEAM_ANALYSIS_OPTIONS::GO_BACK;
	// Team and team found boolean pair, if found present team
	std::pair<Team, bool> team_info = searchFilesForTeam(file_names, team_name, LEAGUE_SEARCH_OPTION::BOTH);
	if(!team_info.second){
		presentMatchHistory(team_info.first);
		presentTeamInfo(team_info.first);
	}
	return TEAM_ANALYSIS_OPTIONS::TEAM_PICKED;
}

void presentBestTeams(std::vector<Team>& teams, BEST_TEAM_OPTIONS option) {
	presentRankedTeams(teams, option);
}

void presentComparison(std::tuple<std::string, std::string, COMPARE_TWO_OPTIONS, LEAGUE_SEARCH_OPTION> two_teams, const std::vector<std::filesystem::path>& file_names) {

	std::pair<Team, bool> team1_info = searchFilesForTeam(file_names, std::get<0>(two_teams), std::get<3>(two_teams));
	std::pair<Team, bool> team2_info = searchFilesForTeam(file_names, std::get<1>(two_teams), std::get<3>(two_teams));

	//if both teams found, compare them
	if (!team1_info.second && !team2_info.second)
		//cout << "Burada Karsilastirma Olacak!\n";
		presentTwoTeamsSideBySide(team1_info.first, team2_info.first);
	else
		std::cout << "En az bir takim ismini yanlis girdiniz!!!\n";
}	

void presentTwoTeamsSideBySide(const Team& team1, const Team& team2) {
	system("cls");
	HANDLE h_cons;
	h_cons = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << format("%50s|\n") % "";
	cout << format("%=50s|%=50s\n") % team1.name % team2.name;

	// Match win draw loss number
	setTitleColor();
	cout << format("%=100s\n") % "MAC SONUCLARI (Galip/Berabere/Maglup)";
	string s1 = str(format("(%-2u / %-2u / %-2u) Toplam Mac: %-2u") % team1.num_of_wins%team1.num_of_draws%team1.num_of_losses%team1.num_of_matches);
	string s2 = str(format("(%-2u / %-2u / %-2u) Toplam Mac: %-2u") % team2.num_of_wins % team2.num_of_draws % team2.num_of_losses % team2.num_of_matches);
	setCommentColor();
	cout << format("%50s|\n") % "";
	cout << format("%=50s|%=50s\n") % s1 % s2;
	cout << format("%50s|\n") % "";

	//HOME VS AWAY PERFORMANCE
	setTitleColor();
	cout << format("%=100s\n") % "EV / DEPLASMAN PERFORMANSI (Galip/Berabere/Maglup)";
	s1 = str(format("Evinde (%-2u / %-2u / %-2u) Toplam Mac: %-2u") % team1.num_of_home_wins % team1.num_of_home_draws % team1.num_of_home_losses % team1.num_of_home_matches);
	s2 = str(format("Deplasmanda (%-2u / %-2u / %-2u) Toplam Mac: %-2u") % team2.num_of_away_wins % team2.num_of_away_draws % team2.num_of_away_losses % team2.num_of_away_matches);
	setCommentColor();
	cout << format("%50s|\n") % "";
	cout << format("%=50s|%=50s\n") % s1 % s2;
	cout << format("%50s|\n") % "";

	setTitleColor();
	cout << format("%=100s\n") % "ILK YARI PERFORMANSI (Galip/Berabere/Maglup)";
	s1 = str(format("(%-2u / %-2u / %-2u) Toplam Mac: %-2u") % team1.num_of_first_half_wins % (team1.num_of_matches - team1.num_of_first_half_wins - team1.num_of_first_half_losses) % team1.num_of_first_half_losses % team1.num_of_matches);
	s2 = str(format("(%-2u / %-2u / %-2u) Toplam Mac: %-2u") % team2.num_of_first_half_wins % (team2.num_of_matches - team2.num_of_first_half_wins - team2.num_of_first_half_losses) % team2.num_of_first_half_losses % team2.num_of_matches);
	setCommentColor();
	cout << format("%50s|\n") % "";
	cout << format("%=50s|%=50s\n") % s1 % s2;
	cout << format("%50s|\n") % "";

	// SECOND HALF COMPARISONS
	setTitleColor();
	cout << format("%=100s\n") % "IKINCI YARI PERFORMANSI (Galip/Berabere/Maglup)";
	s1 = str(format("(%-2u / %-2u / %-2u) Toplam Mac: %-2u") % team1.num_of_second_half_wins % (team1.num_of_matches - team1.num_of_second_half_wins - team1.num_of_second_half_losses) % team1.num_of_second_half_losses % team1.num_of_matches);
	s2 = str(format("(%-2u / %-2u / %-2u) Toplam Mac: %-2u") % team2.num_of_second_half_wins % (team2.num_of_matches - team2.num_of_second_half_wins - team2.num_of_second_half_losses) % team2.num_of_second_half_losses % team2.num_of_matches);
	setCommentColor();
	cout << format("%50s|\n") % "";
	cout << format("%=50s|%=50s\n") % s1 % s2;
	cout << format("%50s|\n") % "";

	// GOALS // TODO: ADD FIRST HALF GOALS ETC
	setTitleColor();
	cout << format("%=100s\n") % "ATILAN YIYILEN GOL ISTATISTIKLERI";
	float avrg1 = (team1.num_of_goals+team1.num_of_goals_rec) / float(team1.num_of_matches);
	float avrg2 = (team2.num_of_goals + team2.num_of_goals_rec) / float(team2.num_of_matches);
	s1 = str(format("Maclarinda Ortalama / Mac Sayisi : %-3.3f / %-3u") % avrg1 % team1.num_of_matches);
	s2 = str(format("Maclarinda Ortalama / Mac Sayisi : %-3.3f / %-3u") % avrg2 % team2.num_of_matches);
	setCommentColor();
	cout << format("%50s|\n") % "";
	cout << format("%=50s|%=50s\n") % s1 % s2;

	avrg1 = team1.num_of_goals / float(team1.num_of_matches);
	avrg2 = team2.num_of_goals / float(team2.num_of_matches);
	s1 = str(format("Attiklari Ortalama / Mac Sayisi : %-3.3f / %-3u") % avrg1 % team1.num_of_matches);
	s2 = str(format("Attiklari Ortalama / Mac Sayisi : %-3.3f / %-3u") % avrg2 % team2.num_of_matches);
	setCommentColor();
	cout << format("%=50s|%=50s\n") % s1 % s2;

	avrg1 = team1.num_of_home_goals / float(team1.num_of_home_matches);
	avrg2 = team2.num_of_away_goals / float(team2.num_of_away_matches);
	s1 = str(format("Evde Attigi Ortalama / Mac Sayisi : %-3.3f / %-3u") % avrg1 % team1.num_of_home_matches);
	s2 = str(format("Depte Attigi Ortalama / Mac Sayisi : %-3.3f / %-3u") % avrg2 % team2.num_of_away_matches);
	setCommentColor();
	cout << format("%=50s|%=50s\n") % s1 % s2;

	avrg1 = team1.num_of_home_goals_rec / float(team1.num_of_home_matches);
	avrg2 = team2.num_of_away_goals_rec / float(team2.num_of_away_matches);
	s1 = str(format("Evde Yedigi Ortalama / Mac Sayisi : %-3.3f / %-3u") % avrg1 % team1.num_of_home_matches);
	s2 = str(format("Depte Yedigi Ortalama / Mac Sayisi : %-3.3f / %-3u") % avrg2 % team2.num_of_away_matches);
	setCommentColor();
	cout << format("%=50s|%=50s\n") % s1 % s2;
	cout << format("%50s|\n") % "";

	// UNDER OVER STATS
	setTitleColor();
	cout << format("%=100s\n") % "ALT UST ISTATISTIKLERI";
	s1 = str(format("2.5 ALT / UST: %2u / %2u") % (team1.num_of_matches - team1.num_of_above_2_5_matches) % team1.num_of_above_2_5_matches);
	s2 = str(format("2.5 ALT / UST: %2u / %2u") % (team2.num_of_matches - team2.num_of_above_2_5_matches) % team2.num_of_above_2_5_matches);
	setCommentColor();
	cout << format("%50s|\n") % "";
	cout << format("%=50s|%=50s\n") % s1 % s2;

	s1 = str(format("3.5 ALT / UST: %2u / %2u") % team1.num_of_below_3_5_matches %(team1.num_of_matches - team1.num_of_below_3_5_matches));
	s2 = str(format("3.5 ALT / UST: %2u / %2u") % team2.num_of_below_3_5_matches % (team2.num_of_matches - team2.num_of_below_3_5_matches));
	setCommentColor();
	cout << format("%=50s|%=50s\n") % s1 % s2;

	s1 = str(format("1Y 1.5 ALT / UST: %2u / %2u") % (team1.num_of_matches - team1.num_of_above_1_5_half_matches) % team1.num_of_above_1_5_half_matches);
	s2 = str(format("1Y 1.5 ALT / UST: %2u / %2u") % (team2.num_of_matches - team2.num_of_above_1_5_half_matches) % team2.num_of_above_1_5_half_matches);
	setCommentColor();
	cout << format("%=50s|%=50s\n") % s1 % s2;

	s1 = str(format("1Y 0.5 ALT / UST: %2u / %2u") % team1.num_of_below_0_5_half_matches % (team1.num_of_matches - team1.num_of_below_0_5_half_matches));
	s2 = str(format("1Y 0.5 ALT / UST: %2u / %2u") % team2.num_of_below_0_5_half_matches % (team2.num_of_matches - team2.num_of_below_0_5_half_matches));
	setCommentColor();
	cout << format("%=50s|%=50s\n") % s1 % s2;
	cout << format("%50s|\n") % "";

	// CORNER STATS
	setTitleColor();
	cout << format("%=100s\n") % "KORNER ISTATISTIKLERI";
	avrg1 = (team1.num_of_corners + team1.num_of_corners_rec) / float(team1.num_of_corner_info_match);
	avrg2 = (team2.num_of_corners + team2.num_of_corners_rec) / float(team2.num_of_corner_info_match);
	s1 = str(format("Maclarinda Ortalama / Mac Sayisi: %3.3f / %2u") % avrg1 % team1.num_of_corner_info_match);
	s2 = str(format("Maclarinda Ortalama / Mac Sayisi: %3.3f / %2u") % avrg2 % team2.num_of_corner_info_match);
	setCommentColor();
	cout << format("%50s|\n") % "";
	cout << format("%=50s|%=50s\n") % s1 % s2;

	avrg1 = team1.num_of_corners / float(team1.num_of_corner_info_match);
	avrg2 = team2.num_of_corners / float(team2.num_of_corner_info_match);
	s1 = str(format("Attiklari Ortalama / Mac Sayisi: %3.3f / %2u") % avrg1 % team1.num_of_corner_info_match);
	s2 = str(format("Attiklari Ortalama / Mac Sayisi: %3.3f / %2u") % avrg2 % team2.num_of_corner_info_match);
	setCommentColor();
	cout << format("%=50s|%=50s\n") % s1 % s2;
	cout << format("%50s|\n") % "";

	// END
	setInfoColor();
	// First Half Second half win loss numbers
	// Home results, away results
	// Average goals scored and recieved
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
	cout << format("%-12s %2u   %s %5.2f\n") % "Yedikleri :" % team.num_of_goals_rec % "Mac basina ort:" % (team.num_of_goals_rec / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Toplam :" % (team.num_of_goals + team.num_of_goals_rec) % "Mac basina ort:" % ((team.num_of_goals + team.num_of_goals_rec) / float(team.num_of_matches));
	cout << "Gol yemedikleri mac sayisi: " << team.num_of_clean_sheets << "\n";
	cout << "KG VAR biten mac sayisi: " << team.num_of_kg_var_matches << "\n";
	Sleep(BET_CHAPTER_DELAY);
	// first half goals
	setTitleColor();
	cout << format("%30s %s") % "" % "ILK YARI GOL ISTATISTIKLERI\n";
	setInfoColor();
	cout << format("%s %2u%s") % "Toplam Mac Sayisi:" % team.num_of_matches % "\n";
	cout << format("%-12s %2u   %s %5.2f\n") % "Attiklari :" % team.num_of_first_half_goals % "Mac basina ort:" % (team.num_of_first_half_goals / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Yedikleri :" % team.num_of_first_half_goals_rec % "Mac basina ort:" % (team.num_of_first_half_goals_rec / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Toplam :" % (team.num_of_first_half_goals + team.num_of_first_half_goals_rec) % "Mac basina ort:" % ((team.num_of_first_half_goals + team.num_of_first_half_goals_rec) / float(team.num_of_matches));
	Sleep(BET_CHAPTER_DELAY);
	//second half goals
	setTitleColor();
	cout << format("%30s %s") % "" % "IKINCI YARI GOL ISTATISTIKLERI\n";
	setInfoColor();
	cout << format("%s %2u%s") % "Toplam Mac Sayisi:" % team.num_of_matches % "\n";
	cout << format("%-12s %2u   %s %5.2f\n") % "Attiklari :" % team.num_of_second_half_goals % "Mac basina ort:" % (team.num_of_second_half_goals / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Yedikleri :" % team.num_of_second_half_goals_rec % "Mac basina ort:" % (team.num_of_second_half_goals_rec / float(team.num_of_matches));
	cout << format("%-12s %2u   %s %5.2f\n") % "Toplam :" % (team.num_of_second_half_goals + team.num_of_second_half_goals_rec) % "Mac basina ort:" % ((team.num_of_second_half_goals + team.num_of_second_half_goals_rec) / float(team.num_of_matches));
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

	//size_t topHowMany = 10;
	system("cls");
	switch (option)
	{
	case BEST_TEAM_OPTIONS::BEST_RESULTS:
		// FINAL WINS
		std::sort(teams.begin(), teams.end(), sortByWins);
		presentRankTitle("EN COK KAZANANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			presentRankN(i + 1, teams[i].name, "Kazandigi / Toplam", teams[i].num_of_wins, teams[i].num_of_matches);
		}
		cout << "\n";
		// FIRST HALF WINS
		std::sort(teams.begin(), teams.end(), sortByFHWins);
		presentRankTitle("1Y EN COK KAZANANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			presentRankN(i + 1, teams[i].name, "Kazandigi / Toplam", teams[i].num_of_first_half_wins, teams[i].num_of_matches);
		}
		cout << "\n";
		// SECOND HALF WINS
		std::sort(teams.begin(), teams.end(), sortBySHWins);
		presentRankTitle("2Y EN COK KAZANANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			presentRankN(i + 1, teams[i].name, "Kazandigi / Toplam", teams[i].num_of_second_half_wins, teams[i].num_of_matches);
		}
		cout << "\n";

		break;
	case BEST_TEAM_OPTIONS::WORST_RESULTS:
		std::sort(teams.begin(), teams.end(), sortByLosses);
		presentRankTitle("EN COK KAYBEDENLER TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			presentRankN(i + 1, teams[i].name, "Kaybettigi / Toplam", teams[i].num_of_losses, teams[i].num_of_matches);
		}
		cout << "\n";
		std::sort(teams.begin(), teams.end(), sortByFHLosses);
		presentRankTitle("1Y EN COK KAYBEDENLER TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			presentRankN(i + 1, teams[i].name, "Kaybettigi / Toplam", teams[i].num_of_first_half_losses, teams[i].num_of_matches);
		}
		cout << "\n";
		//second half losses
		std::sort(teams.begin(), teams.end(), sortBySHLosses);
		presentRankTitle("2Y EN COK KAYBEDENLER TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			presentRankN(i + 1, teams[i].name, "Kaybettigi / Toplam", teams[i].num_of_second_half_losses, teams[i].num_of_matches);
		}
		cout << "\n";
		break;
	case BEST_TEAM_OPTIONS::MOST_GOALS_SCORED:
		std::sort(teams.begin(), teams.end(), sortByMostGoalsScored);
		presentRankTitle("EN COK GOL ATANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			float avrg = teams[i].num_of_goals / float(teams[i].num_of_matches);
			presentRankN(i + 1, teams[i].name, "Ortalama / Mac Sayisi", avrg, teams[i].num_of_matches);
		}
		cout << "\n";

		std::sort(teams.begin(), teams.end(), sortByMostGoalsFH);
		presentRankTitle("1Y EN COK GOL ATANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			float avrg = teams[i].num_of_first_half_goals / float(teams[i].num_of_matches);
			presentRankN(i + 1, teams[i].name, "Ortalama / Mac Sayisi", avrg, teams[i].num_of_matches);
		}
		cout << "\n";
		std::sort(teams.begin(), teams.end(), sortByMostGoalsSH);
		presentRankTitle("2Y EN COK GOL ATANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			float avrg = teams[i].num_of_second_half_goals / float(teams[i].num_of_matches);
			presentRankN(i + 1, teams[i].name, "Ortalama / Mac Sayisi", avrg, teams[i].num_of_matches);
		}
		cout << "\n";

		break;
	case BEST_TEAM_OPTIONS::LEAST_GOALS_SCORED:
		std::sort(teams.begin(), teams.end(), sortByMostGoalsScored);
		std::reverse(teams.begin(), teams.end());
		presentRankTitle("EN AZ GOL ATANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			float avrg = teams[i].num_of_goals / float(teams[i].num_of_matches);
			presentRankN(i + 1, teams[i].name, "Ortalama / Mac Sayisi", avrg, teams[i].num_of_matches);
		}
		cout << "\n";
		break;
	case BEST_TEAM_OPTIONS::MOST_GOALS_RECEIVED:
		std::sort(teams.begin(), teams.end(), sortByMostGoalsRec);
		presentRankTitle("EN COK GOL YIYENLER TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			float avrg = teams[i].num_of_goals_rec / float(teams[i].num_of_matches);
			presentRankN(i + 1, teams[i].name, "Ortalama / Mac Sayisi", avrg, teams[i].num_of_matches);
		}
		cout << "\n";
		break;
	case BEST_TEAM_OPTIONS::LEAST_GOALS_RECEIVED:
		std::sort(teams.begin(), teams.end(), sortByMostGoalsRec);
		std::reverse(teams.begin(), teams.end());
		presentRankTitle("EN AZ GOL YIYENLER TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			float avrg = teams[i].num_of_goals_rec / float(teams[i].num_of_matches);
			presentRankN(i + 1, teams[i].name, "Ortalama / Mac Sayisi", avrg, teams[i].num_of_matches);
		}
		cout << "\n";
		break;
	case BEST_TEAM_OPTIONS::MOST_GOALS_IN_MATCHES:
		std::sort(teams.begin(), teams.end(), sortByMostGoalsInMatch);
		presentRankTitle("MACLARINDA EN COK GOL OLANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			float total = float(teams[i].num_of_goals + teams[i].num_of_goals_rec) / float(teams[i].num_of_matches);
			presentRankN(i + 1, teams[i].name, "Ortalama / 2.5 ust bitenler /Mac Sayisi", total, teams[i].num_of_above_2_5_matches, teams[i].num_of_matches);
		}
		cout << "\n";
		break;
	case BEST_TEAM_OPTIONS::LEAST_GOALS_IN_MATCHES:
		std::sort(teams.begin(), teams.end(), sortByMostGoalsInMatch);
		std::reverse(teams.begin(), teams.end());
		presentRankTitle("MACLARINDA EN AZ GOL OLANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			float total = (teams[i].num_of_goals + teams[i].num_of_goals_rec) / float(teams[i].num_of_matches);
			presentRankN(i + 1, teams[i].name, "Ortalama / Mac Sayisi", total, teams[i].num_of_matches);
		}
		cout << "\n";
		break;
	case BEST_TEAM_OPTIONS::COMEBACKS:
		std::sort(teams.begin(), teams.end(), sortByComebacksAndGobacks);
		presentRankTitle("MACLARINDA EN COK GERI DONUS OLANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			unsigned int total = teams[i].num_of_comebacks + teams[i].num_of_gobacks;
			presentRankN(i + 1, teams[i].name, "Surpriz Mac / Toplam Mac", total, teams[i].num_of_matches);
		}
		cout << "\n";
		std::sort(teams.begin(), teams.end(), sortByComebacks);
		presentRankTitle("MACLARINDA EN COK GERI DONUS YAPANLAR TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			presentRankN(i + 1, teams[i].name, "Surpriz Mac / Toplam Mac", teams[i].num_of_comebacks, teams[i].num_of_matches);
		}
		cout << "\n";
		std::sort(teams.begin(), teams.end(), sortByGobacks);
		presentRankTitle("MACLARINDA EN COK RAKIBIN GERI DONUS YAPTIGI TOP", topHowMany);
		for (size_t i = 0; i < topHowMany; i++) {
			presentRankN(i + 1, teams[i].name, "Surpriz Mac / Toplam Mac", teams[i].num_of_gobacks, teams[i].num_of_matches);
		}
		cout << "\n";
		break;
	case BEST_TEAM_OPTIONS::CORNERS:
		std::sort(teams.begin(), teams.end(), sortByTotalCorners);
		presentRankTitle("MACLARINDA EN COK KORNER OLANLAR TOP", topHowMany);
		{
			float avrg_corner{ 0.f };
			for (size_t i = 0; i < topHowMany; i++) {
				avrg_corner = float((teams[i].num_of_corners + teams[i].num_of_corners_rec)) / teams[i].num_of_corner_info_match;
				presentRankN(i + 1, teams[i].name, "Mac basi / Mac sayisi", avrg_corner, teams[i].num_of_corner_info_match);
			}
		}
		cout << "\n";
		std::reverse(teams.begin(), teams.end());
		presentRankTitle("MACLARINDA EN AZ KORNER OLANLAR TOP", topHowMany);
		{
			float avrg_corner{ 0.f };
			for (size_t i = 0; i < topHowMany; i++) {
				avrg_corner = float((teams[i].num_of_corners + teams[i].num_of_corners_rec)) / teams[i].num_of_corner_info_match;
				presentRankN(i + 1, teams[i].name, "Mac basi / Mac sayisi", avrg_corner, teams[i].num_of_corner_info_match);
			}
		}
		cout << "\n";
		break;
	case BEST_TEAM_OPTIONS::GO_BACK:
		break;
	case BEST_TEAM_OPTIONS::EXIT:
		break;
	default:
		break;
	}

}

void presentRankN(size_t rank,
				std::string name, std::string text,
				float value, unsigned int total) {
	cout << format("%3u-) %-16s (%s) = (%.3f / %u)\n") % rank % name % text % value % total;
}

void presentRankN(size_t rank,
	std::string name, std::string text,
	unsigned int value, unsigned int total) {
	cout << format("%3u-) %-16s (%s) = (%u / %u)\n") % rank % name % text % value % total;
}

void presentRankN(size_t rank,
	std::string name, std::string text,
	float value1, unsigned int value2, unsigned int total) {
	cout << format("%3u-) %-16s (%s) = (%.3f / %u / %u)\n") % rank % name % text % value1 % value2 % total;
}

void presentRankTitle(std::string title, size_t topX) {
	HANDLE h_cons;
	h_cons = GetStdHandle(STD_OUTPUT_HANDLE);
	setTitleColor();
	cout << format("%30s %s %u\n") % "" % title % topX;
	setInfoColor();
}