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
*                                               EXAMPLE
*
*                                    HTTP CLIENT HOOK FUNCTIONS FILE
*
* Filename      : http-c_hooks.c
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

#include  <stdio.h>

#include  "http-c_hooks.h"
#include  "http-c_app.h"
#include  "webpages.h"


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*********************************************************************************************************
*/

#define  HTTP_JSON_MAX_TOKEN_LEN  50

/*
*********************************************************************************************************
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*********************************************************************************************************
*/


CPU_CHAR HTTPcApp_Token[HTTP_JSON_MAX_TOKEN_LEN];

/*
*********************************************************************************************************
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      HTTPcApp_ReqQueryStrHook()
*
* Description : Add a Query String field to a specific HTTP Request.
*
* Argument(s) : p_conn      Pointer to current HTTPc Connection object.
*
*               p_req       Pointer to current HTTPc Request object.
*
*               p_key_val   Pointer to key-value pair to recover from application.
*
* Return(s)   : DEF_YES,    if all the fields of the Query String have been added.
*               DEF_NO,     otherwise.
*
* Caller(s)   : HTTPcReq_QueryStrHook() vis 'p_req->OnQueryStrTx()'.
*
* Note(s)     : (1) In this example function, the query string will be added to all the requests on any
*                   connections.
*********************************************************************************************************
*/

CPU_BOOLEAN  HTTPcApp_ReqQueryStrHook (HTTPc_CONN_OBJ     *p_conn,
                                       HTTPc_REQ_OBJ      *p_req,
                                       HTTPc_KEY_VAL     **p_key_val)
{
    return (DEF_YES);
}


/*
*********************************************************************************************************
*                                          HTTPcApp_ReqHdrHook()
*
* Description : Add an header field to a specific HTTP Request.
*
* Argument(s) : p_conn      Pointer to current HTTPc Connection object.
*
*               p_req       Pointer to current HTTPc Request object.
*
*               p_hdr       Pointer to header field to recover from application.
*
* Return(s)   : DEF_YES,    if all header fields have been added.
*               DEF_NO,     otherwise.
*
* Caller(s)   : HTTPcReq_HdrExtHook() via 'p_req->OnHdrTx()'
*
* Note(s)     : (1) In this example function, the header field will be added to all the requests on any
*                   connections.
*********************************************************************************************************
*/

CPU_BOOLEAN  HTTPcApp_ReqHdrHook (HTTPc_CONN_OBJ     *p_conn,
                                  HTTPc_REQ_OBJ      *p_req,
                                  HTTPc_HDR         **p_hdr)
{
    return (DEF_YES);
}


