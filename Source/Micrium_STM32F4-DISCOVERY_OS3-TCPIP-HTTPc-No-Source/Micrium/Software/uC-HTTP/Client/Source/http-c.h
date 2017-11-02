/*
*********************************************************************************************************
*                                              uC/HTTPc
*                                 Hypertext Transfer Protocol (client)
*
*                          (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/HTTPc is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                             HTTP CLIENT
*
* Filename      : http-c.h
* Version       : V1.00.00
* Programmer(s) : MM
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                       (a) uC/CPU    V1.29.02
*                       (b) uC/LIB    V1.38.00
*                       (c) uC/Common V1.00.00
*                       (d) uC/TCP-IP V3.02.00
*
*
*                 (2) For additional details on the features available with uC/HTTPc, the API, the
*                     installation, etc. Please refer to the uC/HTTPc documentation available at
*                     https://doc.micrium.com/HTTPc.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This main network protocol suite header file is protected from multiple pre-processor
*               inclusion through use of the HTTPc module present pre-processor macro definition.
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  HTTPc_MODULE_PRESENT                                   /* See Note #1.                                         */
#define  HTTPc_MODULE_PRESENT


/*
*********************************************************************************************************
*********************************************************************************************************
*                                        HTTPc VERSION NUMBER
*
* Note(s) : (1) (a) The HTTPc module software version is denoted as follows :
*
*                       Vx.yy.zz
*
*                           where
*                                   V               denotes 'Version' label
*                                   x               denotes     major software version revision number
*                                   yy              denotes     minor software version revision number
*                                   zz              denotes sub-minor software version revision number
*
*               (b) The HTTPc software version label #define is formatted as follows :
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
*********************************************************************************************************
*/

#define  HTTPc_VERSION                                 10000u   /* See Note #1.                                         */


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>
#include  <lib_str.h>
#include  <lib_ascii.h>

#include  <Source/net.h>
#include  <Source/net_cfg_net.h>
#include  <Source/net_app.h>
#include  <Source/net_sock.h>

#include  <http-c_cfg.h>
#include  "../../Common/http.h"


/*
*********************************************************************************************************
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        HTTPc CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  HTTPc_CFG_ARG_CHK_EXT_EN
   #error  "HTTPc_CFG_ARG_CHK_EXT_EN                 not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_ARG_CHK_EXT_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_ARG_CHK_EXT_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_ARG_CHK_EXT_EN           illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_MODE_ASYNC_TASK_EN
   #error  "HTTPc_CFG_MODE_ASYNC_TASK_EN             not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_MODE_ASYNC_TASK_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_MODE_ASYNC_TASK_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_MODE_ASYNC_TASK_EN       illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_MODE_BLOCK_EN
   #error  "HTTPc_CFG_MODE_BLOCK_EN                  not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_MODE_BLOCK_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_MODE_BLOCK_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_MODE_BLOCK_EN            illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_PERSISTENT_EN
   #error  "HTTPc_CFG_PERSISTENT_EN                  not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_PERSISTENT_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_PERSISTENT_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_PERSISTENT_EN            illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_CHUNK_TX_EN
   #error  "HTTPc_CFG_CHUNK_TX_EN                    not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_CHUNK_TX_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_CHUNK_TX_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_CHUNK_TX_EN              illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_QUERY_STR_EN
   #error  "HTTPc_CFG_QUERY_STR_EN                   not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_QUERY_STR_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_QUERY_STR_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_QUERY_STR_EN             illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_HDR_RX_EN
   #error  "HTTPc_CFG_HDR_RX_EN                      not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_HDR_RX_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_HDR_RX_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_HDR_RX_EN                illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_HDR_TX_EN
   #error  "HTTPc_CFG_HDR_TX_EN                      not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_HDR_TX_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_HDR_TX_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_HDR_TX_EN                illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_FORM_EN
   #error  "HTTPc_CFG_FORM_EN                        not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_FORM_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_FORM_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_FORM_EN                  illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif

#ifndef  HTTPc_CFG_USER_DATA_EN
   #error  "HTTPc_CFG_USER_DATA_EN                   not #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#elif  ((HTTPc_CFG_USER_DATA_EN != DEF_ENABLED ) && \
        (HTTPc_CFG_USER_DATA_EN != DEF_DISABLED))
   #error  "HTTPc_CFG_USER_DATA_EN             illegally #define'd in 'http-c_cfg.h'"
   #error  "                             [MUST be  DEF_DISABLED]                    "
   #error  "                             [     ||  DEF_ENABLED ]                    "
#endif


/*
*********************************************************************************************************
*                                    NETWORK CONFIGURATION ERRORS
*********************************************************************************************************
*/

#if     (NET_VERSION < 30200u)
#error  "NET_VERSION                       Invalid network protocol suite version    "
#error  "                                  [MUST be >= 3.02.00]                      "
#endif

#if     (NET_SOCK_CFG_SEL_EN != DEF_ENABLED)
#error  "NET_SOCK_CFG_SEL_EN               illegally #define'd in 'net_cfg.h'        "
#error  "                                  [MUST be  DEF_ENABLED]                    "
#endif


/*
*********************************************************************************************************
*                                      LIB CONFIGURATION ERRORS
*********************************************************************************************************
*/

#if     (LIB_VERSION < 13800u)
#error  "LIB_VERSION                       Invalid library suite version"
#error  "                                  [MUST be >= 1.38.00]         "
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            MODULE DEFINES
*********************************************************************************************************
*/

#if (HTTPc_CFG_MODE_ASYNC_TASK_EN == DEF_ENABLED)

    #define  HTTPc_TASK_MODULE_EN

    #if  (HTTPc_CFG_MODE_BLOCK_EN == DEF_ENABLED)
        #define  HTTPc_SIGNAL_TASK_MODULE_EN
    #endif

#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                   HTTP CLIENT FLAGS DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT08U  HTTPc_FLAGS;

#define  HTTPc_FLAG_NONE                                    DEF_BIT_NONE

                                                                /* SOCKET FLAGS          */
