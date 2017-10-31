#pragma once

#include <ostream>

struct Date{
     unsigned int YEAR;
     unsigned int MONTH;
     unsigned int DAY;
 };

bool checkDate(const Date& date);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
std::ostream& operator<<(std::ostream& s, const Date& date);
