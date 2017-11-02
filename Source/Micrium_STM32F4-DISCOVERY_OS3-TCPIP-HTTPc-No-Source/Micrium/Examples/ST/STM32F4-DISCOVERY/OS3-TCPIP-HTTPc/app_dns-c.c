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
*                                        DNSc INITIALIZATION
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                           STM3240G-EVAL
*                                         Evaluation Board
*
* Filename      : app_dns-c.c
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    APP_DNS_C_MODULE
#include  <app_dns-c.h>
#include  <includes.h>
#include  <net_bsp.h>
#include  <stdio.h>


/*
*********************************************************************************************************
*                                               ENABLE
*********************************************************************************************************
*/

#if (APP_CFG_DNS_C_EN == DEF_ENABLED)

/*
*********************************************************************************************************
*                                           App_DNScInit()
*
* Description :  This function initializes the uC/DNSc module.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Caller(s)   :  App_TaskStart().
*
* Note(s)     :  none.
*********************************************************************************************************
*/

CPU_BOOLEAN App_DNScInit(void)
{

    DNSc_ERR     dns_err;

#if (DNSc_CFG_MODE_ASYNC_EN == DEF_DISABLED)
    DNSc_Init(&DNSc_Cfg, DEF_NULL, &dns_err);          /* See Note #3a.                       */
#else
    DNSc_Init(&DNSc_Cfg, &DNSc_CfgTask, &dns_err);     /* See Note #3b.                       */
#endif
    if (dns_err != DNSc_ERR_NONE) {
        return (DEF_FAIL);
    }
    return (DEF_OK);
}

#endif