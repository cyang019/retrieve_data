import unittest
import context

from donation_analysis import check_zip, check_date, date_to_numerical

class TestCheckers(unittest.TestCase):
    """Test methods related to validating input.
    """

    def test_check_zip(self):
        self.assertEqual(True, check_zip("12345"))
        self.assertEqual(False, check_zip("12b45"))
        self.assertEqual(False, check_zip("88"))

    def test_check_date(self):
        self.assertEqual(True, check_date('01032015'))
        self.assertEqual(True, check_date('10152018'))
        self.assertEqual(True, check_date('09222017'))
        self.assertEqual(False, check_date('21032015'))
        self.assertEqual(False, check_date('210315'))
        self.assertEqual(False, check_date('013315'))
        self.assertEqual(False, check_date('023a2012'))

    

if __name__ == '__main__':
    unittest.main()