#define  HTTPc_FLAG_SOCK_RDY_RD                             DEF_BIT_00
#define  HTTPc_FLAG_SOCK_RDY_WR                             DEF_BIT_01
#define  HTTPc_FLAG_SOCK_RDY_ERR                            DEF_BIT_02

                                                                /* CONNECTION FLAGS      */
#define  HTTPc_FLAG_CONN_CONNECT                            DEF_BIT_00      /* bits 0-3 internal usage. */
#define  HTTPc_FLAG_CONN_IN_USE                             DEF_BIT_01
#define  HTTPc_FLAG_CONN_TO_CLOSE                           DEF_BIT_02
#define  HTTPc_FLAG_CONN_PERSISTENT                         DEF_BIT_04      /* bits 4-7 configurable.   */
#define  HTTPc_FLAG_CONN_NO_BLOCK                           DEF_BIT_05

                                                                /* REQUEST CFG FLAGS     */
#define  HTTPc_FLAG_REQ_NO_BLOCK                            DEF_BIT_00
#define  HTTPc_FLAG_REQ_BODY_PRESENT                        DEF_BIT_01
#define  HTTPc_FLAG_REQ_FORM_PRESENT                        DEF_BIT_02
#define  HTTPc_FLAG_REQ_BODY_CHUNK_TRANSFER                 DEF_BIT_03
#define  HTTPc_FLAG_REQ_IN_USE                              DEF_BIT_04

                                                                /* REQUEST CFG HDR FLAGS */
#define  HTTPc_FLAG_REQ_HDR_HOST_ADD                        DEF_BIT_00
#define  HTTPc_FLAG_REQ_HDR_CONTENT_TYPE_ADD                DEF_BIT_01
#define  HTTPc_FLAG_REQ_HDR_TRANSFER_ENCODE_ADD             DEF_BIT_02
#define  HTTPc_FLAG_REQ_HDR_CONTENT_LENGTH_ADD              DEF_BIT_03
#define  HTTPc_FLAG_REQ_HDR_CONNECTION_ADD                  DEF_BIT_04

                                                                /* REQUEST FLAGS         */
#define  HTTPc_FLAG_REQ_LINE_QUERY_STR_BEGIN                DEF_BIT_00
#define  HTTPc_FLAG_REQ_LINE_QUERY_STR_DONE                 DEF_BIT_01
#define  HTTPc_FLAG_REQ_HDR_DONE                            DEF_BIT_02
#define  HTTPc_FLAG_REQ_BODY_CHUNK_LAST                     DEF_BIT_03

                                                                /* RESPONSE FLAGS        */
#define  HTTPc_FLAG_RESP_RX_MORE_DATA                       DEF_BIT_00
#define  HTTPc_FLAG_RESP_BODY_CHUNK_TRANSFER                DEF_BIT_01
#define  HTTPc_FLAG_RESP_COMPLETE_OK                        DEF_BIT_02


/*
*********************************************************************************************************
*                                     API PARAMETERS DATA TYPE
*********************************************************************************************************
*/

typedef  enum  httpc_param_type {
    HTTPc_PARAM_TYPE_SERVER_PORT,
    HTTPc_PARAM_TYPE_PERSISTENT,
    HTTPc_PARAM_TYPE_CONNECT_TIMEOUT,
    HTTPc_PARAM_TYPE_INACTIVITY_TIMEOUT,
    HTTPc_PARAM_TYPE_SECURE_COMMON_NAME,
    HTTPc_PARAM_TYPE_SECURE_TRUST_CALLBACK,
    HTTPc_PARAM_TYPE_REQ_QUERY_STR_TBL,
    HTTPc_PARAM_TYPE_REQ_QUERY_STR_HOOK,
    HTTPc_PARAM_TYPE_REQ_HDR_TBL,
    HTTPc_PARAM_TYPE_REQ_HDR_HOOK,
    HTTPc_PARAM_TYPE_REQ_FORM_TBL,
    HTTPc_PARAM_TYPE_REQ_BODY_CONTENT_TYPE,
    HTTPc_PARAM_TYPE_REQ_BODY_CONTENT_LEN,
    HTTPc_PARAM_TYPE_REQ_BODY_CHUNK,
    HTTPc_PARAM_TYPE_REQ_BODY_HOOK,
    HTTPc_PARAM_TYPE_RESP_HDR_HOOK,
    HTTPc_PARAM_TYPE_RESP_BODY_HOOK,
    HTTPc_PARAM_TYPE_TRANS_COMPLETE_CALLBACK,
    HTTPc_PARAM_TYPE_TRANS_ERR_CALLBACK,
    HTTPc_PARAM_TYPE_CONN_CONNECT_CALLBACK,
    HTTPc_PARAM_TYPE_CONN_CLOSE_CALLBACK,
} HTTPc_PARAM_TYPE;


/*
*********************************************************************************************************
*                                     TABLE PARAMETER DATA TYPE
*********************************************************************************************************
*/

typedef  struct  httpc_param_tbl {
    void        *TblPtr;
    CPU_INT16U   EntryNbr;
} HTTPc_PARAM_TBL;


/*
*********************************************************************************************************
*                                    CONNECTION STATES DATA TYPE
*********************************************************************************************************
*/

#define  HTTPc_CONN_STATE_FAMILY_MASK                           DEF_BIT_MASK_08(7, 5)

#define  HTTPc_CONN_STATE_FLOW_FAMILY                           DEF_BIT_MASK_08(0, 5)

#define  HTTPc_CONN_STATE_REQ_FAMILY                            DEF_BIT_MASK_08(1, 5)

#define  HTTPc_CONN_STATE_RESP_FAMILY                           DEF_BIT_MASK_08(2, 5)

