#include "gtest/gtest.h"

extern "C" {
    #include "Neo6M_GPSNeo6M.h"
}

TEST(NEO6M_ParseGPSMsg, Testcase_001)
{
    char            str[] = "$GPGSV,2,1,05,04,,,44,08,,,41,09,,,37,21,,,26*7C\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPSMsg, Testcase_002)
{
    char            str[] = "$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPSMsg, Testcase_003)
{
    char            str[] = "$GPGGA,14212844.00,1041218.121662124145593,N,11210639.46323519,E,1,06,3.70,21.0,M,-2.6,M,,*7F23321313\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPSMsg, Testcase_004)
{
    char            str[] = "$GPGSV,2,1,05,04,,,44,08,,,41,09,,,37,21,,,26*7C\r\n";
    GPRMC_Info_t    pGPRMC_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPRMC_Info);

    ASSERT_EQ(pGPRMC_Info.time.hr, 0U);
    ASSERT_EQ(pGPRMC_Info.time.min, 0U);
    ASSERT_EQ(pGPRMC_Info.time.sec, 0U);
    ASSERT_EQ(pGPRMC_Info.date.day, 0U);
    ASSERT_EQ(pGPRMC_Info.date.month, 0U);
    ASSERT_EQ(pGPRMC_Info.date.year, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.pole, 0);
    ASSERT_EQ(pGPRMC_Info.lng.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.pole, 0);
}

TEST(NEO6M_ParseGPSMsg, Testcase_005)
{
    char            str[] = "$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30\r\n";
    GPRMC_Info_t    pGPRMC_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPRMC_Info);

    ASSERT_EQ(pGPRMC_Info.time.hr, 0U);
    ASSERT_EQ(pGPRMC_Info.time.min, 0U);
    ASSERT_EQ(pGPRMC_Info.time.sec, 0U);
    ASSERT_EQ(pGPRMC_Info.date.day, 0U);
    ASSERT_EQ(pGPRMC_Info.date.month, 0U);
    ASSERT_EQ(pGPRMC_Info.date.year, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.pole, 0);
    ASSERT_EQ(pGPRMC_Info.lng.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.pole, 0);
}

TEST(NEO6M_ParseGPSMsg, Testcase_006)
{
    char            str[] = "$GPGGA,14212844.00,1041218.121662124145593,N,11210639.46323519,E,1,06,3.70,21.0,M,-2.6,M,,*7F23321313\r\n";
    GPRMC_Info_t    pGPRMC_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPRMC_Info);

    ASSERT_EQ(pGPRMC_Info.time.hr, 0U);
    ASSERT_EQ(pGPRMC_Info.time.min, 0U);
    ASSERT_EQ(pGPRMC_Info.time.sec, 0U);
    ASSERT_EQ(pGPRMC_Info.date.day, 0U);
    ASSERT_EQ(pGPRMC_Info.date.month, 0U);
    ASSERT_EQ(pGPRMC_Info.date.year, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.pole, 0);
    ASSERT_EQ(pGPRMC_Info.lng.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.pole, 0);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_001)
{
    char            str[] = "$GPVTG,184.34,T,,M,1.936,N,3.586,K,A*32\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 18434U);
    ASSERT_EQ(pGPVTG_Info.sknots, 1936U);
    ASSERT_EQ(pGPVTG_Info.skph, 3586U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_002)
{
    char            str[] = "$GPVTG,,T,,M,2.181,N,4.039,K,A*27\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 2181U);
    ASSERT_EQ(pGPVTG_Info.skph, 4039U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_003)
{
    char            str[] = "$GPVTG,,T,,M,2.181,N,4.039,K,D*27\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPVTGMsg, Testcase_004)
{
    char            str[] = "$GPVTG,,,,,,,,,N*30\r\n";
    GPVTG_Info_t    pGPVTG_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPVTG_Info);

    ASSERT_EQ(pGPVTG_Info.cogt, 0U);
    ASSERT_EQ(pGPVTG_Info.sknots, 0U);
    ASSERT_EQ(pGPVTG_Info.skph, 0U);
}

TEST(NEO6M_ParseGPRMCMsg, Testcase_001)
{
    char            str[] = "$GPRMC,142754.00,A,1048.17086,N,10639.46105,E,0.034,,210923,,,A*73\r\n";
    GPRMC_Info_t    pGPRMC_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPRMC_Info);

    ASSERT_EQ(pGPRMC_Info.time.hr, 14U);
    ASSERT_EQ(pGPRMC_Info.time.min, 27U);
    ASSERT_EQ(pGPRMC_Info.time.sec, 54U);
    ASSERT_EQ(pGPRMC_Info.date.day, 21U);
    ASSERT_EQ(pGPRMC_Info.date.month, 9U);
    ASSERT_EQ(pGPRMC_Info.date.year, 23U);
    ASSERT_EQ(pGPRMC_Info.lat.fracDegs, 80284U);
    ASSERT_EQ(pGPRMC_Info.lat.degs, 10U);
    ASSERT_EQ(pGPRMC_Info.lat.pole, 'N');
    ASSERT_EQ(pGPRMC_Info.lng.fracDegs, 65768U);
    ASSERT_EQ(pGPRMC_Info.lng.degs, 106U);
    ASSERT_EQ(pGPRMC_Info.lng.pole, 'E');
}

TEST(NEO6M_ParseGPRMCMsg, Testcase_002)
{
    char            str[] = "GPRMC,,V,,,,,,,,,,N*53\r\n";
    GPRMC_Info_t    pGPRMC_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPRMC_Info);

    ASSERT_EQ(pGPRMC_Info.time.hr, 0U);
    ASSERT_EQ(pGPRMC_Info.time.min, 0U);
    ASSERT_EQ(pGPRMC_Info.time.sec, 0U);
    ASSERT_EQ(pGPRMC_Info.date.day, 0U);
    ASSERT_EQ(pGPRMC_Info.date.month, 0U);
    ASSERT_EQ(pGPRMC_Info.date.year, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.pole, 0);
    ASSERT_EQ(pGPRMC_Info.lng.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.pole, 0);
}

