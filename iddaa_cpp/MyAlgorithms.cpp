#include <string>
#include <sstream>
#include "MyAlgortihms.h"

bool sortMatchesByDate(const Match& m1, const Match& m2) {

	std::istringstream date1(m1.date);
	std::istringstream date2(m2.date);

	std::string day1;
	std::getline(date1, day1, '.');
	int i_day1 = std::stoi(day1);

	std::string month1;
	std::getline(date1, month1, '.');
	int i_month1 = std::stoi(month1);

	std::string year1;
	std::getline(date1, year1);
	int i_year1 = std::stoi(year1);

	std::string day2;
	std::getline(date2, day2, '.');
	int i_day2 = std::stoi(day2);

	std::string month2;
	std::getline(date2, month2, '.');
	int i_month2 = std::stoi(month2);

	std::string year2;
	std::getline(date2, year2);
	int i_year2 = std::stoi(year2);

	if (i_year1 < i_year2)
		return true;
	else if (i_year1 == i_year2 && i_month1 < i_month2)
		return true;
	else if (i_year1 == i_year2 && i_month1 == i_month2 && i_day1 < i_day2)
		return true;
	else
		return false;
}


bool sortByAlphabethical() {

}