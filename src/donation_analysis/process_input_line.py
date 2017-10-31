# -*- coding: utf-8 -*-
"""
This module provides methods to extract info from lines and to keep track.
"""

from .calc_median import RunningMedian, StaticMedian


class NotEnoughFields(ValueError):
    """An exception indicating insufficient number of fields in an input entry.
    """
    pass

def extract_info_from_line(line):
    """Extract five required fields from a pipe separated single entry.

    Retrieve CMTE_ID, ZIP_CODE, TRANSACTION_DT, TRANSACTION_AMT, and OTHER_ID as
    defined in file format information of Metadata Description on FEC website.

    Args:
        line: a string containing a single entry of donation to a recipient.

    Returns:
        A tuple with extracted CMTE_ID, zip code, transaction date, transaction
        amount, and indicator if from individual.
    """
    entries = line.split("|")  # fields are pipe separated
    if len(entries) < 16:
        raise NotEnoughFields( \
                "each line should contain"
                " at least 16 fields according to specifications"
                " for file format information.")

    cmte_id = entries[0]
    zipcode = entries[10]  # 11th position
    if len(zipcode) > 5:   # only keep 1st 5 digits for zipcode
        zipcode = zipcode[:5]
    t_dt = entries[13]  # transaction date at 14th position
    t_amt = entries[14]  # transaction amount at 15th position
    other_id = entries[15]  # other identification number, should be empty for
                            # donation from individual.
    return cmte_id, zipcode, t_dt, t_amt, other_id

def check_zip(zip_code):
    """check if zip code has correct format.

    Args:
        zip_code as a string

    Returns:
        a boolean indicating if valid (True) or not (False)
    """
    if len(zip_code) < 5:
        return False
    if not zip_code[:5].isdigit():
        return False
    return True

def check_date(date):
    """check if date string has correct format.

    Args:
        date as a string mmddyyyy

    Returns:
        a boolean indicating if valid (True) or not (False)
    """
    if len(date) != 8:
        return False
    if not date.isdigit():
        return False
    # months are between '01' ~ '12'
    if (date[0] != '1' and date[0] != '0'):
        return False
    if date[0] == '1':
        if (date[1] != '0') and (date[1] != '1') and (date[1] != '2'):
            return False

    # dates are between 0 ~ 31
    if (date[2] != '0') and (date[2] != '1') \
            and (date[2] != '2') and (date[2] != '3'):
        return False

    return True

def check_amt(amt):
    """check if amount contains only integers.
    """
    if not amt.isdigit():
        return False

    return True

def date_to_numerical(date):
    """convert date string to a number for chronological sorting.

    Returns:
        value = year * 2000  + month * 100 + date
        the last two decimal digits are reserved for dates.
        The middle two digits will have months values 1 ~ 12.
        year * 2000 is garanteed to have value larger than
        month * 100.
    """
    month_val = int(date[0:2])
    date_val = int(date[2:4])
    year_val = int(date[4:8])
    return year_val * 2000 + month_val * 100 + date_val


class Record:
    """Handler for all Recipients.

    """
    def __init__(self):
        """Prepares containers for running median by zip and median by date.
        
        Dictionaries for running median by zip and median by date respectively.
        """
        self.zip_track = {}
        self.date_track = {}
        pass

    def parse_single_entry(self, line):
        """Given a line of input, returns runing median and record data.

        Args:
            line: a line from input file

        Returns:
            A string of cmte_id, zipcode, running median, cnt, amt separated 
            by pipe.
        """
        cmte_id, zip_code, t_dt, t_amt, other_id = extract_info_from_line(line)

        out_str = None
        if (len(other_id) > 0) or (len(cmte_id) == 0) or (len(t_amt) == 0):   
            # skip invalid inputs
            return out_str

        if t_amt[0] == '-':
            # skip negative amount, since it's not received contribution.
            return out_str

        if not check_amt(t_amt):
            return out_str
        
        if check_zip(zip_code):
            # record entry and return updated median, count, and total amount
            zip_median, zip_cnt, zip_total = self.add_zip_num(\
                    cmte_id, zip_code, t_amt)
            out_str = "|".join([cmte_id, zip_code, \
                               str(zip_median), str(zip_cnt), str(zip_total)])
            out_str += "\n"     # line terminator

        if check_date(t_dt):
            # record entry for the recipient and date combination
            self.add_date_num(\
                    cmte_id, t_dt, t_amt)

        return out_str

    def add_zip_num(self, cmte_id, zip_code, t_amt):
        """add transaction amount to the track for zip_code categorized record.

        Returns:
            a string containing running median, transaction count,
            and transaction amount.
        """
        if cmte_id not in self.zip_track:
            self.zip_track[cmte_id] = {}
        
        if zip_code not in self.zip_track[cmte_id]:
            self.zip_track[cmte_id][zip_code] = RunningMedian()

        results = self.zip_track[cmte_id][zip_code].push_and_calc(t_amt)
        return results


    def add_date_num(self, cmte_id, date, t_amt):
        """add transaction amount to the track for date categorized record.

        Args:
            cmte_id: Recipient unique id number
            date: date in a string format mmddyyyy
            t_amt: transaction amount (only non-negative values taken)
        """
        if cmte_id not in self.date_track:
            self.date_track[cmte_id] = {}

        if date not in self.date_track[cmte_id]:
            self.date_track[cmte_id][date] = StaticMedian()

        self.date_track[cmte_id][date].push(t_amt)
        return

    def calc_and_export_medianvals_by_date(self, file_handler):
        """Calculate and export median values by dates for recipients.

        Args:
            file_handler: an opened file stream for output.
        """
        for r, date_vals in sorted(self.date_track.items()):
            # for each recipient, sort date using date_to_numerical values
            for d, vals in sorted(date_vals.items(), \
                                  key=lambda dval: date_to_numerical(dval[0])):
                median, cnt, amt = \
                        vals.calc_median_and_export_vals()
                out_str = "|".join([r, d, str(median), str(cnt), str(amt)])
                out_str += "\n"
                file_handler.write(out_str)

