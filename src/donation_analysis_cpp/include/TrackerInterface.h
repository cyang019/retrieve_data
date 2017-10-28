#ifndef DONATION_ANALYSIS_TRACKERINTERFACE_H
#define DONATION_ANALYSIS_TRACKERINTERFACE_H

#include <unordered_map>
#include <string>
#include "MedianInterface.h"
#include <tuple> 

namespace donation_analysis {
/** TrackerInterface is an abstract base class for hash table of hash table
 *
 * Both levels should have string as keys
 *
 * A recipient would need two Trackers: 
 *  1) cmte_id and zipcode are the two level keys.
 *  2) cmte_id and date are the two level keys.
 *
 * The class provides flexibility for future extensions
 */
class TrackerInterface {
public:
    /** pure virtual, test if the keys are in the Tracker container already.
     *
     * \param t_key1 is the cmte_id
     * \param t_key2 is either zipcode or date as a string
     * \return a boolean.
     */
    virtual bool has(const std::string &t_key1, const std::string &t_key2) const = 0;

    /** add an element into the Tracker container.
     */
    Tracker& add(const std::string &t_k1, 
                 const std::string &t_k2, 
                 std::int64_t t_val) = 0;

    using TypeValCntAmt = std::tuple<std::int64_t, size_t, std::int64_t>;
    TypeValCntAmt evaluate(const std::string &t_k1, const std::string &t_k2) = 0;
};  // class TrackerInterface
}   // namespace dnonation_analysis

#endif