typedef enum httpc_conn_state {
    HTTPc_CONN_STATE_NONE                                       = 0u,   /* 0b000xxxxx */
    HTTPc_CONN_STATE_UNKNOWN,
    HTTPc_CONN_STATE_PARAM_VALIDATE,
    HTTPc_CONN_STATE_CONNECT,
    HTTPc_CONN_STATE_COMPLETED,
    HTTPc_CONN_STATE_CLOSE,
    HTTPc_CONN_STATE_ERR,

    HTTPc_CONN_STATE_REQ_LINE_METHOD                            = 32u,  /* 0b001xxxxx */
    HTTPc_CONN_STATE_REQ_LINE_URI,
    HTTPc_CONN_STATE_REQ_LINE_QUERY_STR,
    HTTPc_CONN_STATE_REQ_LINE_PROTO_VER,
    HTTPc_CONN_STATE_REQ_HDR_HOST,
    HTTPc_CONN_STATE_REQ_HDR_CONTENT_TYPE,
    HTTPc_CONN_STATE_REQ_HDR_CONTENT_LEN,
    HTTPc_CONN_STATE_REQ_HDR_TRANSFER_ENCODE,
    HTTPc_CONN_STATE_REQ_HDR_CONN,
    HTTPc_CONN_STATE_REQ_HDR_EXT,
    HTTPc_CONN_STATE_REQ_HDR_LAST,
    HTTPc_CONN_STATE_REQ_BODY,
    HTTPc_CONN_STATE_REQ_BODY_DATA,
    HTTPc_CONN_STATE_REQ_BODY_DATA_CHUNK_SIZE,
    HTTPc_CONN_STATE_REQ_BODY_DATA_CHUNK_DATA,
    HTTPc_CONN_STATE_REQ_BODY_DATA_CHUNK_END,
    HTTPc_CONN_STATE_REQ_BODY_FORM_APP,
    HTTPc_CONN_STATE_REQ_BODY_FORM_MULTIPART_BOUNDARY,
    HTTPc_CONN_STATE_REQ_BODY_FORM_MULTIPART_HDR_CONTENT_DISPO,
    HTTPc_CONN_STATE_REQ_BODY_FORM_MULTIPART_HDR_CONTENT_TYPE,
    HTTPc_CONN_STATE_REQ_BODY_FORM_MULTIPART_DATA,
    HTTPc_CONN_STATE_REQ_BODY_FORM_MULTIPART_DATA_END,
    HTTPc_CONN_STATE_REQ_BODY_FORM_MULTIPART_BOUNDARY_END,
    HTTPc_CONN_STATE_REQ_END,

    HTTPc_CONN_STATE_RESP_INIT                                  = 64u,  /* 0b010xxxxx */
    HTTPc_CONN_STATE_RESP_STATUS_LINE,
    HTTPc_CONN_STATE_RESP_HDR,
    HTTPc_CONN_STATE_RESP_BODY,
    HTTPc_CONN_STATE_RESP_BODY_CHUNK_SIZE,
    HTTPc_CONN_STATE_RESP_BODY_CHUNK_DATA,
    HTTPc_CONN_STATE_RESP_BODY_CHUNK_LAST,
    HTTPc_CONN_STATE_RESP_COMPLETED

} HTTPc_CONN_STATE;


/*
*********************************************************************************************************
*                                  CONNECTION CLOSE STATUS DATA TYPE
*********************************************************************************************************
*/

typedef enum httpc_conn_close_status {
    HTTPc_CONN_CLOSE_STATUS_NONE,
    HTTPc_CONN_CLOSE_STATUS_ERR_INTERNAL,
    HTTPc_CONN_CLOSE_STATUS_SERVER,
    HTTPc_CONN_CLOSE_STATUS_NO_PERSISTENT,
    HTTPc_CONN_CLOSE_STATUS_APP
} HTTPc_CONN_CLOSE_STATUS;


/*
*********************************************************************************************************
*                                          ERROR DATA TYPE
*********************************************************************************************************
*/

#define  HTTPc_ERR_FAMILY_MASK                              DEF_BIT_MASK_08(3, 6)
#define  HTTPc_ERR_INIT_CFG_FAMILY                          DEF_BIT_MASK_08(0, 6)
#define  HTTPc_ERR_CONN_FAMILY                              DEF_BIT_MASK_08(1, 6)
#define  HTTPc_ERR_TRANS_FAMILY                             DEF_BIT_MASK_08(2, 6)

