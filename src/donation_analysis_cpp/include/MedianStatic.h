#ifndef DONATION_ANALYSIS_MEDIANSTATIC_H
#define DONATION_ANALYSIS_MEDIANSTATIC_H

#include "MedianInterface.h"
#include <vector>
#include <cstdint>

namespace donation_analysis {
/** class MedianStatic stores values for infrequent calculation of medians.
 *
 * Beacuse one only needs to calculate median values infrequently. This
 * container is using a vector to provide (on average) constant time insertion.
 * The median value is calculated using a quick select algorithm by using
 * STL's `nth_element()` method. 
 */
class MedianStatic : public MedianInterface {
public:
    MedianStatic() : m_vals(), m_total_amt(0) {};
    MedianStatic(const MedianStatic&) = default;
    MedianStatic(MedianStatic &&) noexcept;
    MedianStatic& operator=(const MedianStatic &) = default;
    MedianStatic& operator=(MedianStatic &&) noexcept;
    ~MedianStatic() {}

    /** push an element into the container.
     * \param t_val is the value to push into the container
     */
    void push(std::int64_t t_val) override final;

    /** calculate median of all values in the container.
     */
    std::int64_t calcMedian() override final;

    size_t getCnt() const override final { return m_vals.size(); }
    std::int64_t getAmt() const override final { return m_total_amt; }
private:
    std::vector<std::int64_t> m_vals;
    std::int64_t m_total_amt;
};  // class MedianStatic
}   // namespace donation_analysis


#endif
