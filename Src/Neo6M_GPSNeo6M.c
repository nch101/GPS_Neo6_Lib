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
#define MAX_HEADER_SIZE                     8       /* Max header size */
#define MAX_GPVTG_FIELD                     9       /* Max VTG data field */
#define MAX_GPVTG_LENGTH                    15      /* Max VTG data length */

/* Private functions ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @brief  This function validates the header in the raw message, matching the expected header.
  * @param  rawMessage          Pointer to string read by UART
  * @param  expectedHeader      Expected header string
  * @retval NEO6M_OK if headers match, NEO6M_NOK if they don't
  */
CheckStatus_t NEO6M_CheckHeaderMsg(char const* const rawMessage, char const* const expectedHeader)
{
    char header[MAX_HEADER_SIZE] = {};
    uint8_t index;

    for (index = 0U; index < MAX_HEADER_SIZE; index++)
    {
        /* Check if field has ended */
        if (rawMessage[index] == ',')
        {
            header[index] = '\0';
            break;
        }

        /* Store character indexth into header */
        header[index] = rawMessage[index];
    }

    return (strcmp(expectedHeader, &header[1]) == 0 ? NEO6M_OK : NEO6M_NOK);
}

/**
  * @brief  Sets the priority of an interrupt.
  * @param  rawMessage          Pointer to string read by UART
  * @param  pGPVTG_Info         Pointer to GPVTG_Info_t struct
  * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
  */
ParseStatus_t NEO6M_ParseGPVTG(char const* const rawMessage, GPVTG_Info_t* pGPVTG_Info)
{
    char buffer[MAX_GPVTG_FIELD][MAX_GPVTG_LENGTH] = {};
    uint8_t index, fieldIndex, dataIndex;
    ParseStatus_t status;

    /* Set field index and data index to 0 */
    fieldIndex  = 0U;
    dataIndex   = 0U;
    status      = PARSE_FAIL;

    for (index = 7U; index < MAX_RAW_STRING_LENGTH; index++)
    {
        if (rawMessage[index] == '\n')
        {
            /* Break the loop */
            break;
        }

        /* Check if field has ended */
        if (rawMessage[index] == ',')
        {
            buffer[fieldIndex][dataIndex] = '\0';

            /* Increase field no */
            fieldIndex++;
            /* Reset data index to 0 */
            dataIndex = 0;
        }
        else
        {
            buffer[fieldIndex][dataIndex] = rawMessage[index];

            /* Increase data index */
            dataIndex++;
        }
    }

    if (buffer[8][0] == 'A')
    {
        pGPVTG_Info->cogt   = strtof((char *)&buffer[0], NULL);
        pGPVTG_Info->sknots = strtof((char *)&buffer[4], NULL);
        pGPVTG_Info->skph   = strtof((char *)&buffer[6], NULL);

        status = PARSE_SUCC;
    }
    else
    {
        pGPVTG_Info->cogt   = 0;
        pGPVTG_Info->sknots = 0;
        pGPVTG_Info->skph   = 0;
    }

    return status;
}
