/**
  *******************************************************************************
  * @file    Neo6M_GPSNeo6M.c
  * @author  Huy Nguyen
  * @brief   NMEA sentence parser for GPS Neo 6M implement file
  *******************************************************************************
  * @attention
  *
  * MIT License
  * 
  * Copyright (c) 2023 Nguyễn Công Huy
  * 
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  * 
  * The above copyright notice and this permission notice shall be included in all
  * copies or substantial portions of the Software.
  * 
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  * 
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "Neo6M_GPSNeo6M.h"

/* Private define ------------------------------------------------------------*/
#define MAX_RAW_STRING_LENGTH               100U    /* Max raw string length */
#define MAX_FIELD                           20      /* Max data field */
#define MAX_LENGTH                          12      /* Max data length */

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function converts a number as a string to a number.
  * @param  str                 Pointer to string
  * @retval Unsigned integer
  */
static uint32_t NEO6M_ConvertStr2Uint32(char const* const str)
{
    uint32_t number = 0;
    uint8_t  str2int;
    uint8_t  index;

    for (index = 0; index < strlen(str); index++)
    {
        if (str[index] == '.')
        {
            continue;
        }

        if ((str[index] < '0') || (str[index] > '9'))
        {
            /* Not a number. Set number to 0 and break the loop */
            number = 0;
            break;
        }

        str2int = (uint8_t)str[index] - (uint8_t)'0';
        number  = (number*10U) + str2int;
    }

    return number;
}

/**
  * @brief  This function validates the header in the raw message, matching the expected header.
  * @param  headerMsg           Pointer to header from buffer
  * @param  expectedHeader      Expected header string
  * @retval NEO6M_OK if headers match, NEO6M_NOK if they don't
  */
static CheckStatus_t NEO6M_CheckHeaderMsg(char const* const headerMsg, char const* const expectedHeader)
{
    return ((strcmp(expectedHeader, &headerMsg[1]) == 0) ? NEO6M_OK : NEO6M_NOK);
}

/**
  * @brief  This function parses raw message, then put it into buffer.
  * @param  buffer              Pointer to buffer
  * @param  rawMessage          Pointer to string read by UART
  * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
  */
static ParseStatus_t NEO6M_ParseGPSMsg(char buffer[MAX_FIELD][MAX_LENGTH], char const* const rawMessage)
{
    uint8_t index;
    uint8_t fieldIndex      = 0U;
    uint8_t dataIndex       = 0U;

    ParseStatus_t status    = PARSE_FAIL;

    for (index = 0U; index < MAX_RAW_STRING_LENGTH; index++)
    {
        if (rawMessage[index] == '\n')
        {
            /* Break the loop */
            status = PARSE_SUCC;
            break;
        }

        /* Check if field has ended */
        if (rawMessage[index] == ',')
        {
            buffer[fieldIndex][dataIndex] = '\0';

            /* Increase field no */
            fieldIndex++;
            /* Reset data index to 0 */
            dataIndex = 0U;
        }
        else
        {
            buffer[fieldIndex][dataIndex] = rawMessage[index];

            /* Increase data index */
            dataIndex++;
        }
    }

    return status;
}

/**
  * @brief  Function that makes the parsing of the GPVTG string.
  * @param  buffer              Pointer to buffer
  * @param  pGPVTG_Info         Pointer to GPVTG_Info_t struct
  * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
  */
static ParseStatus_t NEO6M_ParseGPVTG(char buffer[MAX_FIELD][MAX_LENGTH], GPVTG_Info_t* pGPVTG_Info)
{
    ParseStatus_t status    = PARSE_FAIL;

    (void)memset(pGPVTG_Info, 0, sizeof(GPVTG_Info_t));

    if (buffer[9][0] == 'A')
    {
        pGPVTG_Info->cogt   = NEO6M_ConvertStr2Uint32((char *)&buffer[1]);
        pGPVTG_Info->sknots = NEO6M_ConvertStr2Uint32((char *)&buffer[5]);
        pGPVTG_Info->skph   = NEO6M_ConvertStr2Uint32((char *)&buffer[7]);

        status = PARSE_SUCC;
    }

    return status;
}

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  GPS Neo 6M Api function.
  * @param  rawMessage          Pointer to string read by UART
  * @param  pGPS_Neo6M          Pointer to void struct
  * @retval NEO6M_OK if OK, NEO6M_NOK if not
  */
CheckStatus_t NEO6M_GPSNeo6_Api(char const* const rawMessage, void *pGPS_Neo6M)
{
    char buffer[MAX_FIELD][MAX_LENGTH] = {0};

    CheckStatus_t status = NEO6M_NOK;

    if (NEO6M_ParseGPSMsg(buffer, rawMessage) != PARSE_FAIL)
    {
        if (NEO6M_CheckHeaderMsg(buffer[0], "GPVTG") == NEO6M_OK)
        {
            (void)NEO6M_ParseGPVTG(buffer, (GPVTG_Info_t*)pGPS_Neo6M);
            status = NEO6M_OK;
        }
    }

    return status;
}