typedef  enum  httpc_err {

    HTTPc_ERR_NONE                                  = 1,

    HTTPc_ERR_NULL_PTR,
    HTTPc_ERR_FEATURE_DIS,

    HTTPc_ERR_INIT,
    HTTPc_ERR_INIT_NOT_COMPLETED,
    HTTPc_ERR_INIT_TASK_INVALID_ARG,
    HTTPc_ERR_INIT_TASK_MEM_ALLOC,
    HTTPc_ERR_INIT_TASK_CREATE,
    HTTPc_ERR_INIT_CONN_OPEN_Q,
    HTTPc_ERR_INIT_CONN_CLOSE_Q,
    HTTPc_ERR_INIT_REQ_Q,

    HTTPc_ERR_CFG_CONN_TIMEOUT_INVALID,
    HTTPc_ERR_CFG_CONN_Q_SIZE_INVALID,
    HTTPc_ERR_CFG_REQ_Q_SIZE_INVALID,
    HTTPc_ERR_CFG_TASK_PTR_NULL,
    HTTPc_ERR_CFG_TASK_DLY_INVALID,
    HTTPc_ERR_CFG_INVALID_BUF_LEN,

    HTTPc_ERR_PARAM_INVALID,

    HTTPc_ERR_FORM_TYPE_INVALID,
    HTTPc_ERR_FORM_FIELD_INVALID,
    HTTPc_ERR_FORM_CREATE,
    HTTPc_ERR_FORM_BUF_LEN_INVALID,

    HTTPc_ERR_CONN_PARAM_ADDR_INVALID               = 64u,
    HTTPc_ERR_CONN_PARAM_ADDR_FAMILY_INVALID,
    HTTPc_ERR_CONN_PARAM_HOSTNAME_INVALID,
    HTTPc_ERR_CONN_PARAM_PORT_INVALID,
    HTTPc_ERR_CONN_PARAM_PERSISTENT_INVALID,
    HTTPc_ERR_CONN_PARAM_CONNECT_TIMEOUT_INVALID,
    HTTPc_ERR_CONN_PARAM_INACTIVITY_TIMEOUT_INVALID,
    HTTPc_ERR_CONN_PARAM_CONNECT_CALLBACK_INVALID,
    HTTPc_ERR_CONN_PARAM_CLOSE_CALLBACK_INVALID,
    HTTPc_ERR_CONN_PARAM_ERR_CALLBACK_INVALID,

    HTTPc_ERR_CONN_OPEN_Q_FULL,
    HTTPc_ERR_CONN_OPEN_Q_SIGNAL_FAULT,
    HTTPc_ERR_CONN_OPEN_Q_EMPTY,
    HTTPc_ERR_CONN_CLOSE_Q_FULL,
    HTTPc_ERR_CONN_CLOSE_Q_SIGNAL_FAULT,
    HTTPc_ERR_CONN_CLOSE_Q_EMPTY,
    HTTPc_ERR_CONN_REQ_Q_FULL,
    HTTPc_ERR_CONN_REQ_Q_SIGNAL_FAULT,
    HTTPc_ERR_CONN_REQ_Q_EMPTY,

    HTTPc_ERR_CONN_SIGNAL_CREATE,
    HTTPc_ERR_CONN_SIGNAL_DEL,
    HTTPc_ERR_CONN_SIGNAL_TIMEOUT,
    HTTPc_ERR_CONN_SIGNAL_FAULT,

    HTTPc_ERR_CONN_IS_CONNECT,
    HTTPc_ERR_CONN_IS_USED,
    HTTPc_ERR_CONN_IS_RELEASED,
    HTTPc_ERR_CONN_INVALID_STATE,

    HTTPc_ERR_CONN_SOCK_OPEN,
    HTTPc_ERR_CONN_SOCK_CONNECT,
    HTTPc_ERR_CONN_SOCK_TX,
    HTTPc_ERR_CONN_SOCK_TX_FATAL,
    HTTPc_ERR_CONN_SOCK_RX,
    HTTPc_ERR_CONN_SOCK_RX_FATAL,
    HTTPc_ERR_CONN_SOCK_CLOSED,
    HTTPc_ERR_CONN_SOCK_CLOSE_FATAL,
    HTTPc_ERR_CONN_SOCK_SEL,
    HTTPc_ERR_CONN_SOCK_FAULT,

    HTTPc_ERR_TRANS_BUF_LEN_INVALID                 = 128u,
    HTTPc_ERR_TRANS_TX_BUF_FULL,
    HTTPc_ERR_TRANS_RX_MORE_DATA_REQUIRED,

    HTTPc_ERR_REQ_IS_USED,

    HTTPc_ERR_REQ_PARAM_METHOD_INVALID,
    HTTPc_ERR_REQ_PARAM_RESOURCE_PATH_INVALID,
    HTTPc_ERR_REQ_PARAM_CONTENT_TYPE_INVALID,
    HTTPc_ERR_REQ_PARAM_CONTENT_LEN_INVALID,
    HTTPc_ERR_REQ_PARAM_BODY_INVALID,
    HTTPc_ERR_REQ_PARAM_QUERY_STR_TBL_INVALID,
    HTTPc_ERR_REQ_PARAM_HDR_INVALID_TBL_PTR,
    HTTPc_ERR_REQ_PARAM_HDR_UNAUTHORIZED,
    HTTPc_ERR_REQ_PARAM_FORM_FIELD_TBL_INVALID,
    HTTPc_ERR_REQ_PARAM_FORM_FIELD_NULL_PTR,
    HTTPc_ERR_REQ_PARAM_FORM_FIELD_INVALID_LEN,
    HTTPc_ERR_REQ_PARAM_ERR_CALLBACK_INVALID,
    HTTPc_ERR_REQ_PARAM_TRANS_COMPLETE_CALLBACK_INVALID,

    HTTPc_ERR_REQ_LINE_CREATE,
    HTTPc_ERR_REQ_QUERY_STR_CREATE,
    HTTPc_ERR_REQ_QUERY_STR_INVALID,
    HTTPc_ERR_REQ_HDR_CREATE,
    HTTPc_ERR_REQ_HDR_INVALID,
    HTTPc_ERR_REQ_FORM_CREATE,
    HTTPc_ERR_REQ_BODY_PREPARE,
    HTTPc_ERR_REQ_BODY_CHUNK_PREPARE,
    HTTPc_ERR_REQ_BODY_CHUNK_INVALID,
    HTTPc_ERR_REQ_BODY_NOT_PRESENT,

    HTTPc_ERR_RESP_FORMAT_INVALID,
    HTTPc_ERR_RESP_PROTOCOL_VER_INVALID,
    HTTPc_ERR_RESP_STATUS_CODE_INVALID,
    HTTPc_ERR_RESP_REASON_PHRASE_INVALID,
    HTTPc_ERR_RESP_HDR_INVALID,
    HTTPc_ERR_RESP_HDR_MALFORMED,
    HTTPc_ERR_RESP_CONTENT_TYPE_INVALID,
    HTTPc_ERR_RESP_CONTENT_LEN_INVALID,
    HTTPc_ERR_RESP_CHUNK_INVALID,
    HTTPc_ERR_RESP_RX_DATA_LEN_INVALID

} HTTPc_ERR;


/*
*********************************************************************************************************
*                                      HTTP CLIENT OBJECTS DATA TYPE
*********************************************************************************************************
*/

typedef  struct  httpc_conn         HTTPc_CONN;

typedef  struct  httpc_conn_obj     HTTPc_CONN_OBJ;

typedef  struct  httpc_req          HTTPc_REQ;

typedef  struct  httpc_req_obj      HTTPc_REQ_OBJ;

typedef  struct  httpc_resp         HTTPc_RESP;

typedef  struct  httpc_resp         HTTPc_RESP_OBJ;


/*
*********************************************************************************************************
*                                    HTTP CLIENT HDR FIELD DATA TYPE
*********************************************************************************************************
*/

typedef  struct  httpc_hdr {
    HTTP_HDR_FIELD      HdrField;
    CPU_CHAR           *ValPtr;
    CPU_INT16U          ValLen;
} HTTPc_HDR;


