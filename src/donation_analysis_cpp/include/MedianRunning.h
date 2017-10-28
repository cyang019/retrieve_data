#ifndef DONATION_ANALYSIS_MEDIANRUNNING_H
#define DONATION_ANALYSIS_MEDIANRUNNING_H

#include "MedianInterface.h"
#include <queue>
#include <vector>
#include <string>
#include <cstdint>

namespace donation_analysis {
class MedianRunning : public MedianInterface {
public:
    MedianRunning() = default;
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
    std::int64_t calc_median() override final;
private:
    std::priority_queue<std::int64_t, 
                        std::vector<std::int64_t>, 
                        std::less<std::int64_t>> m_lower_q;
    std::priority_queue<std::int64_t, 
                        std::vector<std::int64_t>, 
                        std::greater<std::int64_t>> m_upper_q;
};  // class MedianRunning
}   // namespace donation_analysis

#endif
