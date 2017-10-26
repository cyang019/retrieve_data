# -*- coding: utf-8 -*-
"""

"""


import heapq

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
    t_dt = entries[13]  # transaction date at 14th position
    t_amt = entries[14]  # transaction amount at 15th position
    other_id = entries[15]  # other identification number, should be empty for
                            # donation from individual.
    return cmte_id, zipcode, t_dt, t_amt, other_id

def check_zip(zip_code):
    """check if zip code has correct format.
    """
    return True

def check_date(date):
    """check if date string has correct format.
    """
    return True

class Record:
    """Handler for all Recipients.

    """
    def __init__(self):
        """Prepares containers for running median by zip and median by date.
        """
        pass

    def parse_single_entry(self, line):
        """Given a line of input, returns runing median and record data.
        """
        cmte_id, zip_code, t_dt, t_amt, other_id = extract_info_from_line(line)

        out_str = None
        if len(other_id) > 0:   # skip when OTHER_ID contains non-empty value
            return out_str
        
        if check_zip(zip_code):
            # record entry and return updated median, count, and total amount
            zip_median, zip_cnt, zip_total = self.add_zip_num(\
                    cmte_id, zip_code, t_amt)
            out_str = "|".join(cmte_id, zip_code, \
                               zip_median, zip_cnt, zip_total)

        if check_date(t_dt):
            # record entry for the recipient and date combination
            self.add_date_num(\
                    cmte_id, date, t_amt)
        return out_str

    def add_zip_num(self, cmte_id, zip_code, t_amt):
        pass

    def add_date_num(self, cmte_id, date, t_amt):
        pass

    def export_medianvals_by_date(self, filename):
        """
        """
        pass
