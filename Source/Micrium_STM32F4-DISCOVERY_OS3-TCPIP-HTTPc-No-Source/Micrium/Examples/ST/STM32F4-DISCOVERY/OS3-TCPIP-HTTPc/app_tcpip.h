/*
*********************************************************************************************************
*                                            APPLICATION CODE
*
*                          (c) Copyright 2008-2014; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                           STM3240G-EVAL
*                                         Evaluation Board
*
* Filename      : app_tcpip.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This file system application header file is protected from multiple pre-processor
*               inclusion through use of the TCP/IP application present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  APP_TCPIP_MODULE_PRESENT
#define  APP_TCPIP_MODULE_PRESENT


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   APP_TCPIP_MODULE
#define  APP_TCPIP_EXT
#else
#define  APP_TCPIP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <app_cfg.h>

/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/

#ifndef  APP_CFG_TCPIP_EN
#define  APP_CFG_TCPIP_EN                       DEF_DISABLED
#endif


/*
*********************************************************************************************************
*                                      CONDITIONAL INCLUDE FILES
*********************************************************************************************************
*/

#if (APP_CFG_TCPIP_EN == DEF_ENABLED)
#include  <net.h>
#include  <net_bsp.h>
#include  <net_dev_gmac.h>
#include  <net_dev_cfg.h>
#include  <net_phy.h>
#include  <net_cfg.h>
#include  <net_ascii.h>
#include  <net_ipv4.h>
#include  <net_if_ether.h>

#if  APP_CFG_DHCP_C_EN == DEF_ENABLED
#include  <dhcp-c.h>
#endif

#endif

/*
*********************************************************************************************************
*                                               DEFINES
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


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (APP_CFG_TCPIP_EN == DEF_ENABLED)
void  AppTCPIP_Init (void);
#endif

/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  APP_CFG_TCPIP_EN
#error  "APP_CFG_TCPIP_EN                                             not #define'd in 'app_cfg.h'"
#error  "                                                       [MUST be  DEF_DISABLED]           "
#error  "                                                       [     ||  DEF_ENABLED ]           "

#elif  ((APP_CFG_TCPIP_EN != DEF_DISABLED) && \
        (APP_CFG_TCPIP_EN != DEF_ENABLED ))
#error  "APP_CFG_TCPIP_EN                                       illegally #define'd in 'app_cfg.h'"
#error  "                                                       [MUST be  DEF_DISABLED]           "
#error  "                                                       [     ||  DEF_ENABLED ]           "

#endif


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : See 'MODULE  Note #1'.
*********************************************************************************************************
*/

#endif                                                          /* End of TCP/IP app module include (see Note #1).      */
