/*
*********************************************************************************************************
*                                       EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                                EXAMPLE
*
*                                  HTTP CLIENT APPLICATION FUNCTIONS FILE
*
* Filename      : http-c_app.c
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
*                                           INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#define    HTTPc_APP_MODULE
#include  <stdio.h>

#include  "http-c_app.h"
#include  "http-c_hooks.h"
#include  "webpages.h"

#if (HTTPc_APP_FS_MODULE_PRESENT == DEF_YES)
#include  <fs_app.h>
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                       LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

static  CPU_INT08U   HTTPcApp_ReqPrepareQueryStr      (HTTPc_KEY_VAL         **p_tbl);



/*
*********************************************************************************************************
*                                            HTTPcApp_Init()
*
* Description : Initialize the µC/HTTP-client stack for the example application.
*
* Argument(s) : None.
*
* Return(s)   : DEF_OK,   if initialization was successful.
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  HTTPcApp_Init (void)
{
    HTTPc_ERR    httpc_err;

                                                                /* ------------- INITIALIZE CLIENT SUITE -------------- */
#if (HTTPc_CFG_MODE_ASYNC_TASK_EN == DEF_ENABLED)
    HTTPc_Init(&HTTPc_Cfg, &HTTPc_TaskCfg, DEF_NULL, &httpc_err);
    if (httpc_err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }
#else
    HTTPc_Init(&HTTPc_Cfg, DEF_NULL, DEF_NULL, &httpc_err);
    if (httpc_err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }
#endif

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                       HTTPcApp_PersistentConn()
*
* Description : Establish a persistent connection with the open weather map server
*
* Argument(s) : None.
*
* Return(s)   : DEF_OK,   if persistent connection was successfully established
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  HTTPcApp_PersistentConn (void)
{
    HTTPc_CONN_OBJ      *p_conn;
    CPU_CHAR            *p_buf;
    HTTPc_FLAGS          flags;
    CPU_SIZE_T           str_len;
    CPU_BOOLEAN          persistent;
    HTTPc_ERR            err;


    p_conn  = &HTTPcApp_ConnTbl[0];
    p_buf   = &HTTPcApp_ConnBufTbl[0][0];

                                                                /* ----------- INIT NEW CONNECTION & REQUEST ---------- */
    HTTPc_ConnClr(p_conn, &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }
                                                                /* ------------- SET CONNECTION PARAMETERS ------------ */
    persistent = DEF_YES;
    HTTPc_ConnSetParam(p_conn,
                       HTTPc_PARAM_TYPE_PERSISTENT,
                      &persistent,
                      &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }

                                                                /* ------------- SET CONNECTION CALLBACKS ------------- */
#if (HTTPc_CFG_MODE_ASYNC_TASK_EN == DEF_ENABLED)
    HTTPc_ConnSetParam(         p_conn,
                                HTTPc_PARAM_TYPE_CONN_CLOSE_CALLBACK,
                       (void *)&HTTPcApp_ConnCloseCallback,
                               &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }
#endif
                                                                /* ----------------- OPEN CONNECTION ------------------ */
    str_len = Str_Len(HTTP_SERVER_HOSTNAME);
    flags  = HTTPc_FLAG_NONE;


    HTTPc_ConnOpen(p_conn,
                   p_buf,
                   HTTPc_APP_CFG_CONN_BUF_SIZE,
                   HTTP_SERVER_HOSTNAME,
                   str_len,
                   flags,
                  &err);

    if (err != HTTPc_ERR_NONE) {
        HTTPc_APP_TRACE_INFO(("Connect error: %i\n\r", err));
    }



    return (DEF_OK);
}

/*
*********************************************************************************************************
*                                       HTTPcApp_ReqWeather()
*
* Description : This function establishes a connection (non-persistent) to the open weather map server
*               and sends a request for the current weather conditions in the city established by
*               HTTPc_APP_CFG_QUERY_STR_CITY.
*
* Argument(s) : None.
*
* Return(s)   : DEF_OK,   if persistent connection was successfully established
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  HTTPcApp_ReqWeather (void)
{
    HTTPc_CONN_OBJ      *p_conn;
    HTTPc_REQ_OBJ       *p_req1;
    HTTPc_RESP_OBJ      *p_resp1;
    HTTPc_FLAGS          flags;
    CPU_SIZE_T           str_len;
    HTTPc_PARAM_TBL      tbl_obj;
    HTTPc_KEY_VAL       *p_query_str_tbl;
    CPU_INT08U           query_nbr;
    CPU_CHAR            *p_buf;
    HTTPc_ERR            err;



    p_conn  = &HTTPcApp_ConnTbl[0];

    p_req1  = &HTTPcApp_ReqTbl[0];
    p_resp1 = &HTTPcApp_RespTbl[0];

    p_req1->UserDataPtr = (void *)&HTTPcApp_Data[0];

    p_buf   = &HTTPcApp_ConnBufTbl[0][0];

                                                                /* ----------- INIT NEW CONNECTION & REQUEST ---------- */
    HTTPc_ConnClr(p_conn, &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }


#if (HTTPc_CFG_MODE_ASYNC_TASK_EN == DEF_ENABLED)
    HTTPc_ConnSetParam(         p_conn,
                                HTTPc_PARAM_TYPE_CONN_CLOSE_CALLBACK,
                       (void *)&HTTPcApp_ConnCloseCallback,
                               &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }
