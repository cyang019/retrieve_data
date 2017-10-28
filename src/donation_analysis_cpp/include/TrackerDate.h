#ifndef DONATION_ANALYSIS_TRACKERDATE_H
#define DONATION_ANALYSIS_TRACKERDATE_H

#include <map>
#include <string>
#include <memory> // unique_ptr
#include "MedianInterface.h"
#include "TrackerInterface.h"
#include <tuple> 
#include <functional> // std::less<std::string>

namespace donation_analysis {

/** helper in organizing date strings in ascending order
 *
 * date string should be organized as mmddyyyy
 * Month starts at position 0,
 * date starts at position 1,
 * and year starts at position 4.
 */
struct DateCmp {
    bool operator()(const std::string &lhs, const std::string &rhs) const
    {
        /// compare year first
        if(std::stoi(lhs.substr(4),nullptr) > std::stoi(rhs.substr(4),nullptr)){
            return false;
        }
        /// compare month
        if(std::stoi(lhs.substr(0,2),nullptr) > std::stoi(rhs.substr(0,2),nullptr)){
            return false;
        }
        /// compare date
        if(std::stoi(lhs.substr(2,2),nullptr) > std::stoi(rhs.substr(2,2),nullptr)){
            return false;
        }
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
    TrackerDate(const TrackerDate&);
    TrackerDate(TrackerDate&&) noexcept;
    TrackerDate& operator=(const TrackerDate&);
    TrackerDate& operator=(TrackerDate&&) noexcept;
    ~TrackerDate();

    using PtrMedian = std::unique_ptr<MedianInterface>;
    using StrMap = std::map<std::string, PtrMedian>;
    using StrStrMap = std::map<std::string, StrMap, std::less<std::string>>;

    /** test if the keys are in the Tracker container already.
     *
     * \param t_key1 is the cmte_id
     * \param t_key2 is either zipcode or date as a string
     * \return a boolean.
     */
    bool has(const std::string &t_key1, const std::string &t_key2) const;

    /** add an element into the Tracker container.
     */
    Tracker& add(const std::string &t_k1, 
                 const std::string &t_k2, 
                 std::int64_t t_val);

    using TypeValCntAmt = std::tuple<std::int64_t, size_t, std::int64_t>;
    TypeValCntAmt 
private:
    StrStrMap m_records;
};  // class TrackerDate
}   // namespace dnonation_analysis

#endif
