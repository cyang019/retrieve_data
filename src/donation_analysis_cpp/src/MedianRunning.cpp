#include "MedianRunning.h"

using ::std::int64_t;

namespace donation_analysis {

// move constructors
    MedianRunning::MedianRunning(MedianRunning &&rhs) noexcept
        : m_lower_q(std::move(rhs.m_lower_q)), 
        m_upper_q(std::move(rhs.m_upper_q)), 
        m_total_amt(rhs.m_total_amt)
    {}

    MedianRunning& MedianRunning::operator=(MedianRunning &&rhs) noexcept
    {
        m_lower_q = std::move(rhs.m_lower_q);
        m_upper_q = std::move(rhs.m_upper_q);
        m_total_amt = rhs.m_total_amt;

        return *this;
    }

    void MedianRunning::push(int64_t t_val)
    {
        m_total_amt += t_val;

        if(m_lower_q.empty() || m_lower_q.top() > t_val) m_lower_q.push(t_val);
        else m_upper_q.push(t_val);

        if(m_lower_q.size() > (m_upper_q.size() + 1)){
            m_upper_q.push(m_lower_q.top());
            m_lower_q.pop();
            return;
        }

        if((m_lower_q.size() + 1) < m_upper_q.size()){
            m_lower_q.push(m_upper_q.top());
            m_upper_q.pop();
        }
    }

    int64_t MedianRunning::calcMedian()
    {
        if(m_lower_q.size() == m_upper_q.size()){
            if(m_lower_q.size() == 0) return 0;

            //// round 0.5 up
            const int64_t val_sum = m_lower_q.top() + m_upper_q.top();
            return (val_sum % 2 == 0) ? val_sum/2 : (val_sum+1)/2;
        }
        
        return (m_lower_q.size() > m_upper_q.size()) 
            ? m_lower_q.top() : m_upper_q.top();
    }

}   // namespace donation_analysis
