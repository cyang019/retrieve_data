#ifndef DONATION_ANALYSIS_MEDIANRUNNING_H
#define DONATION_ANALYSIS_MEDIANRUNNING_H

#include "MedianInterface.h"
#include <queue>
#include <vector>
#include <cstdint>

namespace donation_analysis {
/** \class MedianRunning stores values for running median calculation
 *
 * The class use two priority_queue<>'s to store values. The lower half
 * of values are stored in a max-heap, while the upper half of values are
 * stored in a min-heap. Thus median values can be retrieved at constant
 * time. And insertion of a value is bounded by O(nlog(n)).
 */
class MedianRunning : public MedianInterface {
public:
    MedianRunning() : m_total_amt(0) {};
    MedianRunning(const MedianRunning&) = default;
    MedianRunning(MedianRunning &&) noexcept;
    MedianRunning& operator=(const MedianRunning &) = default;
    MedianRunning& operator=(MedianRunning &&) noexcept;
    ~MedianRunning() {}

    /** push an element into the container.
     * \param t_val is the value to push into the container
     */
    void push(std::int64_t t_val) override final;

    /** calculate median of all values in the container.
     */
    std::int64_t calcMedian() override final;

    size_t getCnt() const override final 
    { return m_lower_q.size() + m_upper_q.size(); }

    std::int64_t getAmt() const override final { return m_total_amt; }
private:
    std::priority_queue<std::int64_t, 
                        std::vector<std::int64_t>, 
                        std::less<std::int64_t>> m_lower_q;
    std::priority_queue<std::int64_t, 
                        std::vector<std::int64_t>, 
                        std::greater<std::int64_t>> m_upper_q;
    std::int64_t m_total_amt;
};  // class MedianRunning
}   // namespace donation_analysis

#endif
