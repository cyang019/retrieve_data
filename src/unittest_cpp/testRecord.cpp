#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <tuple>
#include "donation_analysis.h"
#include "gtest/gtest.h"

TEST(TestRecord, Checkers){
    using namespace donation_analysis;
    
    EXPECT_TRUE(checkDate("01312017"));
    EXPECT_FALSE(checkDate("12345"));
    EXPECT_FALSE(checkDate("123456789"));
    EXPECT_FALSE(checkDate("1a232015"));

    EXPECT_TRUE(checkZipcode("12345"));
    EXPECT_FALSE(checkZipcode("5432"));
    EXPECT_FALSE(checkZipcode("ab124"));
    EXPECT_TRUE(checkZipcode("90223545"));
}

TEST(TestRecord, DefaultValues){
    donation_analysis::Record r;
    std::string zip_str = r.parse_single_entry("");
    EXPECT_EQ("", zip_str);

    std::stringstream oss;
    r.calc_and_export_medianvals_by_date(oss);
    std::string date_str = oss.str();
    EXPECT_EQ("", date_str);
}

TEST(TestRecord, Entry1){
    donation_analysis::Record r;

    std::string str1 = "C12345||||||||||02139|||10012015|342||";
    std::string zip_str = r.parse_single_entry(str1);
    EXPECT_EQ("C12345|02139|342|1|342", zip_str);

    std::stringstream ostrm;
    r.calc_and_export_medianvals_by_date(ostrm);
    std::string date_str = ostrm.str();
    EXPECT_EQ("C12345|10012015|342|1|342\n", date_str);
}

TEST(TestRecord, Entry2){
    donation_analysis::Record r;

    std::string str2 = "C00003418|N|M4|P|201704209052369404|32|IND"
        "|KOHORST, W. ROBERT MR.|PASADENA|CA|911012452|EVEREST PROPERTIES"
        "|PRESIDENT|09262016|10000||SA.68234880.21.0317|1159644|X"
        "|CONTRIBUTION MEMO OF TRUMP VICTORY COMMITTEE JFC TRANSFER"
        "|4042420171400267731";
    std::string zip_str = r.parse_single_entry(str2);
    EXPECT_EQ("C00003418|91101|10000|1|10000", zip_str);

    std::stringstream ostrm;
    r.calc_and_export_medianvals_by_date(ostrm);
    std::string date_str = ostrm.str();
    EXPECT_EQ("C00003418|09262016|10000|1|10000\n", date_str);
}

TEST(TestRecord, FourEntries){
    donation_analysis::Record r;

    std::string str1 = "C00562264|N|M4|P|201704209052366693|15|IND|DALY, CHRISTOPHER|TARRYTOWN|NY|10591|REGENERON PHARMACEUTICALS INC.|SR. DIRECTOR - ONCOLOGY & ANGIOGENESIS|03312017|288||SA11AI.5014|1159642|||4042420171400274287";
    std::string str2 = "C00562264|N|M4|P|201704209052366694|15|IND|FAIRHURST, JEANETTE|TARRYTOWN|NY|10591|REGENERON PHARMACEUTICALS INC.|SENIOR MANAGER-THERAPEUTIC ANTIBODIES|03312017|150||SA11AI.5023|1159642|||4042420171400274288";
    std::string str3 = "C00034470|N|M4|P|201704209052347084|15|IND|WALLET, STEVEN A.|MONROE|CT|06468|DIAGEO|EXECUTIVE|03152017|70||SA11AI.28475|1159442|||4042020171400066574";
    std::string str4 = "C00003418|N|M4|P|201704209052369404|32|IND|KOHORST, W. ROBERT MR.|PASADENA|CA|911012452|EVEREST PROPERTIES|PRESIDENT|09262016|10000||SA.68234880.21.0317|1159644|X|CONTRIBUTION MEMO OF TRUMP VICTORY COMMITTEE JFC TRANSFER|4042420171400267731";

    std::string zip_str = r.parse_single_entry(str1);
    EXPECT_EQ("C00562264|10591|288|1|288", zip_str);
    zip_str = r.parse_single_entry(str2);
    EXPECT_EQ("C00562264|10591|219|2|438", zip_str);
    zip_str = r.parse_single_entry(str3);
    EXPECT_EQ("C00034470|06468|70|1|70", zip_str);
    zip_str = r.parse_single_entry(str4);
    EXPECT_EQ("C00003418|91101|10000|1|10000", zip_str);

    std::stringstream ostrm;
    r.calc_and_export_medianvals_by_date(ostrm);
    std::string date_str = ostrm.str();
    std::string ans = "C00003418|09262016|10000|1|10000\n"
                      "C00034470|03152017|70|1|70\n"
                      "C00562264|03312017|219|2|438\n";
    EXPECT_EQ(ans, date_str);
}

