/*
*********************************************************************************************************
*                                               uC/DNSc
*                                     Domain Name Server (client)
*
*                         (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/DNSc is provided in source form to registered licensees ONLY.  It is
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
*                                             DNS CLIENT
*
* Filename      : dns-c.h
* Version       : V2.00.01
* Programmer(s) : JDH
*                 AA
*********************************************************************************************************
* Note(s)       : (1) This file implements a basic DNS client based on RFC #1035.  It provides the
*                     mechanism used to retrieve an IP address from a given host name.
*
*                 (2) Assumes the following versions (or more recent) of software modules are included
*                     in the project build :
*
*                     (a) uC/TCP-IP V3.00
*                     (b) uC/CPU    V1.22
*                     (c) uC/LIB    V1.30
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               DNSc present pre-processor macro definition.
*********************************************************************************************************
*/


#ifndef  DNSc_PRESENT                                           /* See Note #1.                                         */
#define  DNSc_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         DNSc VERSION NUMBER
*
* Note(s) : (1) (a) The DNSc module software version is denoted as follows :
*
*                       Vx.yy.zz
*
*                           where
*                                   V               denotes 'Version' label
*                                   x               denotes     major software version revision number
*                                   yy              denotes     minor software version revision number
*                                   zz              denotes sub-minor software version revision number
*
*               (b) The DNSc software version label #define is formatted as follows :
*
*                       ver = x.yyzz * 100 * 100
*
*                           where
*                                   ver             denotes software version number scaled as an integer value
*                                   x.yyzz          denotes software version number, where the unscaled integer
*                                                       portion denotes the major version number & the unscaled
*                                                       fractional portion denotes the (concatenated) minor
*                                                       version numbers
*********************************************************************************************************
*/

#define  DNSc_VERSION               20001u                      /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) The DNSc module files are located in the following directories :
*
*               (a) \<Your Product Application>\dns-c_cfg.h
*
*               (b) \<Network Protocol Suite>\Source\net_*.*
*
*               (c) \<DNSc>\Source\dns-c.h
*                                 \dns-c.c
*
*                       where
*                               <Your Product Application>      directory path for Your Product's Application
*                               <Network Protocol Suite>        directory path for network protocol suite
*                               <DNSc>                          directory path for DNSc module
*
*           (2) CPU-configuration software files are located in the following directories :
*
*               (a) \<CPU-Compiler Directory>\cpu_*.*
*               (b) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                       where
*                               <CPU-Compiler Directory>        directory path for common CPU-compiler software
*                               <cpu>                           directory name for specific processor (CPU)
*                               <compiler>                      directory name for specific compiler
*
*           (3) NO compiler-supplied standard library functions SHOULD be used.
*
*               (a) Standard library functions are implemented in the custom library module(s) :
*
*                       \<Custom Library Directory>\lib_*.*
*
*                           where
*                                   <Custom Library Directory>      directory path for custom library software
*
*           (4) Compiler MUST be configured to include as additional include path directories :
*
*               (a) '\<Your Product Application>\' directory                            See Note #1a
*
*               (b) '\<Network Protocol Suite>\'   directory                            See Note #1b
*
*               (c) '\<DNSc>\' directory                                                See Note #1c
*
*               (d) (1) '\<CPU-Compiler Directory>\'                  directory         See Note #2a
*                   (2) '\<CPU-Compiler Directory>\<cpu>\<compiler>\' directory         See Note #2b
*
*               (e) '\<Custom Library Directory>\' directory                            See Note #3a
*********************************************************************************************************
*/

#include  <cpu.h>                                               /* CPU Configuration              (see Note #2b)        */
#include  <cpu_core.h>                                          /* CPU Core Library               (see Note #2a)        */

#include  <lib_def.h>                                           /* Standard        Defines        (see Note #3a)        */
#include  <lib_str.h>                                           /* Standard String Library        (see Note #3a)        */

#include  <dns-c_cfg.h>                                         /* DNSc Configuration File (see Note #1a)               */
#include  "dns-c_type.h"
#include  <Source/net_sock.h>
#include  <Source/net_type.h>

#include  <Source/net.h>                                        /* Network Protocol Suite         (see Note #1b)        */

