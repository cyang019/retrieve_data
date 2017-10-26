import sys
import os

repo_dir = os.path.dirname(
    os.path.dirname(
        os.path.dirname(
            os.path.dirname(
                os.path.abspath(__file__)
                )
            )
        )
    )

# append campaign_analysis to search path
my_lib_dir = os.path.join(repo_dir, "src")
sys.path.append(my_lib_dir)

import donation_analysis
