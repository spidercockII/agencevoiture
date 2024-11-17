#include "date.hpp"
#include <iomanip>
#include <regex>

Date::Date(const std::string& ddmmyyyy) {
    std::regex datePattern(R"((\d{2})[-/](\d{2})[-/](\d{4}))");
    std::smatch match;

    if (std::regex_match(ddmmyyyy, match, datePattern)) {
        try {
            d = std::stoi(match[1].str());
            m = std::stoi(match[2].str());
            y = std::stoi(match[3].str());
        } catch (const std::invalid_argument&) {
            throw InvalidDateFormat("Invalid date components.");
        }

        if (!isValid()) {
            throw DateOutOfRange("Date is out of range.");
        }
    } else {
        throw InvalidDateFormat("Invalid date format. Expected dd/mm/yyyy or dd-mm-yyyy.");
    }
}


Date::Date(const uint8_t& dd, const uint8_t& mm, const uint8_t& yyyy)
    : d(dd), m(mm), y(yyyy) {
    if (!isValid()) {
        throw DateOutOfRange("Date is out of range.");
    }
}

bool Date::isValid() const noexcept {
    if (m < 1 || m > 12 || d < 1 || d > 31)
        return false;

    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
        return false;

    if (m == 2) {
        bool leapYear = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
        if ((leapYear && d > 29) || (!leapYear && d > 28))
            return false;
    }

    return true;
}

uint8_t Date::getDay() const noexcept {
    return d;
}

uint8_t Date::getMonth() const noexcept {
    return m;
}

uint8_t Date::getYear() const noexcept {
    return y;
}

std::string Date::getDateStr(const std::string& sep) const noexcept {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << static_cast<int>(d) << sep
       << std::setw(2) << std::setfill('0') << static_cast<int>(m) << sep
       << static_cast<int>(y);
    return ss.str();
}

std::vector<uint8_t> Date::getDateVec() const noexcept {
    return {d, m, y};
}

void Date::setDay(const uint8_t& day) {
    d = day;
    if (!isValid()) {
        throw DateOutOfRange("Invalid day for the current month/year.");
    }
}

void Date::setMonth(const uint8_t& month) {
    m = month;
    if (!isValid()) {
        throw DateOutOfRange("Invalid month for the current year.");
    }
}

void Date::setYear(const uint8_t& year) {
    y = year;
    if (!isValid()) {
        throw DateOutOfRange("Invalid year for the current month/day.");
    }
}

void Date::setDate(uint8_t dd, uint8_t mm, uint8_t yyyy) {
    d = dd;
    m = mm;
    y = yyyy;
    if (!isValid()) {
        throw DateOutOfRange("Invalid date.");
    }
}

void Date::setDateStr(const std::string& date) {
    *this = Date(date);
}
