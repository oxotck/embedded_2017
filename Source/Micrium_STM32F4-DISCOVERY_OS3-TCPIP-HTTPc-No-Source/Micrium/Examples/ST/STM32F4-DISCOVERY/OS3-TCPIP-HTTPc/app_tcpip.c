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
*                                   TCP/IP APPLICATION INITIALIZATION
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                           STM3240G-EVAL
*                                         Evaluation Board
*
* Filename      : app_tcpip.c
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    APP_TCPIP_MODULE
#include  <app_tcpip.h>
#include  <includes.h>
#include  <net_bsp.h>
#include  <stdio.h>

/*
*********************************************************************************************************
*                                               ENABLE
*********************************************************************************************************
*/

#if (APP_CFG_TCPIP_EN == DEF_ENABLED)

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_TCPIP_ADDR_LEN                     16u             /* Maximum Length of standard TCP/IP Address(s).        */


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void         AppTCPIP_PrintIPAddr  (NET_IF_NBR  if_nbr);

#if  APP_CFG_DHCP_C_EN == DEF_ENABLED
static  CPU_BOOLEAN  AppDHCPc_Init         (NET_IF_NBR  if_nbr);
#endif


/*
*********************************************************************************************************
*                                            AppTCPIP_Init()
*
* Description : Initialize uC/TCP-IP.
*
* Arguments   : perr    Pointer to variable to store NET_ERR return code.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  AppTCPIP_Init (void)
{
    NET_IF_NBR     if_nbr;
#if  APP_CFG_DHCP_C_EN != DEF_ENABLED
    NET_IPv4_ADDR  ip;
    NET_IPv4_ADDR  msk;
    NET_IPv4_ADDR  gateway;
#endif
    CPU_BOOLEAN    dhcp_init;
    NET_ERR        net_err;

                                                                /* --------------------- INIT TCPIP ------------------- */
    APP_TRACE_INFO(("===================================================================\r\n"));
    APP_TRACE_INFO(("=                       TCPIP INITIALIZATION                      =\r\n"));
    APP_TRACE_INFO(("===================================================================\r\n"));
    APP_TRACE_INFO(("Initializing TCPIP...\r\n"));
    APP_TRACE_INFO(("\r\n"));

    net_err = Net_Init(&NetRxTaskCfg,                           /* Initialize uC/TCP-IP.                                */
                       &NetTxDeallocTaskCfg,
                       &NetTmrTaskCfg);
    if (net_err != NET_ERR_NONE) {
        APP_TRACE_INFO(("Net_Init() failed w/err = %d \r\n", net_err));
        return;
    }
                                                                /* -------------- ETHERNET CONFIGURATION -------------- */
    if_nbr  = NetIF_Add((void *)&NetIF_API_Ether,               /* Ethernet  Interface API.                             */
                        (void *)&NetDev_API_GMAC,               /* STM3240G  Device API.                                */
                        (void *)&NetDev_BSP_STM32F4xx,          /* STM3240G  Device BSP.                                */
                        (void *)&NetDev_Cfg_STM32F407_0,        /* STM3240G  Device Configuration.                      */
                        (void *)&NetPhy_API_Generic,            /* Generic   Phy API.                                   */
                        (void *)&NetPhy_Cfg_STM32F407_0,        /* STM3240G  PHY Configuration.                         */
                                &net_err);
    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_Add() failed w/err = %d \r\n", net_err));
        return;
    }
                                                                /* ------------------ START IF NBR 1 ------------------ */
    NetIF_Start(if_nbr, &net_err);
    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_Start() failed w/err = %d \r\n", net_err));
        return;
    }

    NetIF_LinkStateWaitUntilUp(if_nbr, 20, 200, &net_err);
    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_LinkStateWaitUntilUp() failed w/err = %d \r\n", net_err));
        return;
    }

#if  APP_CFG_DHCP_C_EN == DEF_ENABLED
    dhcp_init = AppDHCPc_Init(if_nbr);

    if (dhcp_init != DEF_OK) {
        APP_TRACE_INFO(("App_DHCPc_Init() returned an error, uC/DHCPc is not started"));
        return;
    }
