#include "TrackerDate.h"
#include "MedianStatic.h"
#include <iostream>
#include <memory>   // make_unique
#include <string>
#include <tuple>

namespace donation_analysis {
/// constructors
    TrackerDate::TrackerDate() 
        : TrackerInterface()
    { m_records_iter = m_records.begin(); }

    TrackerDate::TrackerDate(TrackerDate &&rhs) noexcept
        : TrackerInterface(), m_records(std::move(rhs.m_records))
    { m_records_iter = m_records.begin(); }

    TrackerDate& TrackerDate::operator=(TrackerDate &&rhs) noexcept
    {
        m_records = std::move(rhs.m_records);
        m_records_iter = m_records.begin();
        return *this;
    }

    TrackerDate::~TrackerDate() {}

/// methods
    bool TrackerDate::has(const std::string &t_key) const
    {
        auto pos = m_records.find(t_key);
        if(pos == m_records.end()) return false;

        return true;
    }

    void TrackerDate::add(const std::string &t_k,
                          std::int64_t t_val)
    {
        if(m_records.find(t_k) == m_records.end()){
            m_records.emplace(std::make_pair(t_k, 
                        std::make_unique<MedianStatic>()));
        }

        (m_records[t_k])->push(t_val);
    }

    TrackerInterface::EntryData TrackerDate::getData()
    {
        if(m_records_iter != m_records.end()){
            const std::string date = m_records_iter->first;
            auto median = m_records_iter->second->calcMedian();
            auto cnt = m_records_iter->second->getCnt();
            auto amt = m_records_iter->second->getAmt();

            ++m_records_iter;

            return std::make_tuple(date, median, cnt, amt); 
        }
        return std::make_tuple("", 0, 0, 0);
    }

    void TrackerDate::resetGetter()
    {
        m_records_iter = m_records.begin();
    }
}   // namespace donation_analysis
