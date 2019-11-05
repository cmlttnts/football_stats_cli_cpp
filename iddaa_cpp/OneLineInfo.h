#pragma once
#include <string>

//Full data availabe for one match in the text files
struct OneLineData {
	std::string home_name = "";
	std::string away_name = "";
	bool score_info_available = false;
	unsigned int home_fh_score = 0;
	unsigned int away_fh_score = 0;
	unsigned int home_final_score = 0;
	unsigned int away_final_score = 0;
	bool corner_info_availabe = false;
	unsigned int home_fh_corners = 0;
	unsigned int away_fh_corners = 0;
	unsigned int home_sh_corners = 0;
	unsigned int away_sh_corners = 0;

};
OneLineData getDataFromLine(const std::string&);
void printOneLineData(const OneLineData&);