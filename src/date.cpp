#include "date.h"
#include <array>

using std::array;

namespace {

array<int,13> daysInMoth = {0/*dummy*/,31,28,31,30,31,30,31,31,30,31,30,31};

bool isLeepYear(unsigned year) {
    if (year % 4 != 0) return false;
    else if (year % 100 != 0) return true;
    else if (year % 400 != 0) return false;
    return true;
}


} // anonymous namespace





bool checkDate(const Date& date) {
    if (date.MONTH < 1 || date.MONTH > 12 || date.DAY < 1) return false;
    int maxDay = daysInMoth[ date.MONTH ];
    if (date.MONTH == 2 && isLeepYear(date.YEAR)) {
        maxDay = 29;
    }
    return date.DAY <= maxDay;
}

std::ostream& operator<<(std::ostream& s, const Date& date) {
    s << date.MONTH << date.DAY << date.YEAR;
    return s;
}

bool operator==(const Date& lhs, const Date& rhs){
    return lhs.YEAR == rhs.YEAR && lhs.MONTH == rhs.MONTH && lhs.DAY == rhs.DAY;
}
bool operator!=(const Date& lhs, const Date& rhs){
    return !(lhs == rhs);
}