TEST(NEO6M_ParseGPRMCMsg, Testcase_003)
{
    char            str[] = "$GPRMC,142456.00,V,,,,,,,,,,N*7D\r\n";
    GPRMC_Info_t    pGPRMC_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPRMC_Info);

    ASSERT_EQ(pGPRMC_Info.time.hr, 0U);
    ASSERT_EQ(pGPRMC_Info.time.min, 0U);
    ASSERT_EQ(pGPRMC_Info.time.sec, 0U);
    ASSERT_EQ(pGPRMC_Info.date.day, 0U);
    ASSERT_EQ(pGPRMC_Info.date.month, 0U);
    ASSERT_EQ(pGPRMC_Info.date.year, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lat.pole, 0);
    ASSERT_EQ(pGPRMC_Info.lng.fracDegs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.degs, 0U);
    ASSERT_EQ(pGPRMC_Info.lng.pole, 0);
}

TEST(NEO6M_ParseGPRMCMsg, Testcase_004)
{
    char            str[] = "$GPRMC,142700.00,A,1048.17269,N,10639.47400,E,2.408,,210923,,,A*79\r\n";
    GPRMC_Info_t    pGPRMC_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPRMC_Info);

    ASSERT_EQ(pGPRMC_Info.time.hr, 14U);
    ASSERT_EQ(pGPRMC_Info.time.min, 27U);
    ASSERT_EQ(pGPRMC_Info.time.sec, 0);
    ASSERT_EQ(pGPRMC_Info.date.day, 21U);
    ASSERT_EQ(pGPRMC_Info.date.month, 9U);
    ASSERT_EQ(pGPRMC_Info.date.year, 23U);
    ASSERT_EQ(pGPRMC_Info.lat.fracDegs, 80287U);
    ASSERT_EQ(pGPRMC_Info.lat.degs, 10);
    ASSERT_EQ(pGPRMC_Info.lat.pole, 'N');
    ASSERT_EQ(pGPRMC_Info.lng.fracDegs, 65790U);
    ASSERT_EQ(pGPRMC_Info.lng.degs, 106);
    ASSERT_EQ(pGPRMC_Info.lng.pole, 'E');
}


TEST(NEO6M_ParseGPRMCMsg, Testcase_005)
{
    char            str[] = "$GPRMC,142706.00,A,1048.17259,N,10639.47070,E,2.547,275.81,210923,,,A*62\r\n";
    GPRMC_Info_t    pGPRMC_Info = {0};

    (void)NEO6M_GPSNeo6_Api(str, &pGPRMC_Info);

    ASSERT_EQ(pGPRMC_Info.time.hr, 14U);
    ASSERT_EQ(pGPRMC_Info.time.min, 27U);
    ASSERT_EQ(pGPRMC_Info.time.sec, 6U);
    ASSERT_EQ(pGPRMC_Info.date.day, 21U);
    ASSERT_EQ(pGPRMC_Info.date.month, 9U);
    ASSERT_EQ(pGPRMC_Info.date.year, 23U);
    ASSERT_EQ(pGPRMC_Info.lat.fracDegs, 80287U);
    ASSERT_EQ(pGPRMC_Info.lat.degs, 10U);
    ASSERT_EQ(pGPRMC_Info.lat.pole, 'N');
    ASSERT_EQ(pGPRMC_Info.lng.fracDegs, 65784U);
    ASSERT_EQ(pGPRMC_Info.lng.degs, 106U);
    ASSERT_EQ(pGPRMC_Info.lng.pole, 'E');
}
