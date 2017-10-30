#ifndef DONATION_ANALYSIS_TRACKERDATE_H
#define DONATION_ANALYSIS_TRACKERDATE_H

#include <map>
#include <string>
#include <memory> // unique_ptr
#include <tuple> 
#include <functional> // std::less<std::string>
#include <iostream>
#include "MedianInterface.h"
#include "TrackerInterface.h"

namespace donation_analysis {

/** helper in organizing date strings in ascending order
 *
 * The comparison object has to be strickly weeak comparison
 * when A == B, should return false
 *
 * date string should be organized as mmddyyyy
 * Month starts at position 0,
 * date starts at position 1,
 * and year starts at position 4.
 */
struct DateCmp {
    bool operator()(const std::string &lhs, const std::string &rhs) const
    {
        if(lhs == rhs) return false;

        /// compare year first
        if(lhs.substr(4,4) > rhs.substr(4,4)) return false;
        if(lhs.substr(4,4) < rhs.substr(4,4)) return true;

        /// then compare month and date
        if(lhs.substr(0,4) > rhs.substr(0,4)) return false;

        /// otherwise (lhs.substr(0,4) < rhs.substr(0,4))
        return true;
    }
};  // struct DateCmp

/** TrackerDate is a hashtable of hashtable of median container.
 *
 * The first level use default sorting of key strings.
 * The second level sort date string considering "mmddyyyy"
 */
class TrackerDate : public TrackerInterface {
public:
    TrackerDate();
    TrackerDate(const TrackerDate&) = delete;   ///< member has unique_ptr
    TrackerDate(TrackerDate&&) noexcept;
    TrackerDate& operator=(const TrackerDate&) = delete;    
    ///< member has unique_ptr
    TrackerDate& operator=(TrackerDate&&) noexcept;
    ~TrackerDate();

    using PtrMedian = std::unique_ptr<MedianInterface>;
    using StrMap = std::map<std::string, PtrMedian, DateCmp>;   
    ///< ordered according to date format mmddyyyy

    /** test if the keys are in the Tracker container already.
     *
     * \param t_key is date as a string
     * \return a boolean.
     */
    bool has(const std::string &t_key) const override final;

    /** add an element into the Tracker container.
     */
    void add(const std::string &t_k, std::int64_t t_val) override final;

    TrackerInterface::EntryData getData() override final;
    void resetGetter() override final;

private:
    StrMap m_records;
    StrMap::iterator m_records_iter;
};  // class TrackerDate
}   // namespace dnonation_analysis

#endif
