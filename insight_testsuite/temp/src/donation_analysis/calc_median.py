# -*- coding: utf-8 -*-
"""
This module provide two containers for calculating median.

RunningMedian:
    a container to calculate running median using two heaps (priority queues).

StaticMedian:
    a container to store values and provides a method to calculate median.
"""

from heapq import heappush, heappop
import math

class RunningMedian:
    """Container for calculating running median. 

    The container maintains two heaps: one for lower half values, the other
    one for upper half values.

    Attributes:
        heap_lower: max heap constructed using negative numbers
        heap_upper: min heap using default heapq
        total_amt: total amount of received transactions
        cnt: count of received transactions
    """
    def __init__(self):
        """Initialize two heaps with empty lists, initialize values.
        """
        self.heap_lower = []
        self.heap_upper = []
        self.total_amt = 0
        self.cnt = 0

    def push(self, val):
        """Add value to the container.
        """
        val = int(val)
        self.total_amt += val
        self.cnt += 1

        if len(self.heap_upper) == 0:  # push to upper by default
            heappush(self.heap_upper, val)
        elif self.heap_upper[0] < val:  
            heappush(self.heap_upper, val)
        else:
            heappush(self.heap_lower, -val) # max heap

        # balance heaps if have different lengths
        if len(self.heap_lower)+2 == len(self.heap_upper):
            heappush(self.heap_lower, -heappop(self.heap_upper)) 
            return

        if len(self.heap_upper)+2 == len(self.heap_lower):
            heappush(self.heap_upper, -heappop(self.heap_lower))
            return

    def calc_median(self):
        """Calculate median of the stored numbers.
        """
        if len(self.heap_upper) == len(self.heap_lower):
            if len(self.heap_upper) == 0:
                return 0

            # avoids possible integer overflow, and deals with negative
            # values stored in lower heap
            val = (self.heap_upper[0] - self.heap_lower[0])*0.5;
            frac_part, int_part = math.modf(val)

            return int(int_part) + (frac_part >= 0.5)

        
        if len(self.heap_upper) > len(self.heap_lower):
            return self.heap_upper[0]

        return -self.heap_lower[0]

    def push_and_calc(self, val):
        """push a value onto the container, and retrieve median, cnt, and amt.
        """
        self.push(val)
        running_median = self.calc_median()
        return running_median, self.cnt, self.total_amt


class StaticMedian:
    """Container to export median after all input.
    """
    def __init__(self):
        """initialize container with an empty list.
        """
        self.vals = []
        self.amt = 0
        self.cnt = 0

    def push(self, val):
        """add one element into container and update attributes.
        """
        self.vals.append(int(val))
        self.cnt += 1
        self.amt += int(val)

    def calc_median(self):
        """calculate median of all values.
        """
        self.vals.sort()
        n_components = len(self.vals)
        if n_components == 0:
            return 0
        if n_components%2 == 0:
            val = 0.5 * (self.vals[n_components//2] + self.vals[n_components//2-1])
            frac_part, int_part = math.modf(val)
            return int(int_part) + (frac_part >= 0.5)
        else:
            return self.vals[n_components//2]

    def calc_median_and_export_vals(self):
        """calculate median and export median, count and total amount.
        """
        m = self.calc_median()
        return m, self.cnt, self.amt
    

