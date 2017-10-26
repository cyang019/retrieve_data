import unittest
import context

from donation_analysis import NotEnoughFields
from donation_analysis import Record, extract_info_from_line

class TestExtractLineInfo(unittest.TestCase):

    def test_empty_input(self):
        self.assertRaises(NotEnoughFields,\
                extract_info_from_line, "")


if __name__ == '__main__':
    unittest.main()