/*
*********************************************************************************************************
*********************************************************************************************************
*                                         CONFIGURATION ERROR
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  DNSc_CFG_MODE_ASYNC_EN
    #error  "DNSc_CFG_MODE_ASYNC_EN not #define'd in 'dns-c_cfg.h' [MUST be  DEF_DISABLED ||  DEF_ENABLED ] "
#elif  ((DNSc_CFG_MODE_ASYNC_EN != DEF_ENABLED ) && \
        (DNSc_CFG_MODE_ASYNC_EN != DEF_DISABLED))
    #error  "DNSc_CFG_MODE_ASYNC_EN not #define'd in 'dns-c_cfg.h' [MUST be  DEF_DISABLED ||  DEF_ENABLED ] "
#endif

#if  (DNSc_CFG_MODE_ASYNC_EN == DEF_ENABLED)
    #define  DNSc_TASK_MODULE_EN

    #ifndef  DNSc_CFG_MODE_BLOCK_EN
        #error  "DNSc_CFG_MODE_BLOCK_EN not #define'd in 'dns-c_cfg.h' [MUST be  DEF_DISABLED ||  DEF_ENABLED ] "
    #elif  ((DNSc_CFG_MODE_BLOCK_EN != DEF_ENABLED ) && \
            (DNSc_CFG_MODE_BLOCK_EN != DEF_DISABLED))
        #error  "DNSc_CFG_MODE_BLOCK_EN not #define'd in 'dns-c_cfg.h' [MUST be  DEF_DISABLED ||  DEF_ENABLED ] "
    #endif

    #if  (DNSc_CFG_MODE_BLOCK_EN == DEF_ENABLED)
        #define  DNSc_SIGNAL_TASK_MODULE_EN
    #endif
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            DEFINE ERROR
*********************************************************************************************************
*********************************************************************************************************
*/

#define  DNSc_DFLT_TASK_DLY_MS                 50u
#define  DNSc_DFLT_REQ_RETRY_NBR_MAX            2u
#define  DNSc_DFLT_REQ_RETRY_TIMEOUT_MS      1000u





