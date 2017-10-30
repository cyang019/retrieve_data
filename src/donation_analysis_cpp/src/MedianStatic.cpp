#include "MedianStatic.h"
#include <algorithm>    // nth_element

using ::std::int64_t;
using ::std::nth_element;

namespace donation_analysis {

// move constructors
    MedianStatic::MedianStatic(MedianStatic &&rhs) noexcept
        : m_vals(std::move(rhs.m_vals)), 
        m_total_amt(rhs.m_total_amt)
    {}

    MedianStatic& MedianStatic::operator=(MedianStatic &&rhs) noexcept
    {
        m_vals = std::move(rhs.m_vals);
        m_total_amt = rhs.m_total_amt;

        return *this;
    }

    void MedianStatic::push(int64_t t_val)
    {
        m_vals.push_back(t_val);
        m_total_amt += t_val;
    }

    int64_t MedianStatic::calcMedian()
    {
        if(m_vals.size() == 0u) return 0;
        if(m_vals.size() == 1u) return m_vals[0];

        const auto idx = m_vals.size()/2;
        if(m_vals.size()%2 == 0u){
            /// get (n-1)th index, and partial sort first half
            nth_element(m_vals.begin(), 
                        m_vals.begin() + idx-1, 
                        m_vals.end());
            /// get nth index, and partial sort second half
            nth_element(m_vals.begin() + idx,
                        m_vals.begin() + idx,
                        m_vals.end());

            const auto total_val = m_vals[idx-1] + m_vals[idx];
            /// if median value has a .5, round up
            return (total_val % 2 == 0) ? total_val/2 : (total_val + 1)/2;
        }else{
            nth_element(m_vals.begin(), 
                        m_vals.begin() + idx, 
                        m_vals.end());
            return m_vals[idx];
        }
    }

}   // namespace donation_analysis