/*
*********************************************************************************************************
*                                      HTTP CLIENT FORM DATA TYPE
*********************************************************************************************************
*/

typedef  enum  httpc_form_field_type {
    HTTPc_FORM_FIELD_TYPE_KEY_VAL,
    HTTPc_FORM_FIELD_TYPE_KEY_VAL_EXT,
    HTTPc_FORM_FIELD_TYPE_FILE
} HTTPc_FORM_FIELD_TYPE;

typedef  struct  httpc_form_tbl_field {
    HTTPc_FORM_FIELD_TYPE   Type;
    void                   *FieldObjPtr;
} HTTPc_FORM_TBL_FIELD;


/*
*********************************************************************************************************
*                                        KEY-VALUE PAIR DATA TYPE
*********************************************************************************************************
*/

typedef  struct  httpc_key_val {
    CPU_CHAR       *KeyPtr;
    CPU_INT16U      KeyLen;
    CPU_CHAR       *ValPtr;
    CPU_INT16U      ValLen;
} HTTPc_KEY_VAL;


/*
*********************************************************************************************************
*                                      BIG KEY-VALUE PAIR DATA TYPE
*********************************************************************************************************
*/

typedef  struct  httpc_key_val_ext  HTTPc_KEY_VAL_EXT;

typedef  CPU_BOOLEAN  (*HTTPc_KEY_VAL_EXT_HOOK) (HTTPc_CONN_OBJ     *p_conn,
                                                 HTTPc_REQ_OBJ      *p_req,
                                                 HTTPc_KEY_VAL_EXT  *p_key_val_obj,
                                                 CPU_CHAR           *p_buf,
                                                 CPU_INT16U          buf_len,
                                                 CPU_INT16U         *p_len_wr);

struct  httpc_key_val_ext {
    CPU_CHAR                *KeyPtr;
    CPU_INT16U               KeyLen;
    HTTPc_KEY_VAL_EXT_HOOK   OnValTx;
    CPU_INT32U               ValLen;
};


/*
*********************************************************************************************************
*                                      HTTP MULTIPART FORM DATA TYPE
*********************************************************************************************************
*/

typedef  struct  http_multipart_file  HTTPc_MULTIPART_FILE;

typedef  CPU_BOOLEAN  (*HTTPc_MULTIPART_FILE_HOOK) (HTTPc_CONN_OBJ        *p_conn,
                                                    HTTPc_REQ_OBJ         *p_req,
                                                    HTTPc_MULTIPART_FILE  *p_file_obj,
                                                    CPU_CHAR              *p_buf,
                                                    CPU_INT16U             buf_len,
                                                    CPU_INT16U            *p_len_wr);

struct  http_multipart_file {
    CPU_CHAR                   *NamePtr;
    CPU_INT16U                  NameLen;
    CPU_CHAR                   *FileNamePtr;
    CPU_INT16U                  FileNameLen;
    CPU_INT32U                  FileLen;
    HTTP_CONTENT_TYPE           ContentType;
    HTTPc_MULTIPART_FILE_HOOK   OnFileTx;
};


/*
*********************************************************************************************************
*                                  HOOK & CALLBACK FUNCTIONS DATA TYPE
*********************************************************************************************************
*/

typedef  void         (*HTTPc_CONNECT_CALLBACK)      (HTTPc_CONN_OBJ            *p_conn,
                                                      CPU_BOOLEAN                open_status);

typedef  void         (*HTTPc_CONN_CLOSE_CALLBACK)   (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_CONN_CLOSE_STATUS    close_status,
                                                      HTTPc_ERR                  err);

typedef  void         (*HTTPc_CONN_ERR_CALLBACK)     (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_ERR                  err);

typedef  CPU_BOOLEAN  (*HTTPc_REQ_QUERY_STR_HOOK)    (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_REQ_OBJ             *p_req,
                                                      HTTPc_KEY_VAL            **p_key_val);

typedef  CPU_BOOLEAN  (*HTTPc_REQ_HDR_HOOK)          (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_REQ_OBJ             *p_req,
                                                      HTTPc_HDR                **p_hdr);

typedef  CPU_BOOLEAN  (*HTTPc_REQ_BODY_HOOK)         (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_REQ_OBJ             *p_req,
                                                      void                     **p_data,
                                                      CPU_CHAR                  *p_buf,
                                                      CPU_INT16U                 buf_len,
                                                      CPU_INT16U                *p_data_len);

typedef  void         (*HTTPc_RESP_HDR_HOOK)         (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_REQ_OBJ             *p_req,
                                                      HTTP_HDR_FIELD             hdr_field,
                                                      CPU_CHAR                  *p_hdr_val,
                                                      CPU_INT16U                 val_len);

typedef  void         (*HTTPc_RESP_BODY_HOOK)        (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_REQ_OBJ             *p_req,
                                                      HTTP_CONTENT_TYPE          content_type,
                                                      void                      *p_data,
                                                      CPU_INT16U                 data_len,
                                                      CPU_BOOLEAN                last_chunk);

typedef  void         (*HTTPc_COMPLETE_CALLBACK)     (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_REQ_OBJ             *p_req,
                                                      HTTPc_RESP_OBJ            *p_resp,
                                                      CPU_BOOLEAN                status);

typedef  void         (*HTTPc_TRANS_ERR_CALLBACK)    (HTTPc_CONN_OBJ            *p_conn,
                                                      HTTPc_REQ_OBJ             *p_req,
                                                      HTTPc_ERR                  err);


/*
*********************************************************************************************************
*                                      HTTPc RESPONSE DATA TYPE
*********************************************************************************************************
*/

struct httpc_resp {
           HTTP_PROTOCOL_VER          ProtocolVer;              /* HTTP version received in response message.           */
           HTTP_STATUS_CODE           StatusCode;               /* Status code received in response.                    */
    const  CPU_CHAR                  *ReasonPhrasePtr;          /* Pointer to received reason phrase.                   */
           HTTP_CONTENT_TYPE          ContentType;              /* Content type received in response.                   */
           CPU_INT32U                 ContentLen;               /* Content length received in response if any.          */
};


