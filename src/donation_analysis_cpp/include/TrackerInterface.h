#ifndef DONATION_ANALYSIS_TRACKERINTERFACE_H
#define DONATION_ANALYSIS_TRACKERINTERFACE_H

#include <unordered_map>
#include <string>
#include <tuple> 
#include <cstdint>
#include "MedianInterface.h"

namespace donation_analysis {
/** TrackerInterface is an abstract base class to store values in order for 
 * calculating medians.
 *
 * The provide provides `add()` to insert elements and `getData()` to retrieve
 * median related data.
 *
 * The class provides flexibility for future extensions
 */
class TrackerInterface {
public:
    /** pure virtual, test if the keys are in the Tracker container already.
     *
     * \param t_key is either zipcode or date as a string
     * \return a boolean.
     */
    virtual bool has(const std::string &t_key) const = 0;

    /** add an element into the Tracker container.
     *
     * \param t_k is either a zipcode or date
     * \param t_val is the value to add into the container.
     */
    virtual void add(const std::string &t_k, 
                     std::int64_t t_val) = 0;

    /// zipcode or date, median, count, transaction amount
    using EntryData = std::tuple<std::string, 
                                 std::int64_t, size_t, std::int64_t>;

    virtual EntryData getData() = 0;
    virtual void resetGetter() = 0;
};  // class TrackerInterface
}   // namespace dnonation_analysis

#endif
