#include "TrackerZip.h"
#include "MedianRunning.h"
#include <iostream>
#include <memory>   // make_unique
#include <string>
#include <tuple>

namespace donation_analysis {
/// constructors
    TrackerZip::TrackerZip() 
        : TrackerInterface(), m_last_zipcode("")
    {}

    TrackerZip::TrackerZip(TrackerZip &&rhs) noexcept
        : TrackerInterface(), 
        m_records(std::move(rhs.m_records)),
        m_last_zipcode(std::move(rhs.m_last_zipcode))
    {}

    TrackerZip& TrackerZip::operator=(TrackerZip &&rhs) noexcept
    {
        m_records = std::move(rhs.m_records);
        m_last_zipcode = std::move(rhs.m_last_zipcode);
        return *this;
    }

    TrackerZip::~TrackerZip() {}

/// methods

    /** tests if a key is in the TrackerZip container
      * \param t_key is the zipcode to look for.
      * \return a boolean value.
      */
    bool TrackerZip::has(const std::string &t_key) const
    {
        auto pos = m_records.find(t_key);
        if(pos == m_records.end()) return false;

        return true;
    }

    /** add a component into the TrackerZip container
     *
     * The method would also store the key in m_last_zipcode for output.
     *
     * \param t_k is the key
     * \param t_val is the value
     */
    void TrackerZip::add(const std::string &t_k,
                          std::int64_t t_val)
    {
        if(m_records.find(t_k) == m_records.end()){
            m_records.emplace(std::make_pair(t_k, 
                        std::make_unique<MedianRunning>()));
        }

        (m_records[t_k])->push(t_val);
        m_last_zipcode = t_k;
    }

    TrackerInterface::EntryData TrackerZip::getData()
    {
        if(!m_last_zipcode.empty()){
            const std::string zip = m_last_zipcode;
            auto median = m_records[zip]->calcMedian();
            auto cnt = m_records[zip]->getCnt();
            auto amt = m_records[zip]->getAmt();

            return std::make_tuple(zip, median, cnt, amt); 
        }
        /// if not found, returns a dummy entry
        return std::make_tuple("", 0, 0, 0);
    }

    void TrackerZip::resetGetter()
    {
        m_last_zipcode = "";
    }

}   // namespace donation_analysis
