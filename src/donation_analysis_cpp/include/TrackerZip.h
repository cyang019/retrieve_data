#ifndef DONATION_ANALYSIS_TRACKER_H
#define DONATION_ANALYSIS_TRACKER_H

#include <unordered_map>
#include <string>
#include <memory> // unique_ptr
#include "MedianInterface.h"
#include "TrackerInterface.h"
#include <tuple> 

namespace donation_analysis {
/** TrackerZip is a hashtable of hashtable of median container.
 *
 */
class TrackerZip : public TrackerInterface {
public:
    TrackerZip();
    TrackerZip(const TrackerZip&) = delete;
    TrackerZip(TrackerZip&&) noexcept;
    TrackerZip& operator=(const TrackerZip&) = delete;
    TrackerZip& operator=(TrackerZip&&) noexcept;
    ~TrackerZip();

    using PtrMedian = std::unique_ptr<MedianInterface>;
    using StrMap = std::unordered_map<std::string, PtrMedian>;

    /** test if the keys are in the TrackerZip container already.
     *
     * \param t_key1 is the cmte_id
     * \param t_key2 is either zipcode or date as a string
     * \return a boolean.
     */
    bool has(const std::string &t_key) const override final;

    /** add an element into the TrackerZip container.
     */
    void add(const std::string &t_k, 
             std::int64_t t_val) override final;

    TrackerInterface::EntryData getData() override final;
    void resetGetter() override final;
private:
    StrMap m_records;
    std::string m_last_zipcode;
};  // class TrackerZip
}   // namespace dnonation_analysis

#endif
