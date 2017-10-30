#ifndef DONATION_ANALYSIS_RECORD_H
#define DONATION_ANALYSIS_RECORD_H

#include "TrackerInterface.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>   // unique_ptr
#include <tuple>
#include <string>
#include <unordered_map>


namespace donation_analysis {
    /// test if Date is valid.
    bool checkDate(const std::string &);
    /// test if Zipcode is valid.
    bool checkZipcode(const std::string &);

    class Record {
    public:
        Record();
        Record(const Record &) = delete;    // has unique_ptr
        Record(Record &&) noexcept;
        Record& operator=(const Record &);  // has unique_ptr
        Record& operator=(Record &&) noexcept;
        ~Record();

        using PtrTracker = std::unique_ptr<TrackerInterface>;

        /// add elements into two trackers, return running median line.
        std::string parse_single_entry(const std::string&);
        /// write into a stream of medians sorted by cmte_id, then date.
        void calc_and_export_medianvals_by_date(std::ostream &);
    private:
        std::unordered_map<std::string, PtrTracker> m_id_zip_records;
        std::map<std::string, PtrTracker> m_id_date_records;

        /// get cmte_id, zipcode, date, amount, and other_id from a line
        /** CMTE_ID, ZIP_CODE, TRANSACTION_DT, TRANSACTION_AMT, and OTHER ID are
         * organized as described in Metadata Description on FEC website.
         */
        std::tuple<std::string, std::string, std::string, 
                   std::int64_t, std::string>
        m_extract_info_from_line(const std::string &);
    };  // class Record

    /// checkDate only checks if input are digits and have correct length.
    /// Date has format mmddyyyy (length = 8)
    inline bool checkDate(const std::string &t_s)
    {
        if(t_s.length() != 8) return false;
        if(std::find_if(t_s.begin(),
                t_s.end(), [](char c){ return !std::isdigit(c); }) != t_s.end())
            return false;

        /// months should be between 01 ~ 12
        if((t_s[0] != '1') && (t_s[0] != '0')) return false;
        if(t_s[0] == '1'){
            if((t_s[1] != '0') && (t_s[1] != '1') && (t_s[1] != '2'))
                return false;
        }

        /// dates first digit between 0 ~ 3
        if((t_s[0] != '0') && (t_s[0] != '1') && (t_s[0] != '2')
                && (t_s[0] != '3')) return false;

        return true;
    }

    /// checkZipcode only checks if more then 5 digits (numerical).
    /// Zipcode has 5 to 9 digits.
    inline bool checkZipcode(const std::string &t_s)
    {
        if(t_s.length() < 5) return false;
        /// first 5 characters need to be digits.
        if(std::find_if(t_s.begin(),
                t_s.begin()+5, 
                [](char c){ return !std::isdigit(c); }) != t_s.begin()+5)
            return false;

        return true;
    }
}   // namespace donation_analysis

#endif