/*
*********************************************************************************************************
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         STRUCT FIELD DEFINE MACRO
*********************************************************************************************************
*/

#define  FIELD_DEF(prefix, type, name, suffix)    prefix  type  name##suffix;


/*
*********************************************************************************************************
*                                          USER DATA FIELD MACRO
*********************************************************************************************************
*/

#if (HTTPc_CFG_USER_DATA_EN == DEF_ENABLED)
#define  USER_DATA_FIELD_DEF(prefix, suffix)  FIELD_DEF(prefix,  void,  *UserDataPtr,  suffix)
#else
#define  USER_DATA_FIELD_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                     REQUEST QUERY STRING FIELDS MACRO
*********************************************************************************************************
*/

#if (HTTPc_CFG_QUERY_STR_EN == DEF_ENABLED)
#define  REQ_QUERY_STR_FIELDS_DEF(prefix, suffix)  FIELD_DEF(prefix,  HTTPc_KEY_VAL,             *QueryStrTbl,  suffix) \
                                                   FIELD_DEF(prefix,  CPU_INT16U,                 QueryStrNbr,  suffix) \
                                                   FIELD_DEF(prefix,  HTTPc_REQ_QUERY_STR_HOOK,   OnQueryStrTx,  suffix)
#else
#define  REQ_QUERY_STR_FIELDS_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                     REQUEST HEADER TX FIELDS MACRO
*********************************************************************************************************
*/

#if (HTTPc_CFG_HDR_TX_EN == DEF_ENABLED)
#define  REQ_HDR_TX_FIELDS_DEF(prefix, suffix)  FIELD_DEF(prefix,  HTTPc_HDR,           *HdrTbl,   suffix) \
                                                FIELD_DEF(prefix,  CPU_INT16U,           HdrNbr,   suffix) \
                                                FIELD_DEF(prefix,  HTTPc_REQ_HDR_HOOK,   OnHdrTx,  suffix)
#else
#define  REQ_HDR_TX_FIELDS_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                        REQUEST FORM FIELDS MACRO
*********************************************************************************************************
*/

#if (HTTPc_CFG_FORM_EN == DEF_ENABLED)
#define  REQ_FORM_FIELDS_DEF(prefix, suffix)  FIELD_DEF(prefix,  HTTPc_FORM_TBL_FIELD ,  *FormFieldTbl,  suffix) \
                                              FIELD_DEF(prefix,  CPU_INT16U,              FormFieldNbr,  suffix)
#else
#define  REQ_FORM_FIELDS_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                     REQUEST HDR RX HOOK FIELD MACRO
*********************************************************************************************************
*/

#if (HTTPc_CFG_HDR_RX_EN == DEF_ENABLED)
#define  REQ_HDR_RX_FIELD_DEF(prefix, suffix)  FIELD_DEF(prefix,  HTTPc_RESP_HDR_HOOK,  OnHdrRx,  suffix)
#else
#define  REQ_HDR_RX_FIELD_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                    REQUEST TASK CALLBACK FIELDS MACRO
*********************************************************************************************************
*/

#ifdef HTTPc_TASK_MODULE_EN
#define  REQ_TASK_CALLBACK_FIELDS_DEF(prefix, suffix)  FIELD_DEF(prefix,  HTTPc_COMPLETE_CALLBACK,   OnTransComplete,  suffix) \
                                                       FIELD_DEF(prefix,  HTTPc_TRANS_ERR_CALLBACK,  OnErr,            suffix)
#else
#define  REQ_TASK_CALLBACK_FIELDS_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                         REQUEST STRUCTURE MACRO
*********************************************************************************************************
*/

#define  STRUCT_REQ_INIT(prefix, suffix)  \
    FIELD_DEF(prefix,  HTTPc_FLAGS,                Flags,            suffix) /* Request set of flags.                   */ \
    FIELD_DEF(prefix,  HTTPc_FLAGS,                HdrFlags,         suffix) /* Set of flags for hdr to include in Req. */ \
    FIELD_DEF(prefix,  HTTP_METHOD,                Method,           suffix) /* HTTP Request Method.                    */ \
    FIELD_DEF(prefix,  CPU_CHAR,                  *ResourcePathPtr,  suffix) /* Pointer to URI or Resource path string. */ \
    FIELD_DEF(prefix,  CPU_INT16U,                 ResourcePathLen,  suffix) /* URI or Resource path string's length.   */ \
    FIELD_DEF(prefix,  HTTP_CONTENT_TYPE,          ContentType,      suffix) /* Content Type of the Request body.       */ \
    FIELD_DEF(prefix,  CPU_INT32U,                 ContentLen,       suffix) /* Content Length of the Request body.     */ \
    FIELD_DEF(prefix,  void,                      *DataPtr,          suffix) /* Pointer to data to put in Request body. */ \
    REQ_QUERY_STR_FIELDS_DEF(prefix, suffix)                                 /* Query String parameters.                */ \
    REQ_HDR_TX_FIELDS_DEF(prefix, suffix)                                    /* Request Header fields parameters.       */ \
    REQ_FORM_FIELDS_DEF(prefix, suffix)                                      /* Form parameters.                        */ \
    FIELD_DEF(prefix,  HTTPc_REQ_BODY_HOOK,        OnBodyTx,         suffix) /* Body Transfer hook parameter.           */ \
    REQ_HDR_RX_FIELD_DEF(prefix, suffix)                                     /* Response Header fields parameter.       */ \
    FIELD_DEF(prefix,  HTTPc_RESP_BODY_HOOK,       OnBodyRx,         suffix) /* Response body hook function.            */ \
    REQ_TASK_CALLBACK_FIELDS_DEF(prefix, suffix)                             /* Request's callback parameters.          */ \
    FIELD_DEF(prefix,  HTTPc_CONN,                *ConnPtr,          suffix) /* Pointer to Connection object.           */ \
    FIELD_DEF(prefix,  HTTPc_RESP,                *RespPtr,          suffix) /* Pointer to Response object.             */ \
    FIELD_DEF(prefix,  HTTPc_REQ,                 *NextPtr,          suffix) /* Pointer to next Request object.         */ \
    USER_DATA_FIELD_DEF(,)                                                   /* Pointer to user data.                   */


