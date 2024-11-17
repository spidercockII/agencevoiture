#ifndef DATE_HPP
#define DATE_HPP

#include <stdint.h>
#include <string>
#include <vector>
#include <stdexcept>

class Date{
private:
    uint8_t d;
    uint8_t m;
    uint8_t y;

    bool isValid() const noexcept;
public:
    Date(const std::string& ddmmyyyy);
    Date(const uint8_t& dd, const uint8_t& mm, const uint8_t& yyyy);

    uint8_t              getDay()                            const noexcept;
    uint8_t              getMonth()                          const noexcept;
    uint8_t              getYear()                           const noexcept;
    std::string          getDateStr(const std::string& sep)  const noexcept;
    std::vector<uint8_t> getDateVec()                        const noexcept;

    void        setDay(const uint8_t& day);
    void        setMonth(const uint8_t& month);
    void        setYear(const uint8_t& year);
    void        setDateStr(const std::string& date);
    void        setDate(uint8_t dd, uint8_t mm, uint8_t yyyy);
};

class DateException : public std::runtime_error {
public:
    DateException(const std::string& msg) : std::runtime_error(msg) {}
};

class InvalidDateFormat : public DateException {
public:
    InvalidDateFormat(const std::string& msg) : DateException(msg) {}
};

class DateOutOfRange : public DateException {
public:
    DateOutOfRange(const std::string& msg) : DateException(msg) {}
};


#endif
