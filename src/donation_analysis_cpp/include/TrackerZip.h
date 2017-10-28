#ifndef DONATION_ANALYSIS_TRACKER_H
#define DONATION_ANALYSIS_TRACKER_H

#include <unordered_map>
#include <string>
#include <memory> // unique_ptr
#include "MedianInterface.h"
#include <tuple> 

namespace donation_analysis {
/** Tracker is a hashtable of hashtable of median container.
 *
 * A recipient would need two Trackers: 
 *  1) cmte_id and zipcode are the two level keys.
 *  2) cmte_id and date are the two level keys.
 */
class Tracker {
public:
    Tracker();
    Tracker(const Tracker&);
    Tracker(Tracker&&) noexcept;
    Tracker& operator=(const Tracker&);
    Tracker& operator=(Tracker&&) noexcept;
    ~Tracker();

    using PtrMedian = std::unique_ptr<MedianInterface>;
    using StrMap = std::unordered_map<std::string, PtrMedian>;
    using StrStrMap = std::unordered_map<std::string, StrMap>;

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
};  // class Tracker
}   // namespace dnonation_analysis

#endif