struct httpc_req_obj {
    STRUCT_REQ_INIT(const, _reserved)
};

struct httpc_req {
    STRUCT_REQ_INIT(,)
};


/*
*********************************************************************************************************
*                                        SOCKET SECURE CFG FIELD MACRO
*********************************************************************************************************
*/

#ifdef NET_SECURE_MODULE_EN
#define  SOCK_SECURE_CFG_FIELD_DEF(prefix, suffix)  FIELD_DEF(prefix, NET_APP_SOCK_SECURE_CFG, SockSecureCfg, suffix)  /* Connection's Socket Secure Cfg. */
#else
#define  SOCK_SECURE_CFG_FIELD_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                      CONNECTION CALLBACK FIELDS MACRO
*********************************************************************************************************
*/

#ifdef HTTPc_TASK_MODULE_EN
#define  TASK_CONN_CALLBACK_FIELDS_DEF(prefix, suffix)  FIELD_DEF(prefix,  HTTPc_CONNECT_CALLBACK,      OnConnect,  suffix) \
                                                        FIELD_DEF(prefix,  HTTPc_CONN_CLOSE_CALLBACK ,  OnClose,    suffix)
#else
#define  TASK_CONN_CALLBACK_FIELDS_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                       CONNECTION SIGNAL FIELDS MACRO
*********************************************************************************************************
*/

#ifdef HTTPc_SIGNAL_TASK_MODULE_EN
#define  TASK_CONN_SIGNAL_FIELDS_DEF(prefix, suffix)  FIELD_DEF(prefix,  KAL_SEM_HANDLE,   ConnectSignal,    suffix) \
                                                      FIELD_DEF(prefix,  KAL_SEM_HANDLE ,  TransDoneSignal,  suffix) \
                                                      FIELD_DEF(prefix,  KAL_SEM_HANDLE,   CloseSignal,      suffix)
#else
#define  TASK_CONN_SIGNAL_FIELDS_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                      CONNENCTION QUERY STRING FIELDS MACRO
*********************************************************************************************************
*/

#if (HTTPc_CFG_QUERY_STR_EN == DEF_ENABLED)
#define  CONN_QUERY_STR_FIELDS_DEF(prefix, suffix)  FIELD_DEF(prefix,  CPU_INT16U ,     ReqQueryStrTxIx,     suffix) \
                                                    FIELD_DEF(prefix,  HTTPc_KEY_VAL,  *ReqQueryStrTempPtr,  suffix)
#else
#define  CONN_QUERY_STR_FIELDS_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                       CONNECTION HEADER FIELDS MACRO
*********************************************************************************************************
*/

#if (HTTPc_CFG_HDR_TX_EN == DEF_ENABLED)
#define  CONN_HDR_FIELDS_DEF(prefix, suffix)  FIELD_DEF(prefix,  CPU_INT16U ,   ReqHdrTxIx,     suffix) \
                                              FIELD_DEF(prefix,  HTTPc_HDR,    *ReqHdrTempPtr,  suffix)
#else
#define  CONN_HDR_FIELDS_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                         CONECTION FORM FIELD MACRO
*********************************************************************************************************
*/

#if (HTTPc_CFG_FORM_EN == DEF_ENABLED)
#define  CONN_FORM_FIELD_DEF(prefix, suffix)  FIELD_DEF(prefix,  CPU_INT16U,  ReqFormDataTxIx,  suffix)
#else
#define  CONN_FORM_FIELD_DEF(prefix, suffix)
#endif


/*
*********************************************************************************************************
*                                       CONNECTION STRUCTURE MACRO
*********************************************************************************************************
*/

#define  STRUCT_CONN_INIT(prefix, suffix)  \
    FIELD_DEF(prefix,  NET_SOCK_ID,                 SockID,              suffix) /* Connection's Socket ID.                 */ \
    FIELD_DEF(prefix,  HTTPc_FLAGS,                 SockFlags,           suffix) /* Connection's Socket flags.              */ \
    SOCK_SECURE_CFG_FIELD_DEF(prefix, suffix)                                    /* Connection's Socket Secure Cfg.         */ \
    FIELD_DEF(prefix,  CPU_INT16U,                  ConnectTimeout_ms,   suffix) /* Connection Connect Timeout.             */ \
    FIELD_DEF(prefix,  CPU_INT16U,                  InactivityTimeout_s, suffix) /* Connection Inactivity Timeout.          */ \
    FIELD_DEF(prefix,  NET_PORT_NBR,                ServerPort,          suffix) /* Server Port number.                     */ \
    FIELD_DEF(prefix,  NET_SOCK_ADDR,               ServerSockAddr,      suffix) /* Server Socket address.                  */ \
    FIELD_DEF(prefix,  CPU_CHAR,                   *HostNamePtr,         suffix) /* Pointer to server hostname string.      */ \
    FIELD_DEF(prefix,  CPU_INT16U,                  HostNameLen,         suffix) /* Server Hostname length.                 */ \
    FIELD_DEF(prefix,  HTTPc_CONN_STATE,            State,               suffix) /* Connection State.                       */ \
    FIELD_DEF(prefix,  HTTPc_FLAGS,                 Flags,               suffix) /* Set of flags related to HTTP conn.      */ \
    FIELD_DEF(prefix,  HTTPc_CONN_CLOSE_STATUS,     CloseStatus,         suffix) /* Status of connection closed.            */ \
    FIELD_DEF(prefix,  HTTPc_ERR,                   ErrCode,             suffix) /* Error code of connection.               */ \
    TASK_CONN_CALLBACK_FIELDS_DEF(prefix, suffix)                                /* Connection's Callback functions.        */ \
    TASK_CONN_SIGNAL_FIELDS_DEF(prefix, suffix)                                  /* Conneciton's signals's handle.          */ \
    FIELD_DEF(prefix,  HTTPc_REQ,                  *ReqListHeadPtr,      suffix) /* Head of the Request list.               */ \
    FIELD_DEF(prefix,  HTTPc_REQ,                  *ReqListEndPtr,       suffix) /* End of the Request list.                */ \
    FIELD_DEF(prefix,  HTTPc_FLAGS,                 ReqFlags,            suffix) /* Req flags for internal process.         */ \
    CONN_QUERY_STR_FIELDS_DEF(prefix, suffix)                                    /* QueryStr param for internal process.    */ \
    CONN_HDR_FIELDS_DEF(prefix, suffix)                                          /* Header param for internal process.      */ \
    CONN_FORM_FIELD_DEF(prefix, suffix)                                          /* Form param for internal process.        */ \
    FIELD_DEF(prefix,  CPU_INT16U,                  ReqDataOffset,       suffix) /* Offset in Req Data Ptr to Tx.           */ \
    FIELD_DEF(prefix,  HTTPc_FLAGS,                 RespFlags,           suffix) /* Set of flags related to the resp.       */ \
    FIELD_DEF(prefix,  void,                       *TxDataPtr,           suffix) /* Pointer to data to transmit.            */ \
    FIELD_DEF(prefix,  CPU_CHAR,                   *BufPtr,              suffix) /* Pointer to conn buffer.                 */ \
    FIELD_DEF(prefix,  CPU_INT16U,                  BufLen,              suffix) /* Conn buffer's length.                   */ \
    FIELD_DEF(prefix,  CPU_CHAR,                   *RxBufPtr,            suffix) /* Pointer inside Buf where to Rx data.    */ \
    FIELD_DEF(prefix,  CPU_INT16U,                  RxDataLenRem,        suffix) /* Remaining data to process in the rx buf.*/ \
    FIELD_DEF(prefix,  CPU_INT32U,                  RxDataLen,           suffix) /* Data length received.                   */ \
    FIELD_DEF(prefix,  CPU_CHAR,                   *TxBufPtr,            suffix) /* Pointer inside Buf where to Tx data.    */ \
    FIELD_DEF(prefix,  CPU_INT16U,                  TxDataLen,           suffix) /* Length of data to Tx.                   */ \
    FIELD_DEF(      ,  HTTPc_CONN,                 *NextPtr,             suffix) /* Pointer to next conn in list.           */ \
    USER_DATA_FIELD_DEF( , )                                                     /* Pointer to user data.                   */