#else

    ip      = NetASCII_Str_to_IPv4((CPU_CHAR *)APP_CFG_TCPIP_IP_ADDR_IPv4, &net_err);
    msk     = NetASCII_Str_to_IPv4((CPU_CHAR *)APP_CFG_TCPIP_SUBNET_MASK_IPv4, &net_err);
    gateway = NetASCII_Str_to_IPv4((CPU_CHAR *)APP_CFG_TCPIP_DFLT_GATEWAY_IPv4, &net_err);

    (void)NetIPv4_CfgAddrAdd( if_nbr,
                              ip,
                              msk,
                              gateway,
                             &net_err);
    if (net_err != NET_IPv4_ERR_NONE) {
        APP_TRACE_INFO(("NetIPv4_CfgAddrAdd() failed w/err = %d \r\n", net_err));
        return;


    }
#endif

    AppTCPIP_PrintIPAddr(if_nbr);                               /* Get & Display IP Address                             */

    return;
}

/*
*********************************************************************************************************
*                                           AppDHCPc_Init()
*
* Description : Initialize DHCP client for specified interface.
*
* Argument(s) : if_nbr      Interface number to start DHCP management.
*
* Return(s)   : none.
*
* Caller(s)   : App_TCPIP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if  APP_CFG_DHCP_C_EN == DEF_ENABLED
static  CPU_BOOLEAN  AppDHCPc_Init (NET_IF_NBR  if_nbr)
{
    DHCPc_OPT_CODE  req_param[DHCPc_CFG_PARAM_REQ_TBL_SIZE];
    CPU_BOOLEAN     cfg_done;
    CPU_BOOLEAN     dly;
    DHCPc_STATUS    dhcp_status;
    OS_ERR          err_os;
    DHCPc_ERR       err_dhcp;


                                                                /* -------------- INITIALIZE DHCP CLIENT -------------- */
    APP_TRACE_INFO(("\r\n"));
    APP_TRACE_INFO(("===================================================================\r\n"));
    APP_TRACE_INFO(("=                       DHCPc INITIALIZATION                      =\r\n"));
    APP_TRACE_INFO(("===================================================================\r\n"));
    APP_TRACE_INFO(("Initialize DHCP client ...\n\r"));

    err_dhcp = DHCPc_Init();
    if (err_dhcp != DHCPc_ERR_NONE) {
        APP_TRACE_INFO(("DHCPc_Init() failed w/err = %d \r\n", err_dhcp));
        return (DEF_FAIL);
    }

                                                                /* ----------- START INTERFACE'S DHCP CLIENT ---------- */
    req_param[0] = DHCP_OPT_DOMAIN_NAME_SERVER;

    DHCPc_Start((NET_IF_NBR      ) if_nbr,
                (DHCPc_OPT_CODE *)&req_param[0],
                (CPU_INT08U      ) 1u,
                (DHCPc_ERR      *)&err_dhcp);
    if (err_dhcp != DHCPc_ERR_NONE) {
        APP_TRACE_INFO(("DHCPc_Start() failed w/err = %d \r\n", err_dhcp));
        return (DEF_FAIL);
    }

    APP_TRACE_INFO(("DHCP address configuration started\n\r"));

                                                                /* ------ CHECK INTERFACE'S DHCP CONFIGURE STATUS ----- */
    dhcp_status = DHCP_STATUS_NONE;
    cfg_done    = DEF_NO;
    dly         = DEF_NO;

    while (cfg_done != DEF_YES) {
        if (dly == DEF_YES) {
            OSTimeDlyHMSM((CPU_INT16U) 0u,
                          (CPU_INT16U) 0u,
                          (CPU_INT16U) 0u,
                          (CPU_INT16U) 100u,
                          (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
                          (OS_ERR   *)&err_os);
        }

        dhcp_status = DHCPc_ChkStatus(if_nbr, &err_dhcp);
        switch (dhcp_status) {
            case DHCP_STATUS_CFGD:
                 APP_TRACE_INFO(("DHCP address configured\n\r"));
                 cfg_done = DEF_YES;
                 break;


            case DHCP_STATUS_CFGD_NO_TMR:
                 APP_TRACE_INFO(("DHCP address configured (no timer)\n\r"));
                 cfg_done = DEF_YES;
                 break;


            case DHCP_STATUS_CFGD_LOCAL_LINK:
                 APP_TRACE_INFO(("DHCP address configured (link-local)\n\r"));
                 cfg_done = DEF_YES;
                 break;


            case DHCP_STATUS_FAIL:
                 APP_TRACE_INFO(("DHCP address configuration failed\n\r"));
                 cfg_done = DEF_YES;
                 break;


            case DHCP_STATUS_CFG_IN_PROGRESS:
            default:
                 dly = DEF_YES;
                 break;
        }
    }

                                                                /* ------------ DISPLAY INTERFACE'S ADDRESS ----------- */
    APP_TRACE_INFO(("\n\r"));

    if (dhcp_status == DHCP_STATUS_FAIL) {
        return (DEF_FAIL);
    } else {
        return (DEF_OK);
    }
}
#endif

