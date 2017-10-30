#include "Record.h"
#include "TrackerDate.h"    // inherit from TrackerInterface
#include "TrackerZip.h"     // inherit from TrackerInterface
#include <cstdint>  // int64_t
#include <cstring>  // strtok
#include <iostream>     // endl
#include <map>
#include <memory>   // unique_ptr
#include <sstream>  // stringstream
#include <string>
#include <tuple>    // std::tie
#include <unordered_map>
#include <utility>  // make_pair

using ::std::int64_t;
using ::std::map;
using ::std::make_pair;
using ::std::make_unique;
using ::std::string;
using ::std::strtok;
using ::std::to_string;
using ::std::tuple;
using ::std::unordered_map;

namespace donation_analysis {
    Record::Record() : m_id_zip_records(), m_id_date_records()
    {}

    Record::Record(Record &&rhs) noexcept
        : m_id_zip_records(std::move(rhs.m_id_zip_records)),
        m_id_date_records(std::move(rhs.m_id_date_records))
    {}

    Record& Record::operator=(Record &&rhs) noexcept
    {
        m_id_zip_records = std::move(rhs.m_id_zip_records);
        m_id_date_records = std::move(rhs.m_id_date_records);

        return *this;
    }

    Record::~Record() {}

    std::string Record::parse_single_entry(const string &t_s)
    {
        string cmte_id, zipcode, date, other_id;
        int64_t amt;
        
        std::tie(cmte_id, zipcode, date, amt, other_id) = 
            m_extract_info_from_line(t_s);

        string output_line = "";
        /// if not from individual, skip entry
        if(!other_id.empty()) return output_line;
        /// if no cmte_id, skip entry
        if(cmte_id.empty()) return output_line;
        /// if no amount value, skip entry
        if(amt < 0) return output_line;

        /// if date is valid, store value to calculate median
        if(checkDate(date)){
            if(m_id_date_records.find(cmte_id) == m_id_date_records.end()){
                m_id_date_records.emplace(
                    make_pair(cmte_id, make_unique<TrackerDate>())
                    );
            }
            m_id_date_records[cmte_id]->add(date, amt);
        }

        /// if zip is valid, store value and return running median
        if(checkZipcode(zipcode)){
            //if(m_id_zip_records.find(cmte_id) == m_id_zip_records.end()){
                /// add 1st zipcode recipient
                m_id_zip_records.emplace(
                    make_pair(cmte_id, make_unique<TrackerZip>())
                    );
            //}
            /// add zipcode element
            m_id_zip_records[cmte_id]->add(zipcode, amt);
            int64_t median, total_amt;
            size_t cnt;
            /// get median, count, and total transaction amount
            std::tie(zipcode, median, cnt, total_amt) = 
                m_id_zip_records[cmte_id]->getData();

            output_line += cmte_id + "|" + zipcode + "|" 
                + to_string(median) + "|" + to_string(cnt) + "|" 
                + to_string(total_amt);
        }

        return output_line;
    }

    void Record::calc_and_export_medianvals_by_date(std::ostream &t_os)
    {
        string date;
        int64_t median, total_amt;
        size_t cnt;
        for(auto &kv : m_id_date_records){
            const string cmte_id = kv.first;
            (kv.second)->resetGetter();
            std::tie(date, median, cnt, total_amt) = (kv.second)->getData();

            /// past last element when getting all empty entries.
            while(true){ 
                if((date == "") && (median == 0) && (cnt == 0) && (total_amt == 0)) break;
                const string out_str =
                    cmte_id + "|" + date + "|"
                    + to_string(median) + "|" + to_string(cnt) + "|"
                    + to_string(total_amt);
                ///< out_str format: cmte_id|date|median|cnt|total_amt
                t_os << out_str << std::endl;
                std::tie(date, median, cnt, total_amt) = (kv.second)->getData();
            }
        }
    }

    /** Get cmte_id, zipcode, date, amount from a pipe deliminated line
     * \param t_s is the input line.
     * \return a tuple of above mentioned data.
     */
    tuple<string, string, string, int64_t, string>
    Record::m_extract_info_from_line(const string &t_s)
    {
        std::string delim = "|";    ///< fields are pipe deliminated.
        string cmte_id, zipcode, date, other_id, strAmt;
        std::stringstream sAmt;
        int64_t amt = 0;
        std::string token;
        size_t token_cnt = 0;   ///< index of token
        size_t pos = 0; ///< token position in the string
        size_t found = 0; ///< pipe position
        while((found = t_s.find(delim,pos)) != string::npos){
            ++token_cnt;
            token = t_s.substr(pos,found - pos);
            pos = found+1;  ///< look ahead the found pipe character
            switch(token_cnt){
                case 1: cmte_id = token;    ///< CMTE_ID
                        break;
                case 11: zipcode = token; break;    ///< ZIPCODE
                case 14: date = token; break;   ///< TRANSACTION_DT
                case 15: strAmt = token;    ///< TRANSACTION_AMT
                         if(strAmt.empty()) amt = -1;   ///< if no amount
                         else {     /// convert char* to int
                            sAmt << token;
                            sAmt >> amt;
                         }
                         break;
                case 16: other_id = token; break;   ///< OTHER_ID
                default: break;
            }
        }

        /// When there are exactly 16 fields, cannot find last pipe.
        if(other_id.empty() && token_cnt == 15){
            if(pos == t_s.size()) other_id = "";
            else
                other_id = t_s.substr(pos);
        }

        if(zipcode.length() > 5) zipcode = zipcode.substr(0,5);

        return make_tuple(cmte_id, zipcode, date, amt, other_id);
    }
}   // namespace donation_analysis
