/*
 * FastRPC -- Fast RPC library compatible with XML-RPC
 * Copyright (C) 2005-7  Seznam.cz, a.s.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Seznam.cz, a.s.
 * Radlicka 2, Praha 5, 15000, Czech Republic
 * http://www.seznam.cz, mailto:fastrpc@firma.seznam.cz
 *
 * FILE          $Id: frpcdatetime.h,v 1.8 2008-05-05 12:52:00 burlog Exp $
 *
 * DESCRIPTION
 *
 * AUTHOR
 *              Miroslav Talasek <miroslav.talasek@firma.seznam.cz>
 *
 * HISTORY
 *
 */
#ifndef FRPCDATETIME_H
#define FRPCDATETIME_H

#include <time.h>
#include <string>

#include <frpcvalue.h>

namespace FRPC
{
class Pool_t;

/**
@brief DateTime type
@author Miroslav Talasek
*/
class FRPC_DLLEXPORT DateTime_t : public Value_t
{
    friend class Pool_t;

public:
    enum{ TYPE = 0x05 };
    /**
        @brief Default destructor
    */
    virtual ~DateTime_t();
    /**
        @brief Getting type of value
        @return  @b unsigned @b short always
        @li @b DateTime_t::TYPE - identificator of datetime value
    */
    virtual unsigned short getType() const
    {
        return TYPE;
    }
    /**
        @brief Getting typename of value
        @return @b const @b char* always
        @li @b "DateTime" - typename of DateTime_t
    */
    virtual const char* getTypeName() const
    {
        return "dateTime";
    }
    /**
        @brief Get localtime day number.
        @return Day (1-31). */
    short getDay() const;
    /**
        @brief Get localtime hours.
        @return Hour (0-23).
    */
    short getHour() const;
    /**
        @brief Get localtime minutes.
        @return Minute (0-59).
    */
    short getMin() const;
    /**
        @brief Get localtime month number.
        @return Month (1-12).
    */
    short getMonth() const;
    /**
        @brief Get localtime seconds.
        @return Second (0-59).
    */
    short getSec() const;
    /**
        @brief Get localtime shift in sec relative to GMT (should be local timezone).

        Eastern timezones from GMT will report positive offset numbers,
        western timezones from GMT will report negative offsets.
        For example Central European Time (CET=GMT+0100) would have +3600.
        @return Localtime offset to GMT in secs.
    */
    int getTimeZone() const;
    /**
        @brief Get localtime year number.
        @return Year (1600-3647).
    */
    short getYear() const;
    /**
        @brief Get common unix time number (in UTC).
        @return Number of secs from 1970-01-01 00:00:00 UTC.
    */
    time_t getUnixTime() const;
    /**
        @brief  Get localtime day of week.
        @return Day of week (0=sunday, 1=monday, ..., 6=saturday).
    */
    short getDayOfWeek() const;
    /**
        @brief  Return true if datetime have save light day.
        @return true if datetime have is save light day.
    */
    bool isSaveLightDay() const;

    /**
        @brief Method to clone/copy DateTime_t
        @param newPool is reference of Pool_t which is used for allocate objects
    */
    virtual Value_t& clone(Pool_t &newPool) const;
    /**
        @brief get iso format.
        @return iso format string
    */
    std::string isoFormat() const;
    ///static members
    static const DateTime_t &FRPC_EPOCH;
    static const DateTime_t &FRPC_NULL;

private:
    /**
        @brief Constructor  from now time
    */
    DateTime_t();

    /**
        @brief Constructor.  Create specified date
        @param year - Year is offset (0 - 2047) to zero-year 1600
        (0=1600, ... 370 = 1970, ...)
        @param month - Month is 1 - 12
        @param day -   Day is 1 - 31
        @param hour -  Hour is 0 - 23
        @param min -   Minute is 0 - 59
        @param sec -   Second is 0 - 59
        @param weekDay
        @param unixTime
        @param timeZone as difference between UTC and localtime in seconds
    */
    DateTime_t(short year, char month, char day,
               char hour, char min, char sec, char weekDay,
               time_t unixTime, int timeZone);

    /**
        @brief Constructor.  Create specified date
        @param year - Year is offset (0 - 2047) to zero-year 1600
        (0=1600, ... 370 = 1970, ...)
        @param month - Month is 1 - 12
        @param day -   Day is 1 - 31
        @param hour -  Hour is 0 - 23
        @param min -   Minute is 0 - 59
        @param sec -   Second is 0 - 59
    */
    DateTime_t(short year, char month, char day,
               char hour, char min, char sec);

    /**
        @brief Constructor from common unix time number.
        @param unixTime Number of secs from 1970-01-01 00:00:00 UTC.
    */
    explicit DateTime_t(const time_t &unixTime);

    /**
        @brief Constructor from common unix time number.
        @param unixTime Number of secs from 1970-01-01 00:00:00 UTC.
        @param timeZone as difference between UTC and localtime in seconds.
    */
    DateTime_t(time_t unixTime, int timeZone);

     /**
        @brief Constructor from common unix time structure.
        @param dateTime unix date time structure.
    */
    explicit DateTime_t(const struct tm &tm);

     /**
        @brief Constructor from ISO format.
        @param isoFormat DateTime in iso format.
    */
    explicit DateTime_t(const std::string &isoFormat);

    /**
        @brief Create new DateTime_t object without clearly from given data.
               No additional check will be performed. Weekday and zone will be
               set to 0 .
    */
    explicit DateTime_t(short year, char month, char day,
                        char hour, char min, char sec,
                        time_t unixTime);


    short year;        /// year
    char month;        /// month
    char day;          /// day
    char hour;         /// hour
    char minute;       /// minute
    char sec;          /// second
    char weekDay;      /// day of week
    time_t unixTime;   /// long unix time
    int timeZone;      /// as difference between UTC and localtime in seconds
};

/**
    @brief Inline method

    Used to retype Value_t to DateTime_t
    @return  If Value_t  can  retype to DateTime_t return reference to DateTime_t
    @n If Value_t can't retype to DateTime_t throw exception TypeError_t
*/
inline FRPC_DLLEXPORT DateTime_t& DateTime(Value_t &value)
{
    DateTime_t *dateTime = dynamic_cast<DateTime_t*>(&value);

    if(!dateTime)
        throw TypeError_t("Type is %s but not dateTime",value.getTypeName());

    return *dateTime;
}

/**
    @brief Inline method

    Used to retype Value_t to DateTime_t
    @return  If Value_t  can  retype to DateTime_t return reference to DateTime_t
    @n If Value_t can't retype to DateTime_t throw exception TypeError_t
*/
inline FRPC_DLLEXPORT const DateTime_t& DateTime(const Value_t &value)
{
    const DateTime_t *dateTime = dynamic_cast<const DateTime_t*>(&value);

    if(!dateTime)
        throw TypeError_t("Type is %s but not dateTime",value.getTypeName());

    return *dateTime;
}

};

#endif