#endif
                                                                /* ----------------- OPEN CONNECTION ------------------ */
    str_len = Str_Len(HTTP_SERVER_HOSTNAME);
    flags  = HTTPc_FLAG_NONE;


    HTTPc_ConnOpen(p_conn,
                   p_buf,
                   HTTPc_APP_CFG_CONN_BUF_SIZE,
                   HTTP_SERVER_HOSTNAME,
                   str_len,
                   flags,
                  &err);

    if (err != HTTPc_ERR_NONE) {
        HTTPc_APP_TRACE_INFO(("Connect error: %i\n\r", err));
        return (DEF_FAIL);
    }

    HTTPc_ReqClr(p_req1, &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }
                                                             /* ------------ SET REQ/RESP HOOK FUNCTIONS ----------- */
    HTTPc_ReqSetParam(         p_req1,
                               HTTPc_PARAM_TYPE_RESP_HDR_HOOK,
                      (void *)&HTTPcApp_RespHdrHook,
                              &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }

    HTTPc_ReqSetParam(         p_req1,
                               HTTPc_PARAM_TYPE_RESP_BODY_HOOK,
                      (void *)&HTTPcApp_RespBodyHook,
                              &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }

                                                                /* --------- SET REQ/RESP CALLBACK FUNCTIONS ---------- */
#if (HTTPc_CFG_MODE_ASYNC_TASK_EN == DEF_ENABLED)
    HTTPc_ReqSetParam(         p_req1,
                               HTTPc_PARAM_TYPE_TRANS_COMPLETE_CALLBACK,
                      (void *)&HTTPcApp_TransDoneCallback,
                              &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }

    HTTPc_ReqSetParam(         p_req1,
                               HTTPc_PARAM_TYPE_TRANS_ERR_CALLBACK,
                      (void *)&HTTPcApp_TransErrCallback,
                              &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }
#endif

    query_nbr = HTTPcApp_ReqPrepareQueryStr(&p_query_str_tbl);
    if (query_nbr <= 0) {
        return (DEF_FAIL);
    }

                                                                /* ------------ SET STRING QUERY PARAMETERS ----------- */
    tbl_obj.EntryNbr = query_nbr;
    tbl_obj.TblPtr   = (void *)p_query_str_tbl;
    HTTPc_ReqSetParam(p_req1, HTTPc_PARAM_TYPE_REQ_QUERY_STR_TBL, &tbl_obj, &err);
    if (err != HTTPc_ERR_NONE) {
        return (DEF_FAIL);
    }

                                                                /* ---------------- SEND HTTP REQUEST ----------------- */
    str_len = Str_Len("/data/2.5/weather");
    flags = HTTPc_FLAG_NONE;

    (void)HTTPc_ReqSend(p_conn,
                        p_req1,
                        p_resp1,
                        HTTP_METHOD_GET,
                        HTTPc_APP_CFG_URI,
                        str_len,
                        flags,
                       &err);
    if (err != HTTPc_ERR_NONE) {
        HTTPc_APP_TRACE_INFO(("Request error: %i\n\r", err));
        return (DEF_FAIL);
    }

    return (DEF_OK);
}

/*
*********************************************************************************************************
*                                       HTTPcApp_CloseConn()
*
* Description : Close the connection to the weather server.
*
* Argument(s) : None.
*
* Return(s)   : DEF_OK,   if persistent connection was successfully established
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  HTTPcApp_CloseConn (void)
{
    HTTPc_ERR        err;
    HTTPc_CONN_OBJ  *p_conn;


    p_conn  = &HTTPcApp_ConnTbl[0];

    HTTPc_ConnClose (p_conn, HTTPc_FLAG_NONE, &err);
    if (err != HTTPc_ERR_NONE) {
        HTTPc_APP_TRACE_INFO(("Close error: %i\n\r", err));
        return (DEF_FAIL);
    }

    return (DEF_OK);

}

/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     HTTPcApp_ReqPrepareQueryStr()
*
* Description : Configure the Query String table.
*
* Argument(s) : p_tbl   Variable that will received the pointer to the Query String Table.
*
* Return(s)   : Number of fields in the table.
*
* Caller(s)   : HTTPcApp_ReqSendGet().
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  CPU_INT08U  HTTPcApp_ReqPrepareQueryStr (HTTPc_KEY_VAL  **p_tbl)
{
    HTTPc_KEY_VAL  *p_kvp;


                                                                /* ------------------- SET QUERY ---------------------- */
    p_kvp         = &HTTPcApp_ReqQueryStrTbl[0];
    p_kvp->KeyPtr = &HTTPcApp_ReqQueryStrKeyTbl[0][0];
    p_kvp->ValPtr = &HTTPcApp_ReqQueryStrValTbl[0][0];

   (void)Str_Copy_N(p_kvp->KeyPtr, "q",       HTTPc_APP_CFG_QUERY_STR_KEY_LEN_MAX);
   (void)Str_Copy_N(p_kvp->ValPtr, HTTPc_APP_CFG_QUERY_STR_CITY, HTTPc_APP_CFG_QUERY_STR_VAL_LEN_MAX);

    p_kvp->KeyLen = Str_Len(&HTTPcApp_ReqQueryStrKeyTbl[0][0]);
    p_kvp->ValLen = Str_Len(&HTTPcApp_ReqQueryStrValTbl[0][0]);

   *p_tbl = &HTTPcApp_ReqQueryStrTbl[0];

    return (1);
}




