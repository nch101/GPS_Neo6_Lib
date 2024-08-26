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

/* Private variables ---------------------------------------------------------*/
static Node_t *g_pHead          = NULL;         /* Head of linked list */
static uint8_t g_fieldNum;                      /* Current number of data field */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief      This function inserts a string into a node.
  * @param[in]  str                 Pointer to string
  * @param[in]  dataLen             Length of string
  * @retval     NEO6M_OK if ok, NEO6M_NOK if not
  */
static CheckStatus_t NEO6M_InsertToNode(char const* const str, const uint8_t dataLen)
{
    Node_t *dataNode;
    CheckStatus_t status    = NEO6M_NOK;

    /* Allocate memory for a dataNode */
    dataNode = (Node_t *) malloc(sizeof(Node_t));

    /* Check if dataNode is allocated success or not */
    if (dataNode != NULL)
    {
        /* Allocate memory for buffer */
        dataNode->data  = (char *) calloc(sizeof(char), dataLen + 1U);

        /* Check if data is allocated success or not */
        if (dataNode->data != NULL)
        {
            /* Copy data from str to buffer */
            (void) strncpy(dataNode->data, str, dataLen);

            /* Point new node to old node */
            dataNode->next = g_pHead;

            /* Point head to new node */
            g_pHead = dataNode;

            /* Increase data field index */
            g_fieldNum++;

            /* Update status to OK */
            status  = NEO6M_OK;
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* Do nothing */
    }

    return status;
}

/**
  * @brief      This function gets data of node from list by index.
  * @param[in]  nodeIndex           Index of node
  * @retval     Pointer to data node
  */
static char* NEO6M_GetDataByIndex(const uint8_t nodeIndex)
{
    Node_t *dataNode        = g_pHead;
    uint8_t index;

    for (index = 0; index < (g_fieldNum - 1U - nodeIndex); index++)
    {
        dataNode = dataNode->next;
    }

    return dataNode->data;
}

/**
  * @brief      This function frees node in list.
  * @retval     None
  */
static void NEO6M_FreeList(void)
{
    Node_t *pCurNode;

    while (g_pHead != NULL)
    {
        pCurNode = g_pHead;

        g_pHead    = g_pHead->next;

        free(pCurNode->data);
        free(pCurNode);
    }

    g_fieldNum = 0U;
}

/**
  * @brief      This function converts a number as a string to a number.
  * @param[in]  str                 Pointer to string
  * @retval     Unsigned integer
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

        str2int = (uint8_t) str[index] - (uint8_t) '0';
        number  = (number * 10U) + str2int;
    }

    return number;
}

/**
  * @brief      This function converts a time as a string to time format.
  * @param[in]  str                 Pointer to string
  * @retval     Time_Info_t
  */
static Time_Info_t NEO6M_ConvertStr2TimeFormat(char const* const str)
{
    Time_Info_t curr_time = (Time_Info_t){0, 0, 0};
    uint8_t  str2uint8;
    uint8_t  index;

    for (index = 0; index < 6U; index++)
    {
        if ((str[index] < '0') || (str[index] > '9'))
        {
            /* Not a number. Set time to max value and break the loop */
            curr_time = (Time_Info_t){255, 255, 255};
            break;
        }

        str2uint8 = (uint8_t)str[index] - (uint8_t)'0';

        if (index < 2U)
        {
            curr_time.hr = (curr_time.hr * 10U) + str2uint8;
        }
        else if (index < 4U)
        {
            curr_time.min = (curr_time.min * 10U) + str2uint8;
        }
        else
        {
            curr_time.sec = (curr_time.sec * 10U) + str2uint8;
        }
    }

    return curr_time;
}

/**
  * @brief      This function converts a date as a string to date format.
  * @param[in]  str                 Pointer to string
  * @retval     Date_Info_t
  */
static Date_Info_t NEO6M_ConvertStr2DateFormat(char const* const str)
{
    Date_Info_t date = (Date_Info_t){0, 0, 0};
    uint8_t  str2uint8;
    uint8_t  index;

    for (index = 0; index < 6U; index++)
    {
        if ((str[index] < '0') || (str[index] > '9'))
        {
            /* Not a number. Set time to max value and break the loop */
            date = (Date_Info_t){255, 255, 255};
            break;
        }

        str2uint8 = (uint8_t)str[index] - (uint8_t)'0';

        if (index < 2U)
        {
            date.day = (date.day * 10U) + str2uint8;
        }
        else if (index < 4U)
        {
            date.month = (date.month * 10U) + str2uint8;
        }
        else
        {
            date.year = (date.year * 10U) + str2uint8;
        }
    }

    return date;
}

/**
  * @brief      This function converts a date as a string to coordinate format.
  * @param[in]  str                 Pointer to string
  * @param[in]  pole                Pointer to string
  * @retval     Date_Info_t
  */
static Coord_Info_t NEO6M_ConvertStr2Coord(char const* const str, char const* const pole)
{
    Coord_Info_t coord = (Coord_Info_t){0, 0, 'I'};
    uint32_t fracDegs  = 0;
    uint8_t  str2uint8;
    uint8_t  index;

    if ((pole[0] != 'N')
        && (pole[0] != 'E')
        && (pole[0] != 'W')
        && (pole[0] != 'S')
    )
    {
        coord = (Coord_Info_t){255, 255, 'I'};
    }
    else 
    {
        coord.pole = pole[0];

        for (index = 0; index < strlen(str); index++)
        {
            if (str[index] == '.')
            {
                continue;
            }

            if ((str[index] < '0')
                || (str[index] > '9')
            )
            {
                /* Invalid data. Break the loop */
                coord = (Coord_Info_t){255, 255, 'I'};
                break;
            }

            str2uint8 = (uint8_t)str[index] - (uint8_t)'0';
            
            if ((pole[0] == 'N') || (pole[0] == 'S'))
            {
                if (index > 1U)
                {
                    fracDegs = (fracDegs * 10U) + str2uint8;
                }
                else
                {
                    coord.degs = (coord.degs * 10U) + str2uint8;
                }
            }
            else if ((pole[0] == 'E') || (pole[0] == 'W'))
            {
                if (index > 2U)
                {
                    fracDegs = (fracDegs * 10U) + str2uint8;
                }
                else
                {
                    coord.degs = (coord.degs * 10U) + str2uint8;
                }
            }
            else
            {
                /* Do nothing */
            }
        }

        if (coord.pole != 'I')
        {
            coord.fracDegs = fracDegs / 60U;
        }
    }

    return coord;
}

/**
  * @brief      This function validates the header in the raw message, matching the expected header.
  * @param[in]  headerMsg           Pointer to header from buffer
  * @param[in]  expectedHeader      Expected header string
  * @retval     NEO6M_OK if headers match, NEO6M_NOK if they don't
  */
static CheckStatus_t NEO6M_CheckHeaderMsg(char const* const headerMsg, char const* const expectedHeader)
{
    return ((strcmp(expectedHeader, &headerMsg[1]) == 0) ? NEO6M_OK : NEO6M_NOK);
}

/**
  * @brief      This function parses raw message, then put it into buffer.
  * @param[in]  rawMessage          Pointer to string read by UART
  * @retval     PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
  */
static ParseStatus_t NEO6M_ParseGPSMsg(char const* const rawMessage)
{
    ParseStatus_t status    = PARSE_FAIL;

    uint8_t index;
    uint8_t beginDataIndex  = 0U;
    uint8_t dataLength      = 0U;

    for (index = 0U; index < MAX_RAW_STRING_LENGTH; index++)
    {
        if (rawMessage[index] == '\r')
        {
            /* Insert raw message block to buffer */
            status = ((NEO6M_InsertToNode(&rawMessage[beginDataIndex], dataLength) == NEO6M_OK) ? PARSE_SUCC : PARSE_FAIL);

            /* Break the loop */
            break;
        }
        else if (rawMessage[index] == ',')
        {
            /* Insert raw message block to buffer */
            status = ((NEO6M_InsertToNode(&rawMessage[beginDataIndex], dataLength) == NEO6M_OK) ? PARSE_SUCC : PARSE_FAIL);

            /* Reset data length to 0 */
            dataLength = 0U;

            /* Reset begin index of data */
            beginDataIndex = index + 1U;
        }
        else
        {
            /* Increase data length */
            dataLength++;
        }
    }

    return status;
}

/**
  * @brief      Function that makes the parsing of the GPVTG string.
  * @param[out] pGPVTG_Info         Pointer to GPVTG_Info_t struct
  * @retval     PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
  */
static ParseStatus_t NEO6M_ParseGPVTG(GPVTG_Info_t* pGPVTG_Info)
{
    ParseStatus_t status    = PARSE_FAIL;

    (void) memset(pGPVTG_Info, 0, sizeof(GPVTG_Info_t));

    if (NEO6M_GetDataByIndex(9)[0] == 'A')
    {
        pGPVTG_Info->cogt   = NEO6M_ConvertStr2Uint32(NEO6M_GetDataByIndex(1));
        pGPVTG_Info->sknots = NEO6M_ConvertStr2Uint32(NEO6M_GetDataByIndex(5));
        pGPVTG_Info->skph   = NEO6M_ConvertStr2Uint32(NEO6M_GetDataByIndex(7));

        status = PARSE_SUCC;
    }

    return status;
}

/**
  * @brief      Function that makes the parsing of the GPRMC string.
  * @param[out] pGPRMC_Info         Pointer to GPRMC_Info_t struct
  * @retval     PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
  */
static ParseStatus_t NEO6M_ParseGPRMC(GPRMC_Info_t* pGPRMC_Info)
{
    ParseStatus_t status    = PARSE_FAIL;

    (void)memset(pGPRMC_Info, 0, sizeof(GPRMC_Info_t));

    if (NEO6M_GetDataByIndex(2)[0] == 'A')
    {
        pGPRMC_Info->time   = NEO6M_ConvertStr2TimeFormat(NEO6M_GetDataByIndex(1));
        pGPRMC_Info->date   = NEO6M_ConvertStr2DateFormat(NEO6M_GetDataByIndex(9));
        pGPRMC_Info->lat    = NEO6M_ConvertStr2Coord(NEO6M_GetDataByIndex(3), NEO6M_GetDataByIndex(4));
        pGPRMC_Info->lng    = NEO6M_ConvertStr2Coord(NEO6M_GetDataByIndex(5), NEO6M_GetDataByIndex(6));

        status = PARSE_SUCC;
    }

    return status;
}

/* Exported functions --------------------------------------------------------*/

/**
  * @brief      GPS Neo 6M Api function.
  * @param[in]  rawMessage          Pointer to string read by UART
  * @param[out] pGPS_Neo6M          Pointer to void struct
  * @retval     NEO6M_OK if OK, NEO6M_NOK if not
  */
CheckStatus_t NEO6M_GPSNeo6_Api(char const* const rawMessage, void *pGPS_Neo6M)
{
    CheckStatus_t status = NEO6M_NOK;

    if (NEO6M_ParseGPSMsg(rawMessage) != PARSE_FAIL)
    {
        if (NEO6M_CheckHeaderMsg(NEO6M_GetDataByIndex(0), "GPVTG") == NEO6M_OK)
        {
            status = ((NEO6M_ParseGPVTG((GPVTG_Info_t*)pGPS_Neo6M) == PARSE_SUCC) ? NEO6M_OK : NEO6M_NOK);
        }
        else if (NEO6M_CheckHeaderMsg(NEO6M_GetDataByIndex(0), "GPRMC") == NEO6M_OK)
        {
            status = ((NEO6M_ParseGPRMC((GPRMC_Info_t*)pGPS_Neo6M) == PARSE_SUCC) ? NEO6M_OK : NEO6M_NOK);
        }
        else
        {
            /* Do nothing */
        }
    }

    /* Clean list */
    NEO6M_FreeList();

    return status;
}