/*
*********************************************************************************************************
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

typedef  enum  DNSc_err {
    DNSc_ERR_NONE                =   1,
    DNSc_ERR_MEM_ALLOC           =   2,
    DNSc_ERR_FAULT               =   3,
    DNSc_ERR_TASK_SIGNAL         =   3,
    DNSc_ERR_FAULT_INIT          =   4,
    DNSc_ERR_NULL_PTR            =   5,
    DNSc_ERR_INVALID_ARG         =   6,
    DNSc_ERR_INVALID_CFG         =   7,
    DNSc_ERR_INVALID_SERVER      =   8,

    DNSc_ERR_INVALID_HOST_NAME   =   9,


    DNSc_ERR_CACHE_LOCK           = 50,
    DNSc_ERR_CACHE_HOST_NOT_FOUND = 51,
    DNSc_ERR_CACHE_HOST_PENDING   = 52,
    DNSc_ERR_CACHE_HOST_FAILED    = 52,

    DNSc_ERR_NO_SERVER           =  10,
    DNSc_ERR_GIVING_UP           =  11,
    DNSc_ERR_FMT                 =  12,
    DNSc_ERR_SERVER_FAIL         =  13,
    DNSc_ERR_NAME_NOT_EXIST      =  14,
    DNSc_ERR_NOT_A_RESPONSE      =  15,
    DNSc_ERR_RESOLUTION_FAIL     =  19,
    DNSc_ERR_NO_RESPONSE         =  25,

    DNSc_ERR_SOCK_OPEN_FAIL      =  20,
    DNSc_ERR_SOCK_CONN_FAIL      =  21,

    DNSc_ERR_TX                  =  30,
    DNSc_ERR_TX_FAULT            =  31,
    DNSc_ERR_RX                  =  32,
    DNSc_ERR_RX_FAULT            =  33,

    DNSc_ERR_BUF_LEN             =  35,


    DNSc_ERR_BAD_RESPONSE_TYPE   =  40,
    DNSc_ERR_BAD_QUESTION_COUNT  =  41,
    DNSc_ERR_BAD_ANSWER_COUNT    =  42,
    DNSc_ERR_BAD_RESPONSE_ID     =  43,
    DNSc_ERR_BAD_REQUEST_TYPE    =  45,


    DNSc_ERR_LAST                =  20,
    DNSc_ERR_INVALID_ID          =  21,
    DNSc_ERR_ADDR_INVALID        =  22,

} DNSc_ERR;


typedef  enum DNSc_state {
    DNSc_STATE_FREE = 0,
    DNSc_STATE_INIT_REQ,
    DNSc_STATE_TX_REQ_IPv4,
    DNSc_STATE_RX_RESP_IPv4,
    DNSc_STATE_TX_REQ_IPv6,
    DNSc_STATE_RX_RESP_IPv6,
    DNSc_STATE_RESOLVED,
    DNSc_STATE_FAILED,
} DNSc_STATE;


typedef  enum  DNSc_status {
    DNSc_STATUS_PENDING,
    DNSc_STATUS_RESOLVED,
    DNSc_STATUS_FAILED,
    DNSc_STATUS_UNKNOWN,
    DNSc_STATUS_NONE,
} DNSc_STATUS;



#ifdef  NET_IPv6_MODULE_EN
#define  DNSc_ADDR_SIZE   NET_IPv6_ADDR_LEN
#else
#define  DNSc_ADDR_SIZE   NET_IPv4_ADDR_LEN
#endif

typedef  CPU_INT08U   DNSc_FLAGS;

#define  DNSc_FLAG_NONE              DEF_BIT_NONE
#define  DNSc_FLAG_NO_BLOCK          DEF_BIT_00
#define  DNSc_FLAG_FORCE_CACHE       DEF_BIT_01
#define  DNSc_FLAG_FORCE_RENEW       DEF_BIT_02
#define  DNSc_FLAG_FORCE_RESOLUTION  DEF_BIT_03
#define  DNSc_FLAG_IPv4_ONLY         DEF_BIT_04
#define  DNSc_FLAG_IPv6_ONLY         DEF_BIT_05


typedef  struct  dnsc_ip_addr {
    CPU_INT08U  Addr[DNSc_ADDR_SIZE];
    CPU_INT08U  Len;
} DNSc_ADDR_OBJ;

typedef  struct  DNSc_addr_item   DNSc_ADDR_ITEM;

struct  DNSc_addr_item {
    DNSc_ADDR_OBJ   *AddrPtr;
    DNSc_ADDR_ITEM  *NextPtr;
};


#define  DNSc_QUERY_ID_NONE     0u

typedef  struct  DNSc_req_cfg {
    DNSc_ADDR_OBJ  *ServerAddrPtr;
    NET_PORT_NBR    ServerPort;
    CPU_INT16U      TaskDly_ms;
    CPU_INT16U      ReqTimeout_ms;
    CPU_INT08U      ReqRetry;
} DNSc_REQ_CFG;


typedef  struct  DNSc_host {
    CPU_CHAR        *NamePtr;
    CPU_INT16U       NameLenMax;
    DNSc_STATE       State;
    DNSc_ADDR_ITEM  *AddrsFirstPtr;
    DNSc_ADDR_ITEM  *AddrsEndPtr;
    CPU_INT08U       AddrsCount;
    CPU_INT08U       AddrsIPv4Count;
    CPU_INT08U       AddrsIPv6Count;
    CPU_INT08U       ReqCtr;
    NET_SOCK_ID      SockID;
    CPU_INT16U       QueryID;
    NET_TS_MS        TS_ms;
    DNSc_REQ_CFG    *ReqCfgPtr;
#ifdef  DNSc_SIGNAL_TASK_MODULE_EN
    KAL_SEM_HANDLE   TaskSignal;
#endif
} DNSc_HOST_OBJ;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void         DNSc_Init            (const  DNSc_CFG       *p_cfg,
                                   const  DNSc_CFG_TASK  *p_task_cfg,
                                          DNSc_ERR       *p_err);

void         DNSc_CfgServerByStr  (       CPU_CHAR       *p_server,
                                          DNSc_ERR       *p_err);

void         DNSc_CfgServerByAddr (       DNSc_ADDR_OBJ  *p_addr,
                                          DNSc_ERR       *p_err);

void         DNSc_GetServerByStr  (       CPU_CHAR       *p_str,
                                          CPU_INT08U      str_len_max,
                                          DNSc_ERR       *p_err);

void         DNSc_GetServerByAddr (       DNSc_ADDR_OBJ  *p_addr,
                                          DNSc_ERR       *p_err);

DNSc_STATUS  DNSc_GetHost         (       CPU_CHAR       *p_host_name,
                                          DNSc_ADDR_OBJ  *p_addrs,
                                          CPU_INT08U     *p_addr_nbr,
                                          DNSc_FLAGS      flags,
                                          DNSc_REQ_CFG   *p_cfg,
                                          DNSc_ERR       *p_err);

void         DNSc_CacheClrAll     (       DNSc_ERR       *p_err);

void         DNSc_CacheClrHost    (       CPU_CHAR       *p_host_name,
                                          DNSc_ERR       *p_err);

#endif

