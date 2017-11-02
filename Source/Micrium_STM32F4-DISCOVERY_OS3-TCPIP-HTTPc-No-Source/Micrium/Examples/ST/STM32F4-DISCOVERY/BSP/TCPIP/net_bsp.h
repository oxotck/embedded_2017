/*
*********************************************************************************************************
*                                             uC/TCP-IP V3
*                                      The Embedded TCP/IP Suite
*
*                          (c) Copyright 2003-2014; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/TCP-IP is provided in source form to registered licensees ONLY.  It is 
*               illegal to distribute this source code to any third party unless you receive 
*               written permission by an authorized Micrium representative.  Knowledge of 
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest 
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                            NETWORK BOARD SUPPORT PACKAGE (BSP) FUNCTIONS
*
*                                     ST Microelectronics STM32
*                                              on the
*                                         STM32F4DISCOVERY
*
* Filename      : net_bsp.h
* Version       : V3.00
* Programmer(s) : ITJ
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <net.h>
#include  <net_if.h>
#include  <net_if_ether.h>
#include  <net_cfg.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_BSP_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_BSP_EXT
#else
#define  NET_BSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                           NETWORK BOARD SUPPORT PACKAGE (BSP) ERROR CODES
*
* Note(s) : (1) ALL BSP-independent error codes #define'd in      'net_err.h';
*               ALL BSP-specific    error codes #define'd in this 'net_bsp.h'.
*
*           (2) Network error code '10000' series reserved for network BSP errors.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

#ifdef  NET_IF_ETHER_MODULE_EN
extern  const  NET_DEV_BSP_ETHER  NetDev_BSP_STM32F4xx;
#endif


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

