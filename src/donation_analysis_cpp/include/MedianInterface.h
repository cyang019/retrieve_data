#ifndef DONATION_ANALYSIS_MEDIANINTERFACE_H
#define DONATION_ANALYSIS_MEDIANINTERFACE_H

#include <string>
#include <cstdint>

namespace donation_analysis {
/** class MedianInterface is the interface for median container.
 */
class MedianInterface {
public:
    /** push an element into the container.
     * \param t_val is the value to push into the container
     */
    virtual void push(std::int64_t t_val) = 0;

    /** calculate median of all values in the container.
     *
     * The method is not constant, because modification can
     * happen during the calculation
     */
    virtual std::int64_t calc_median() = 0;
};  // class MedianBuff
}   // namespace donation_analysis

#endif