/*
*********************************************************************************************************
*                                          HTTPcApp_ReqBodyHook()
*
* Description : Specify the data to be sent in the Request body.
*
* Argument(s) : p_conn      Pointer to current HTTPc Connection object.
*
*               p_req       Pointer to current HTTPc Request object.
*
*               p_data      Variable that will received the pointer to the data to include in the HTTP request.
*
*               p_buf       Pointer to HTTP transmit buffer.
*
*               buf_len     Length of space remaining in  the HTTP transmit buffer.
*
*               p_data_len  Length of the data.
*
* Return(s)   : DEF_YES, if all data to transmit was passed by the application
*               DEF_NO,  if data still remaining to be sent.
*
* Caller(s)   : HTTPcReq_BodyData() via 'p_req->OnBodyTx()'
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  HTTPcApp_ReqBodyHook (HTTPc_CONN_OBJ     *p_conn,
                                   HTTPc_REQ_OBJ      *p_req,
                                   void              **p_data,
                                   CPU_CHAR           *p_buf,
                                   CPU_INT16U          buf_len,
                                   CPU_INT16U         *p_data_len)
{
    return (DEF_YES);
}


/*
*********************************************************************************************************
*                                        HTTPcApp_RespHdrHook()
*
* Description : Retrieve header fields in the HTTP response received.
*
* Argument(s) : p_conn      Pointer to current HTTPc Connection object.
*
*               p_req       Pointer to current HTTPc Request object.
*
*               hdr_field   HTTP header type of the header field received in the HTTP response.
*
*               p_hdr_val   Pointer to the value string received in the Response header field.
*
*               val_len     Length of the value string.
*
* Return(s)   : None.
*
* Caller(s)   : HTTPcResp_ParseHdr() via 'p_req->OnHdrRx()'
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  HTTPcApp_RespHdrHook (HTTPc_CONN_OBJ    *p_conn,
                            HTTPc_REQ_OBJ     *p_req,
                            HTTP_HDR_FIELD     hdr_field,
                            CPU_CHAR          *p_hdr_val,
                            CPU_INT16U         val_len)
{

}


/*
*********************************************************************************************************
*                                       HTTPcApp_RespBodyHook()
*
* Description : This function finds the "temp" field in the provided JSON script and print the 
*               associated value.
*
* Argument(s) : p_conn          Pointer to current HTTPc Connection object.
*
*               p_req           Pointer to current HTTPc Request object.
*
*               content_type    HTTP Content Type of the HTTP Response body's data.
*
*               p_data          Pointer to a data piece of the HTTP Response body.
*
*               data_len        Length of the data piece received.
*
*               last_chunk      DEF_YES, if this is the last piece of data.
*
*                               DEF_NO,  if more data is up coming.
*
* Return(s)   : None.
*
* Caller(s)   : HTTPcResp_BodyStd()   via 'p_req->OnBodyRx()'
*               HTTPcResp_BodyChunk() via 'p_req->OnBodyRx()'
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  HTTPcApp_RespBodyHook (HTTPc_CONN_OBJ     *p_conn,
                             HTTPc_REQ_OBJ      *p_req,
                             HTTP_CONTENT_TYPE   content_type,
                             void               *p_data,
                             CPU_INT16U          data_len,
                             CPU_BOOLEAN         last_chunk)
{
    CPU_INT08U  decimal_flag;
    CPU_INT16U  cnt;
    CPU_INT16U  idx1;
    CPU_INT16U  idx2;
    CPU_INT32U  temp;
    CPU_FP64    val_complete;
    CPU_FP64    val_fraction;
    
    
    if (data_len > 0) {
        cnt  = 0;
        idx1 = 0;
        idx2 = 0;
    
        Mem_Copy(&HTTPcApp_Buf[0], p_data, data_len);
    
        while (cnt < data_len) {
            if (idx1 == 0) {
                if (HTTPcApp_Buf[cnt] == '\"') {                /* Look for the opening quotation mark                  */
                    idx1  = ++cnt;
                } else {
                    cnt++;
                }    
            } else {
                if (HTTPcApp_Buf[cnt] == '\"') {                /* Look for the closing quotation mark                  */
                    idx2 = cnt++;                 
                                                                /* Copy the string in quotes                            */
                    Str_Copy_N (&HTTPcApp_Token[0], &HTTPcApp_Buf[idx1], idx2 - idx1);
                    HTTPcApp_Token[idx2 - idx1] = '\0';
                    if ((Str_Cmp (&HTTPcApp_Token[0], "temp")) == 0) {
                        idx1 = ++cnt;
                        decimal_flag = 0;
                        while ((cnt < data_len) && (idx1 != 0)){
                            if (HTTPcApp_Buf[cnt] == '.') {
                                idx2 = cnt++;  
                                Str_Copy_N (&HTTPcApp_Token[0], &HTTPcApp_Buf[idx1], idx2 - idx1);
                                HTTPcApp_Token[idx2 - idx1] = '\0';
                                                                /* Format the value preceding the decimal point         */
                                temp = Str_ParseNbr_Int32U(&HTTPcApp_Token[0], (CPU_CHAR **)0, 10);
                                val_complete = (CPU_FP64)temp;
                                decimal_flag = 1;
                                idx1 = cnt;
                            } else if (HTTPcApp_Buf[cnt] == ',') {
                                idx2 = cnt++;
                                Str_Copy_N (&HTTPcApp_Token[0], &HTTPcApp_Buf[idx1], idx2 - idx1);
                                HTTPcApp_Token[idx2 - idx1] = '\0';
                                                                /* Format the value following the decimal point         */
                                temp = Str_ParseNbr_Int32U(&HTTPcApp_Token[0], (CPU_CHAR **)0, 10);
                                val_fraction = (CPU_FP64)temp;
                                if (decimal_flag != 0) {
                                   val_complete = val_complete + (val_fraction / 100.0);
                                } else {
                                    val_complete = val_fraction;  
                                }
                                                                /* Convert the total floating-point value to Fahrenheit */
                                val_complete = (1.8 * (val_complete - 273)) + 32;
                                                                /* Print the floating-point value                       */
                                HTTPc_APP_TRACE_INFO(("Current Ft. Lauderdale Temp = %.1fF\n", val_complete));
                                idx1 = 0;
                                idx2 = 0;
                            } else {
                                 cnt++;
                            }
                        }
                    } else {
                        idx1 = 0;
                        idx2 = 0;
                    }
                } else {
                    cnt++;
                }
            }
        }
    }
}


