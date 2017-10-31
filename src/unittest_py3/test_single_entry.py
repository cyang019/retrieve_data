import unittest
from . import context

from donation_analysis import NotEnoughFields
from donation_analysis import Record, extract_info_from_line

class TestExtractLineInfo(unittest.TestCase):
    """Test methods related to processing a single line of input.
    """

    @classmethod
    def setUpClass(cls):
        """Define two input entries for testing.
        """
        # input with non-zero other_id
        cls.input_str1 =("C00629618|N|TER|P|201701230300133512|"
                        "15C|IND|PEREZ, JOHN A|LOS ANGELES|CA|"
                        "90017|PRINCIPAL|DOUBLE NICKEL ADVISORS|"
                        "01032017|40|H6CA34245|SA01251735122|"
                        "1141239|||2012520171368850783")
        
        # input with empty other_id
        cls.input_str2 = ("C00177436|N|M2|P|201702039042410893|15|IND|"
                         "SABOURIN, JAMES|LOOKOUT MOUNTAIN|GA|307502818|"
                         "UNUM|SVP, CORPORATE COMMUNICATIONS|01312017|"
                         "230||PR1890575345050|1147350||"
                         "P/R DEDUCTION ($115.00 BI-WEEKLY)|"
                         "4020820171370029335")
        # test hand written input
        cls.input_str3 = ("C0001011|A|B|C|D|E|F|G|H|I|02139|K|L|"
                          "09062016|3001||M|N|O")

    def test_empty_input(self):
        self.assertRaises(NotEnoughFields,\
                extract_info_from_line, "")

    def test_correct_input_1(self):
        cmte_id, zipcode, t_dt, t_amt, other_id = \
                extract_info_from_line(self.input_str1)
        self.assertEqual("C00629618", cmte_id)
        self.assertEqual("90017", zipcode)
        self.assertEqual("01032017", t_dt)
        self.assertEqual("40", t_amt)
        self.assertEqual("H6CA34245", other_id)
    
    def test_correct_input_2(self):
        cmte_id, zipcode, t_dt, t_amt, other_id = \
                extract_info_from_line(self.input_str2)
        self.assertEqual("C00177436", cmte_id)
        self.assertEqual("30750", zipcode)
        self.assertEqual("01312017", t_dt)
        self.assertEqual("230", t_amt)
        self.assertEqual("", other_id)

    def test_correct_input_3(self):
        cmte_id, zipcode, t_dt, t_amt, other_id = \
                extract_info_from_line(self.input_str3)
        self.assertEqual("C0001011", cmte_id)
        self.assertEqual("02139", zipcode)
        self.assertEqual("09062016", t_dt)
        self.assertEqual("3001", t_amt)
        self.assertEqual("", other_id)



if __name__ == '__main__':
    unittest.main()
