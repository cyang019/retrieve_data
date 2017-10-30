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
        self.cnt = 0
        self.amt = 0

    def push(self, val):
        """add one element into container and update attributes.
        """
        val = int(val)
        self.vals.append(val)
        self.cnt += 1
        self.amt += val

    def calc_median(self):
        """Calculate median of an array.
        
        If has more than 6 elements and only need to find center, 
        use quick select. Otherwise sort first then select
        """
        return self.calc_median_default()
        #if (self.cnt > 6) and (self.cnt%2 == 1):
        #    return self.calc_median_quick_select()
        #else:
        #    return self.calc_median_default()

    def calc_median_and_export_vals(self):
        """calculate median and export median, count and total amount.
        """
        m = self.calc_median()
        return m, self.cnt, self.amt

    def calc_pivot(self, left, right):
        """calculate pivots by median of three.
        """
        pivots = [[self.vals[left], left],\
                  [self.vals[(right+left+1)//2], (right+left+1)//2],\
                  [self.vals[right], right]]
        pivots.sort(key=lambda tup:tup[0])
        return pivots[1][1]

    def partition(self, left, right, pivot):
        """calculate partition of the mid range with same value as pivot.

        Returns:
            indexLeft: index where value pivot begins
            indexRight: index where value pivot ends
        """
        pivot_val = self.vals[pivot]
        # swap pivot to the right
        self.vals[pivot], self.vals[right] = self.vals[right], self.vals[pivot]
        indexLeft = left
        for i in range(left, right):
            if self.vals[i] < pivot_val:
                if i == indexLeft:
                    pass
                else:
                    # swap smaller values to the left of pivot
                    self.vals[i], self.vals[indexLeft] = \
                            self.vals[indexLeft], self.vals[i]
                indexLeft += 1
        self.vals[indexLeft], self.vals[right] = \
                self.vals[right], self.vals[indexLeft]
        indexRight = indexLeft
        # look for the range of same values as pivot
        for j in range(indexLeft+1, right):
            if self.vals[j] == pivot_val:
                indexRight += 1
                if j == indexRight:
                    pass
                else:
                    self.vals[j], self.vals[indexRight] = \
                            self.vals[indexRight], self.vals[j]
        return indexLeft, indexRight

    def select_n(self, left, right, n):
        """select the nth element. (deals with repeat values as well)
        """
        while True:
            if left == right:
                return left 
            pivot = self.calc_pivot(left, right)
            left_idx, right_idx = self.partition(left, right, pivot)
            if left_idx <= n <= right_idx:
                return left_idx
            elif n < left_idx:
                right = left_idx - 1
            else:
                left = right_idx + 1

    def select_mid_2(self, left, right, n):
        """select the nth, and (n-1)th elements.
        """
        pos1 = self.select_n(left, right, n-1)
        left = pos1 + 1
        while True:
            if left == right:
                return left 
            pivot = left # lower part already sorted
            left_idx, right_idx = self.partition(left, right, pivot)
            if left_idx <= n <= right_idx:
                return left_idx
            elif n < left_idx:
                right = left_idx - 1
            else:
                left = right_idx + 1

        val = 0.5 * (self.vals[pos1] + self.vals[pos2])
        frac_part, int_part = math.modf(val)
        return int(int_part) + (frac_part >= 0.5)

    def calc_median_quick_select(self):
        """ calculate median by partial quick sort.
        """
        if self.cnt == 0:
            return 0

        if self.cnt%2 == 1:
            return self.select_n(0, self.cnt-1, self.cnt//2)
        else:
            # return average of n/2 and n/2-1
            return self.select_mid_2(0, self.cnt-1, self.cnt//2)

    def calc_median_default(self):
        """calculate median of all values by sorting first.

        The time complexity of this one ~ nlog(n)
        """
        n_components = len(self.vals)
        if n_components == 0:
            return 0
        if n_components == 1:
            return self.vals[0]
        self.vals.sort()
        if n_components%2 == 0:
            val = 0.5 * (self.vals[n_components//2] + self.vals[n_components//2-1])
            frac_part, int_part = math.modf(val)
            return int(int_part) + (frac_part >= 0.5)
        else:
            return self.vals[n_components//2]

    