/*
*********************************************************************************************************
*                                     HTTPcApp_FormMultipartHook()
*
* Description : Retrieve the value data for an Key-Val Extended object.
*
* Argument(s) : p_conn          Pointer to current HTTPc Connection object.
*
*               p_req           Pointer to current HTTPc Request object.
*
*               p_key_val_obj   Pointer to current Key-Value Extended object.
*
*               p_buf           Pointer to HTTP transmit buffer.
*
*               buf_len         Size remaining in HTTP buffer.
*
*               p_len_wr        Variable that will received the size of the data copied in the buffer.
*
* Return(s)   : DEF_YES, if all the data was transmitted.
*               DEF_NO,  otherwise.
*
* Caller(s)   : HTTPcApp_ReqPrepareFormMultipart().
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  HTTPcApp_FormMultipartHook (HTTPc_CONN_OBJ     *p_conn,
                                         HTTPc_REQ_OBJ      *p_req,
                                         HTTPc_KEY_VAL_EXT  *p_key_val_obj,
                                         CPU_CHAR           *p_buf,
                                         CPU_INT16U          buf_len,
                                         CPU_INT16U         *p_len_wr)
{
    return (DEF_YES);
}


/*
*********************************************************************************************************
*                                   HTTPcApp_FormMultipartFileHook()
*
* Description : Retrieve the file data for a Multipart File object.
*
* Argument(s) : p_conn      Pointer to current HTTPc Connection object.
*
*               p_req       Pointer to current HTTPc Request object.
*
*               p_file_obj  Pointer to current Multipart File object.
*
*               p_buf       Pointer to HTTP transmit buffer.
*
*               buf_len     Size remaining in HTTP buffer.
*
*               p_len_wr    Variable that will received the size of the data copied in the buffer.
*
* Return(s)   : DEF_YES, if all the data was transmitted.
*               DEF_NO,  otherwise.
*
* Caller(s)   : HTTPcApp_ReqPrepareFormMultipart().
*
* Note(s)     : None.
*********************************************************************************************************
*/
#if (HTTPc_APP_FS_MODULE_PRESENT == DEF_YES)
CPU_BOOLEAN  HTTPcApp_FormMultipartFileHook (HTTPc_CONN_OBJ        *p_conn,
                                             HTTPc_REQ_OBJ         *p_req,
                                             HTTPc_MULTIPART_FILE  *p_file_obj,
                                             CPU_CHAR              *p_buf,
                                             CPU_INT16U             buf_len,
                                             CPU_INT16U            *p_len_wr)
{
    return (DEF_YES);
}
#endif


/*
*********************************************************************************************************
*                                      HTTPcApp_ConnConnectCallback()
*
* Description : Callback to notify application that an HTTP connection connect process was completed.
*
* Argument(s) : p_conn          Pointer to current HTTPc Connection.
*
*               open_status     Status of the connection:
*
*                               DEF_OK,   if the connection with the server was successful.
*                               DEF_FAIL, otherwise.
*
* Return(s)   : None.
*
* Caller(s)   : HTTPcTask_Handler() via 'p_conn->OnConnect()'.
*
* Note(s)     : None.
*********************************************************************************************************
*/
#ifdef HTTPc_TASK_MODULE_EN
void  HTTPcApp_ConnConnectCallback (HTTPc_CONN_OBJ  *p_conn,
                                    CPU_BOOLEAN      open_status)
{
    if (open_status == DEF_OK) {
        HTTPc_APP_TRACE_INFO(("Connection to server succeeded.\n\r"));
    } else {
        HTTPc_APP_TRACE_INFO(("Connection to server failed.\n\r"));
    }
}
#endif


