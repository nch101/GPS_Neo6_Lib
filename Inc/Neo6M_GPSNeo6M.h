/**
  *******************************************************************************
  * @file    Neo6M_GPSNeo6M.h
  * @author  Huy Nguyen
  * @brief   NMEA sentence parser for GPS Neo 6M header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef NEO6M_GPSNEO6M_H
#define NEO6M_GPSNEO6M_H

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Exported defines ----------------------------------------------------------*/

/**
 * @brief Enumeration structure that contains the two results of a command
*/
typedef enum __attribute__((packed))
{
    NEO6M_NOK,                  /* Not OK status */
    NEO6M_OK                    /* OK status */
} CheckStatus_t;

/**
 * @brief Enumeration structure that contains the two results of a parsing process
*/
typedef enum __attribute__((packed))
{
    PARSE_FAIL,                 /* Fail status */
    PARSE_SUCC                  /* Success status */
} ParseStatus_t;

/**
 * @brief Data structure that contains node information
*/
typedef struct Node
{
    char*         data;
    struct Node*  next;
} Node_t;

/**
 * @brief Data structure that contains all of the information about time data
*/
typedef struct
{
    uint8_t hr;                 /* Hour */
    uint8_t min;                /* Minute */
    uint8_t sec;                /* Second */
} Time_Info_t;

/**
 * @brief Data structure that contains all of the information about date data
*/
typedef struct
{
    uint8_t year;               /* Year */
    uint8_t month;              /* Month */
    uint8_t day;                /* Day */
} Date_Info_t;

/**
 * @brief Data structure that contains all of the information about coordinate data
*/
typedef struct
{
    uint32_t fracDegs;          /* Fraction of degrees */
    uint8_t degs;               /* Degrees */
    char pole;                  /* Pole */
} Coord_Info_t;

/**
 * @brief Data structure that contains all of the information about VTG (Course over ground and Ground speed) data 
*/
typedef struct
{
    uint32_t cogt;              /* Course over ground (true) */
    uint32_t sknots;            /* Speed over ground (knots) */
    uint32_t skph;              /* Speed over ground (kilometers/hour) */
} GPVTG_Info_t;

/**
 * @brief Data structure that contains all of the information about RMC (Recommended Minimum) data 
*/
typedef struct
{
    Time_Info_t time;           /* UTC time */
    Date_Info_t date;           /* Date in day, month, year format, */
    Coord_Info_t lat;           /* Latitude */
    Coord_Info_t lng;           /* Longitude */
} GPRMC_Info_t;

extern CheckStatus_t NEO6M_GPSNeo6_Api(char const* const rawMessage, void *pGPS_Neo6M);

#endif /* NEO6M_GPSNEO6M_H */
