//
// Created by pawel on 18/02/16.
//

#include "calendar.h"
#include <boost/format.hpp>

namespace Calendar {

Calendar::Calendar(unsigned short year) :
        year_(year),
        yearRange_(day_iterator(date(greg_year(year_), 1, 1)), day_iterator(date(greg_year(year_), 12, 31))) {
}

Calendar::~Calendar() {

}

void Calendar::display(std::ostream &str) {
    auto months = getMonths();
    for(auto month : months) {
        str << "\n" << getMonthName(month) << "\n";
        auto weeks = getWeeks(month);
        for(auto week : weeks) {
            str << formatWeek(week) << "\n";
        }
    }
}

void Calendar::displayInAGrid(std::ostream &str) {
    auto months = getMonths();
    for(auto row = 0; row < 4; ++row) {
        str << getMonthName(months.at(3 * row)) << "   "
            << getMonthName(months.at(3 * row + 1)) << "   "
            << getMonthName(months.at(3 * row + 2)) << "\n";
        auto weeks1 = getWeeks(months.at(3 * row));
        auto weeks2 = getWeeks(months.at(3 * row + 1));
        auto weeks3 = getWeeks(months.at(3 * row + 2));
        for(auto line = 1; line <= 6; ++line) {
            line <= weeks1.size() ? str << formatWeek(weeks1.at(line - 1)) : str << boost::str(boost::format("%|22t|"));
            str << "   ";
            line <= weeks2.size() ? str << formatWeek(weeks2.at(line - 1)) : str << boost::str(boost::format("%|22t|"));
            str << "   ";
            line <= weeks3.size() ? str << formatWeek(weeks3.at(line - 1)) : str << boost::str(boost::format("%|22t|"));
            str << "\n";
        }
    }
}

std::vector<DateRange> Calendar::getMonths() {
    std::vector<DateRange> months;
    auto monthBegin = yearRange_.first;
    for(auto day = monthBegin; day <= *yearRange_.second;) {
        auto monthEnd = day;
        if(day->month() != (++day)->month()) {
            months.push_back(DateRange(monthBegin, monthEnd));
            monthBegin = day;
        }
    }
    return months;
}

std::vector<DateRange> Calendar::getWeeks(DateRange &month) {
    std::vector<DateRange> weeks;
    auto weekBegin = month.first;
    auto weekEnd = weekBegin;
    for(auto day = weekBegin; day <= *month.second;) {
        weekEnd = day;
        if(day->week_number() != (++day)->week_number()) {
            weeks.push_back(DateRange(weekBegin, weekEnd));
            weekBegin = day;
        }
    }
    weeks.push_back(DateRange(weekBegin, weekEnd));
    return weeks;
}

std::string Calendar::getMonthName(DateRange &month) {
    return boost::str(boost::format("%|=22|") % month.first->month().as_long_string());
}

std::string Calendar::formatDay(const date &day) {
    return boost::str(boost::format("%|3|") % day.day());
}

std::string Calendar::formatWeek(DateRange &week) {
    std::string str;
    for(auto day = week.first; day <= *week.second; ++day)
        str += formatDay(*day);
    auto dayNum = week.first->day_of_week();
    return boost::str(boost::format("%1%%2%%|22t|") % std::string((dayNum == Sunday ? 6 : dayNum - 1) * 3, ' ') % str);
}

} // namespace Calendar
