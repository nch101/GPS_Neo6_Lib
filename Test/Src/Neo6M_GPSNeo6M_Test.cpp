#include "gtest/gtest.h"

extern "C" {
    #include "Neo6M_GPSNeo6M.h"
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_001)
{
    char            str[] = "$GPVTG,184.34,T,,M,1.936,N,3.586,K,A*32\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 18434U);
    ASSERT_EQ(pGPVTG_Info.sknots, 1936U);
    ASSERT_EQ(pGPVTG_Info.skph, 3586U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_002)
{
    char            str[] = "$GPVTG,,T,,M,2.181,N,4.039,K,A*27\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 2181U);
    ASSERT_EQ(pGPVTG_Info.skph, 4039U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_003)
{
    char            str[] = "$GPVTG,,T,,M,2.181,N,4.039,K,D*27\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_004)
{
    char            str[] = "$GPVTG,,,,,,,,,N*30\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_005)
{
    char            str[] = "$GPGSV,2,1,05,04,,,44,08,,,41,09,,,37,21,,,26*7C\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_006)
{
    char            str[] = "$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_007)
{
    char            str[] = "$GPGGA,14212844.00,1041218.121662124145593,N,11210639.46323519,E,1,06,3.70,21.0,M,-2.6,M,,*7F23321313\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}
