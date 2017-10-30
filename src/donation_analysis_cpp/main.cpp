#include "donation_analysis.h"
#include <string>
#include <iostream>
#include <iomanip>  // setprecision
#include <fstream>  // ifstream, ofstream
#include <ctime>    // clock

using namespace std;

int main(int argc, char **argv)
{
    /// need input_filename, output_by_zip, and output_by_date
    if(argc < 4) return 1;

    /// time the execution
    clock_t c_start = clock();


    donation_analysis::Record r;
    
    ifstream istrm(argv[1], std::ios::in);
    string line;
    ofstream ostrm_zip(argv[2], std::ios::out);
    while(getline(istrm, line)){
        const string by_zip_str = r.parse_single_entry(line);
        if(!by_zip_str.empty()){
            ostrm_zip << by_zip_str << endl;
        }
    }
    ostrm_zip.close();
    istrm.close();

    ofstream ostrm_date(argv[3], std::ios::out);
    r.calc_and_export_medianvals_by_date(ostrm_date);
    ostrm_date.close();

    clock_t c_end = clock();
    std::cout << std::setprecision(4) << " --- CPU time used: "
              << 1.0 * (c_end - c_start)/ CLOCKS_PER_SEC << " s ---\n";
    return 0;
}
