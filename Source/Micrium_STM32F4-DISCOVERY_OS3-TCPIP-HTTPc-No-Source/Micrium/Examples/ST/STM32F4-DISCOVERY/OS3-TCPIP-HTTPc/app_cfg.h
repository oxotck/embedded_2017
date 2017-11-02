/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2014; Micrium, Inc.; Weston, FL
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
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              on the
*                                         STM32F4DISCOVERY
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_TCPIP_EN                           DEF_ENABLED
#define  APP_CFG_HTTP_C_EN                          DEF_ENABLED
#define  APP_CFG_DHCP_C_EN                          DEF_ENABLED
#define  APP_CFG_DNS_C_EN                           DEF_ENABLED

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                      15u

#define  NET_CFG_TASK_TX_DEALLOC_PRIO                 4u

#define  HTTPc_OS_CFG_TASK_PRIO                       5u

#define  NET_CFG_TASK_TMR_PRIO                        7u
#define  NET_CFG_TASK_RX_PRIO                         13u


#define  DHCPc_OS_CFG_TASK_PRIO                       8u
#define  DHCPc_OS_CFG_TMR_TASK_PRIO                   9u

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE               2 * 1024u

#define  HTTPs_OS_CFG_INSTANCE_TASK_STK_SIZE       1024u

#define  NET_CFG_TASK_TX_DEALLOC_STK_SIZE          2048u
#define  NET_CFG_TASK_RX_STK_SIZE                  3072u
#define  NET_CFG_TASK_TMR_STK_SIZE                 2048u

#define  DHCPc_OS_CFG_TASK_STK_SIZE                 512u
#define  DHCPc_OS_CFG_TMR_TASK_STK_SIZE             512u
 
/*
*********************************************************************************************************
*                                               TCPIP
*********************************************************************************************************
*/
                                                                /* ------------ ETHERNET CONFIGURATION ---------------- */
#define  APP_CFG_TCPIP_IP_ADDR_IPv4             "10.10.1.240"
#define  APP_CFG_TCPIP_SUBNET_MASK_IPv4         "255.255.255.0"
#define  APP_CFG_TCPIP_DFLT_GATEWAY_IPv4        "10.10.1.1"


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#ifndef  TRACE_LEVEL_OFF
#define  TRACE_LEVEL_OFF                        0u
#endif

#ifndef  TRACE_LEVEL_INFO
#define  TRACE_LEVEL_INFO                       1u
#endif

#ifndef  TRACE_LEVEL_DBG
#define  TRACE_LEVEL_DBG                        2u
#endif

#include <cpu.h>

#define  APP_TRACE_LEVEL                        TRACE_LEVEL_INFO

#define  APP_TRACE                              printf

#define  IPERF_TRACE_LEVEL                      TRACE_LEVEL_OFF
#define  IPERF_TRACE                            App_SerPrintf

#define  APP_TRACE_INFO(x)               ((APP_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                ((APP_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_TRACE x) : (void)0)

#endif
