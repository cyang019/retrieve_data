import unittest
import context

from donation_analysis import RunningMedian

class TestRunningMedian(unittest.TestCase):
    """Test methods related to calculating running median.
    """

    def test_number_sequence_1(self):
        nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        answers = [1, 2, 2, 3, 3, 4, 4, 5, 5, 6]
        cnts = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        amts = [1, 3, 6, 10, 15, 21, 28, 36, 45, 55]
        r = RunningMedian()
        for i, a, cnt, amt in zip(nums, answers, cnts, amts):
            m, calc_cnt, calc_amt = r.push_and_calc(i)
            self.assertEqual(m, a)
            self.assertEqual(cnt, calc_cnt)
            self.assertEqual(amt, calc_amt)

    def test_number_sequence_2(self):
        nums = [320, 410, 280, 300, 320, 340]
        answers = [320, 365, 320, 310, 320, 320]
        cnts = [1, 2, 3, 4, 5, 6]
        amts = [320, 730, 1010, 1310, 1630, 1970]
        r = RunningMedian()
        for i, a, cnt, amt in zip(nums, answers, cnts, amts):
            m, calc_cnt, calc_amt = r.push_and_calc(i)
            self.assertEqual(m, a)
            self.assertEqual(cnt, calc_cnt)
            self.assertEqual(amt, calc_amt)


if __name__ == '__main__':
    unittest.main()
