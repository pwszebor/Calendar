//
// Created by pawel on 18/02/16.
//

#ifndef CALENDAR_CALENDAR_H
#define CALENDAR_CALENDAR_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <utility>

namespace Calendar {

using namespace boost::gregorian;

struct DateRange : public std::pair<day_iterator, day_iterator> {
    DateRange(const day_iterator &begin, const day_iterator &end) :
            std::pair<day_iterator, day_iterator>(begin, end) {

    }
    DateRange() :
            std::pair<day_iterator, day_iterator>(day_iterator(date()), day_iterator(date())) {

    }
};

class Calendar {
public:
    Calendar(unsigned short year);
    ~Calendar();

    void display(std::ostream &str);

private:
    std::vector<DateRange> getMonths();
    std::vector<DateRange> getWeeks(DateRange &month);
    std::string getMonthName(DateRange &month);
    std::string formatDay(const date &day);
    std::string formatWeek(DateRange &week);

private:
    unsigned short year_;
    DateRange yearRange_;
};

} // namespace Calendar

#endif //CALENDAR_CALENDAR_H
