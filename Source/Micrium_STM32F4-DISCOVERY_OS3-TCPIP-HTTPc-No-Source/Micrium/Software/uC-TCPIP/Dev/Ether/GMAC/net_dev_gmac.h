/*
*********************************************************************************************************
*                                             uC/TCP-IP
*                                      The Embedded TCP/IP Suite
*
*                         (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/TCP-IP is provided in source form to registered licensees ONLY.  It is
*                  illegal to distribute this source code to any third party unless you receive
*                  written permission by an authorized Micrium representative.  Knowledge of
*                  the source code may NOT be used to develop a similar product.
*
*                  Please help us continue to provide the Embedded community with the finest
*                  software available.  Your honesty is greatly appreciated.
*
*                  You can find our product's user manual, API reference, release notes and
*                  more information at: https://doc.micrium.com
*
*                  You can contact us at: http://www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        NETWORK DEVICE DRIVER
*
*                                            GMAC 10/100
*
* Filename      : net_dev_gmac.h
* Version       : V3.00.00.00
* Programmer(s) : AF
*                 EHS
*                 AA
*                 AP
*                 FF
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/TCP-IP V2.20.00 (or more recent version) is included in the project build.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  NET_DEV_GMAC_MODULE_PRESENT
#define  NET_DEV_GMAC_MODULE_PRESENT

#include  <IF/net_if_ether.h>

#ifdef  NET_IF_ETHER_MODULE_EN


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
* Note(s) : (1) The following MCUs are support by NetDev_API_GMAC API:
*
*                          STMicroelectronics  STM32F107xx  series
*                          STMicroelectronics  STM32F2xxx   series
*                          STMicroelectronics  STM32F4xxx   series
*                          FUJITSU             MB9BFD10T    series
*                          FUJITSU             MB9BF610T    series
*                          FUJITSU             MB9BF210T    series
*
*           (2) The following MCUs are support by NetDev_API_LPCXX_ENET API:
*
*                          NXP                 LPC185x      series
*                          NXP                 LPC183x      series
*                          NXP                 LPC435x      series
*                          NXP                 LPC433x      series
*
*********************************************************************************************************
*/

extern  const  NET_DEV_API_ETHER  NetDev_API_GMAC;
extern  const  NET_DEV_API_ETHER  NetDev_API_LPCXX_ENET;



/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif /* NET_IF_ETHER_MODULE_EN      */
#endif /* NET_DEV_GMAC_MODULE_PRESENT */

