#!/usr/bin/env python3

import argparse

def show_diff_lines(file1, file2):
    """show differences of two files line by line.

    Arguments:
        file1: filename of first file for comparison
        file2: filename of second file for comparison
    """
    f1 = open(file1, 'r')
    f2 = open(file2, 'r')

    for i, lines in enumerate(zip(f1, f2)):
        line1, line2 = lines
        if line1 == line2:
            continue
        else:
            print("[%d] --- diff ---" % i)
            print("[%d]%s: %s" % (i, file1, line1))
            print("[%d]%s: %s" % (i, file2, line2))
            print("--- ---- ---")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("file1")
    parser.add_argument("file2")
    args = parser.parse_args()
    show_diff_lines(args.file1, args.file2)

if __name__ == '__main__':
    #print(help(show_diff_lines))
    main()