/*
*********************************************************************************************************
*                                     AppTCPIP_PrintIPAddr()
*
* Description : Obtain and Display IP Address, Subnet Mask, and Default Gateway on TCPIP IF Connection.
*
* Arguments   : if_nbr      Interface Number to obtain interface information.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppTCPIP_PrintIPAddr (NET_IF_NBR  if_nbr)
{
    NET_IPv4_ADDR     ip_addr_tbl[NET_IPv4_CFG_IF_MAX_NBR_ADDR];
    NET_IPv4_ADDR     subnet_addr;
    NET_IPv4_ADDR     gateway_addr;
    NET_IP_ADDRS_QTY  ip_addr_tbl_qty;
    NET_ERR           net_err;
    CPU_CHAR          ip_disp_addr[APP_TCPIP_ADDR_LEN];
    CPU_CHAR          sub_disp_addr[APP_TCPIP_ADDR_LEN];
    CPU_CHAR          gate_disp_addr[APP_TCPIP_ADDR_LEN];


    Mem_Clr(ip_disp_addr,   sizeof(ip_disp_addr));              /* Init Var(s).                                         */
    Mem_Clr(sub_disp_addr,  sizeof(sub_disp_addr));
    Mem_Clr(gate_disp_addr, sizeof(gate_disp_addr));
    ip_addr_tbl_qty = sizeof(ip_addr_tbl) / sizeof(NET_IPv4_ADDR);

    NetIPv4_GetAddrHost(if_nbr,                                 /* Get IPv4 Host Addresses based on Interface Number.   */
                        &ip_addr_tbl[0u],
                        &ip_addr_tbl_qty,
                        &net_err);

    if (net_err != NET_IPv4_ERR_NONE) {
        APP_TRACE_INFO(("NetIPv4_GetAddrHost() failed w/err = %d \r\n", net_err));
        return;
    }
                                                                /* Get IPv4 Subnet Mask & Dflt Gateway from Host Addr   */
    subnet_addr  = NetIPv4_GetAddrSubnetMask (ip_addr_tbl[0u], &net_err);
    gateway_addr = NetIPv4_GetAddrDfltGateway(ip_addr_tbl[0u], &net_err);

    NetASCII_IPv4_to_Str( ip_addr_tbl[0u],                      /* Set IPv4 IP Address to string.                       */
                         &ip_disp_addr[0u],
                          DEF_NO,
                         &net_err);

    NetASCII_IPv4_to_Str( subnet_addr,                          /* Set IPv4 Subnet Mask to String.                      */
                         &sub_disp_addr[0u],
                          DEF_NO,
                         &net_err);

    NetASCII_IPv4_to_Str( gateway_addr,                         /* Set IPv4 Default Gateway to String.                  */
                         &gate_disp_addr[0u],
                          DEF_NO,
                         &net_err);

                                                                /* -------------------- DISPLAY ADDR ------------------ */
    APP_TRACE_INFO(("- ETHERNET CONFIGURATION - \r\n"));
    APP_TRACE_INFO(("IP Address      : %s \r\n", ip_disp_addr  ));
    APP_TRACE_INFO(("Subnet Mask     : %s \r\n", sub_disp_addr ));
    APP_TRACE_INFO(("Default Gateway : %s \r\n", gate_disp_addr));
    APP_TRACE_INFO(("\r\n"));
}


/*
*********************************************************************************************************
*                                             ENABLE END
*********************************************************************************************************
*/

#endif
