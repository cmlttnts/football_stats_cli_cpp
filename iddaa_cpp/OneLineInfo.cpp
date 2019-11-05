#include "OneLineInfo.h"
#include <sstream>

OneLineData getDataFromLine(const std::string& line) {
	OneLineData data;
	//make line stream to retrieve words seperated by whitespaces
	std::istringstream line_stream(line);
	std::getline(line_stream, data.home_name, ' ');
	std::getline(line_stream, data.away_name, ' ');
	//rest will be converted to uints so store for temp in buffer
	std::string buffer;
	//get the words one by one if exists
	std::getline(line_stream, buffer, ' ');
	//check if score exists
	if (buffer.empty()) {
		data.score_info_available = false;
		return data;
	}
	data.home_fh_score = std::stoul(buffer);
	data.score_info_available = true;

	std::getline(line_stream, buffer, ' ');
	data.away_fh_score = std::stoul(buffer);

	std::getline(line_stream, buffer, ' ');
	data.home_final_score = std::stoul(buffer);
	
	std::getline(line_stream, buffer, ' ');
	data.away_final_score = std::stoul(buffer);
	
	//if scores followed by 'c' means there is corner info
	std::getline(line_stream, buffer, ' ');
	if (!buffer.compare("c")) {
		data.corner_info_availabe = true;
		std::getline(line_stream, buffer, ' ');
		data.home_fh_corners = std::stoul(buffer);
		std::getline(line_stream, buffer, ' ');
		data.away_fh_corners = std::stoul(buffer);
		std::getline(line_stream, buffer, ' ');
		data.home_sh_corners = std::stoul(buffer);
		std::getline(line_stream, buffer, ' ');
		data.away_sh_corners = std::stoul(buffer);
	}
	else
		data.corner_info_availabe = false;
	return data;

}

#include <iostream>
void printOneLineData(const OneLineData& data) {
	std::cout << "home team = " << data.home_name << "\n";
	std::cout << "away team = " << data.away_name << "\n";

	std::cout << data.home_final_score << " - " << data.away_final_score << "\n";
}