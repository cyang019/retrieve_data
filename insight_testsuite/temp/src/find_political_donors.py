import sys
import os
import argparse
import time
from donation_analysis import Record

def main():
    """main function for parsing transactions entries line by line.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument(
            "input_filename", help="transaction data input")
    parser.add_argument(
            "output_by_zip_filename", help="running median output by zip code")
    parser.add_argument(
            "output_by_date_filename", help="median by date for summary output")
    args = parser.parse_args()

    r = Record()
    with open(args.input_filename, 'r') as f:
        f_out_running = open(args.output_by_zip_filename, "a+")
        for line in f:
            output_str = r.parse_single_entry(line) 
            if output_str:
                f_out_running.write(output_str)
        f_out_running.close()

        with open(args.output_by_date_filename, "a+") as f_date:
            summary_str = r.calc_and_export_medianvals_by_date(f_date)

    return

if __name__ == "__main__":
    begin_time = time.time()
    main()
    print("------ %s seconds ------" % (time.time() - begin_time))
