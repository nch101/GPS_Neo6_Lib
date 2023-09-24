#include "gtest/gtest.h"

extern "C" {
    #include "Neo6M_GPSNeo6M.h"
}

TEST(NEO6M_CheckHeaderMsg, Testcase_001)
{
    char            str[] = "$GPVTG,,,,,,,,,N*30\r\n";
    CheckStatus_t   status;

    status = NEO6M_CheckHeaderMsg(str, "GPVTG");

    EXPECT_EQ(status, NEO6M_OK);
}

TEST(NEO6M_CheckHeaderMsg, Testcase_002)
{
    char            str[] = "$GPV,,,,,,,,,N*30\r\n";
    CheckStatus_t   status;

    status = NEO6M_CheckHeaderMsg(str, "GPVTG");

    EXPECT_EQ(status, NEO6M_NOK);
}

TEST(NEO6M_CheckHeaderMsg, Testcase_003)
{
    char            str[] = "$GPVTGCA,,,,,,,,,N*30\r\n";
    CheckStatus_t   status;

    status = NEO6M_CheckHeaderMsg(str, "GPVTG");

    EXPECT_EQ(status, NEO6M_NOK);
}

TEST(NEO6M_CheckHeaderMsg, Testcase_004)
{
    char            str[] = "$GPGSV,4,4,14,47,10,093,42,50,44,103,35*73\r\n";
    CheckStatus_t   status;

    status = NEO6M_CheckHeaderMsg(str, "GPVTG");

    EXPECT_EQ(status, NEO6M_NOK);
}

TEST(NEO6M_CheckHeaderMsg, Testcase_005)
{
    char            str[] = "$GPGSV,4,4,14,47,10,093,42,50,44,103,35*73\r\n";
    CheckStatus_t   status;

    status = NEO6M_CheckHeaderMsg(str, "GPVTG");

    EXPECT_EQ(status, NEO6M_NOK);
}

TEST(NEO6M_ParseGPVTG, Testcase_001)
{
    char            str[] = "$GPVTG,,,,,,,,,N*30\r\n";
    GPVTG_Info_t    pGPVTG_Info;
    ParseStatus_t   status;

    status = NEO6M_ParseGPVTG(str, &pGPVTG_Info);

    EXPECT_FLOAT_EQ(pGPVTG_Info.cogt, 0);
    EXPECT_FLOAT_EQ(pGPVTG_Info.sknots, 0);
    EXPECT_FLOAT_EQ(pGPVTG_Info.skph, 0);
    EXPECT_EQ(status, PARSE_FAIL);
}

TEST(NEO6M_ParseGPVTG, Testcase_002)
{
    char            str[] = "$GPVTG,,T,,M,2.181,N,4.039,K,A*27\r\n";
    GPVTG_Info_t    pGPVTG_Info;
    ParseStatus_t   status;

    status = NEO6M_ParseGPVTG(str, &pGPVTG_Info);

    EXPECT_FLOAT_EQ(pGPVTG_Info.cogt, 0);
    EXPECT_FLOAT_EQ(pGPVTG_Info.sknots, 2.181);
    EXPECT_FLOAT_EQ(pGPVTG_Info.skph, 4.039);
    EXPECT_EQ(status, PARSE_SUCC);
}


TEST(NEO6M_ParseGPVTG, Testcase_003)
{
    char            str[] = "$GPVTG,,T,,M,0.034,N,0.062,K,A*20\r\n";
    GPVTG_Info_t    pGPVTG_Info;
    ParseStatus_t   status;

    status = NEO6M_ParseGPVTG(str, &pGPVTG_Info);

    EXPECT_FLOAT_EQ(pGPVTG_Info.cogt, 0);
    EXPECT_FLOAT_EQ(pGPVTG_Info.sknots, 0.034);
    EXPECT_FLOAT_EQ(pGPVTG_Info.skph, 0.062);
    EXPECT_EQ(status, PARSE_SUCC);
}

TEST(NEO6M_ParseGPVTG, Testcase_004)
{
    char            str[] = "$GPVTG,270.17,T,,M,3.065,N,5.677,K,A*3D\r\n";
    GPVTG_Info_t    pGPVTG_Info;
    ParseStatus_t   status;

    status = NEO6M_ParseGPVTG(str, &pGPVTG_Info);

    EXPECT_FLOAT_EQ(pGPVTG_Info.cogt, 270.17);
    EXPECT_FLOAT_EQ(pGPVTG_Info.sknots, 3.065);
    EXPECT_FLOAT_EQ(pGPVTG_Info.skph, 5.677);
    EXPECT_EQ(status, PARSE_SUCC);
}

TEST(NEO6M_ParseGPVTG, Testcase_005)
{
    char            str[] = "$GPVTG,270.17,T,,M,3.065,N,5.677,K,D*3D\r\n";
    GPVTG_Info_t    pGPVTG_Info;
    ParseStatus_t   status;

    status = NEO6M_ParseGPVTG(str, &pGPVTG_Info);

    EXPECT_FLOAT_EQ(pGPVTG_Info.cogt, 0);
    EXPECT_FLOAT_EQ(pGPVTG_Info.sknots, 0);
    EXPECT_FLOAT_EQ(pGPVTG_Info.skph, 0);
    EXPECT_EQ(status, PARSE_FAIL);
}
