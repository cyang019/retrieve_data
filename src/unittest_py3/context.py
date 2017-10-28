import sys
import os

my_lib_dir = os.path.dirname(
                    os.path.dirname(
                        os.path.abspath(__file__)
                    )
                )

# append campaign_analysis to search path
sys.path.append(my_lib_dir)

import donation_analysis