struct httpc_conn_obj {
      STRUCT_CONN_INIT(const, _reserved)
};

struct httpc_conn {
      STRUCT_CONN_INIT(,)
};


/*
*********************************************************************************************************
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void         HTTPc_Init                (const  HTTPc_CFG             *p_cfg,
                                        const  HTTPc_TASK_CFG        *p_task_cfg,
                                               void                  *p_mem_seg,
                                               HTTPc_ERR             *p_err);

void         HTTPc_ConnClr             (       HTTPc_CONN_OBJ        *p_conn_obj,
                                               HTTPc_ERR             *p_err);

void         HTTPc_ConnSetParam        (       HTTPc_CONN_OBJ        *p_conn_obj,
                                               HTTPc_PARAM_TYPE       type,
                                               void                  *p_param,
                                               HTTPc_ERR             *p_err);

CPU_BOOLEAN  HTTPc_ConnOpen            (       HTTPc_CONN_OBJ        *p_conn_obj,
                                               CPU_CHAR              *p_buf,
                                               CPU_INT16U             buf_len,
                                               CPU_CHAR              *p_hostname_str,
                                               CPU_INT16U             hostname_str_len,
                                               HTTPc_FLAGS            flags,
                                               HTTPc_ERR             *p_err);

void         HTTPc_ConnClose           (       HTTPc_CONN_OBJ        *p_conn_obj,
                                               HTTPc_FLAGS            flags,
                                               HTTPc_ERR             *p_err);

void         HTTPc_ReqClr              (       HTTPc_REQ_OBJ         *p_req_obj,
                                               HTTPc_ERR             *p_err);

void         HTTPc_ReqSetParam         (       HTTPc_REQ_OBJ         *p_req_obj,
                                               HTTPc_PARAM_TYPE       type,
                                               void                  *p_param,
                                               HTTPc_ERR             *p_err);

CPU_BOOLEAN  HTTPc_ReqSend             (       HTTPc_CONN_OBJ        *p_conn_obj,
                                               HTTPc_REQ_OBJ         *p_req_obj,
                                               HTTPc_RESP_OBJ        *p_resp_obj,
                                               HTTP_METHOD            method,
                                               CPU_CHAR              *p_resource_path,
                                               CPU_INT16U             resource_path_len,
                                               HTTPc_FLAGS            flags,
                                               HTTPc_ERR             *p_err);


CPU_INT32U   HTTPc_FormAppFmt          (       CPU_CHAR              *p_buf,
                                               CPU_INT16U             buf_len,
                                               HTTPc_FORM_TBL_FIELD  *p_form_tbl,
                                               CPU_INT16U             form_tbl_size,
                                               HTTPc_ERR             *p_err);


CPU_INT32U   HTTPc_FormMultipartFmt    (       CPU_CHAR              *p_buf,
                                               CPU_INT16U             buf_len,
                                               HTTPc_FORM_TBL_FIELD  *p_form_tbl,
                                               CPU_INT16U             form_tbl_size,
                                               HTTPc_ERR             *p_err);

void         HTTPc_FormAddKeyVal       (       HTTPc_FORM_TBL_FIELD  *p_form_tbl,
                                               HTTPc_KEY_VAL         *p_key_val,
                                               HTTPc_ERR             *p_err);

void         HTTPc_FormAddKeyValExt    (       HTTPc_FORM_TBL_FIELD  *p_form_tbl,
                                               HTTPc_KEY_VAL_EXT     *p_key_val_ext,
                                               HTTPc_ERR             *p_err);

void         HTTPc_FormAddFile         (       HTTPc_FORM_TBL_FIELD  *p_form_tbl,
                                               HTTPc_MULTIPART_FILE  *p_file_obj,
                                               HTTPc_ERR             *p_err);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif  /* HTTPc_MODULE_PRESENT  */