/*
*********************************************************************************************************
*                                     HTTPcApp_ConnCloseCallback()
*
* Description : Callback to notify application that an HTTP connection was closed.
*
* Argument(s) : p_conn          Pointer to current HTTPc Connection.
*
*               close_status    Status of the connection closing:
*                                   HTTPc_CONN_CLOSE_STATUS_ERR_INTERNAL
*                                   HTTPc_CONN_CLOSE_STATUS_SERVER
*                                   HTTPc_CONN_CLOSE_STATUS_NO_PERSISTENT
*                                   HTTPc_CONN_CLOSE_STATUS_APP
*
*               err             Error Code when connection was closed.
*
* Return(s)   : None.
*
* Caller(s)   : Various, via 'p_conn->OnClose()'
*
* Note(s)     : none.
*********************************************************************************************************
*/
#ifdef HTTPc_TASK_MODULE_EN
void  HTTPcApp_ConnCloseCallback (HTTPc_CONN_OBJ           *p_conn,
                                  HTTPc_CONN_CLOSE_STATUS   close_status,
                                  HTTPc_ERR                 err)
{
    HTTPc_APP_TRACE_INFO(("Connection closed.\n\r"));
}
#endif


/*
*********************************************************************************************************
*                                     HTTPcApp_TransDoneCallback()
*
* Description : Callback to notify application that an HTTP transaction was completed.
*
* Argument(s) : p_conn  Pointer to current HTTPc Connection object.
*
*               p_req   Pointer to current HTTPc Request object.
*
*               p_resp  Pointer to current HTTPc Response object.
*
*               status  Status of the transaction:
*
*                           DEF_OK,   transaction was successful.
*                           DEF_FAIL, otherwise.
*
* Return(s)   : None.
*
* Caller(s)   : Various, via 'p_req->OnTransComplete()'.
*
* Note(s)     : None.
*********************************************************************************************************
*/
#ifdef HTTPc_TASK_MODULE_EN
void  HTTPcApp_TransDoneCallback (HTTPc_CONN_OBJ  *p_conn,
                                  HTTPc_REQ_OBJ   *p_req,
                                  HTTPc_RESP_OBJ  *p_resp,
                                  CPU_BOOLEAN      status)
{
    HTTPc_APP_REQ_DATA  *p_data;
    HTTPc_REQ_OBJ       *p_req1;
    CPU_SR_ALLOC();


    p_req1 = &HTTPcApp_ReqTbl[0];

    if (status == DEF_OK) {
        HTTPc_APP_TRACE_INFO(("Transaction Status Code: %s\n\r", p_resp->ReasonPhrasePtr));
    } else {
        HTTPc_APP_TRACE_INFO(("Transaction failed\n\r"));
    }

    if (p_req == p_req1) {
        p_data = (HTTPc_APP_REQ_DATA *)p_req->UserDataPtr;
        CPU_CRITICAL_ENTER();
        p_data->Done = DEF_YES;
        CPU_CRITICAL_EXIT();
    }
}
#endif


/*
*********************************************************************************************************
*                                      HTTPcApp_TransErrCallback()
*
* Description : Callback to notify application that an error occurred during an HTTP transaction.
*
* Argument(s) : p_conn      Pointer to current HTTPc Connection object.
*
*               p_req       Pointer to current HTTPc Request object.
*
*               err_code    Error Code.
*
* Return(s)   : None.
*
* Caller(s)   : Various, via 'p_req->OnErr()'.
*
* Note(s)     : None.
*********************************************************************************************************
*/
#ifdef HTTPc_TASK_MODULE_EN
void HTTPcApp_TransErrCallback (HTTPc_CONN_OBJ  *p_conn,
                                HTTPc_REQ_OBJ   *p_req,
                                HTTPc_ERR        err_code)
{
    HTTPc_APP_TRACE_INFO(("Transaction error: %i\n\r", err_code));

}
#endif
