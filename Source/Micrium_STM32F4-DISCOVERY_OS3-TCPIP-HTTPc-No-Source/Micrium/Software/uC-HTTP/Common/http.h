/*
*********************************************************************************************************
*                                              uC/HTTP
*                                      Hypertext Transfer Protocol
*
*                          (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/HTTP is provided in source form to registered licensees ONLY.  It is
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
*                                                HTTP
*
* Filename      : http.h
* Version       : V1.00.00
* Programmer(s) : MM
*********************************************************************************************************
* Note(s)       : (1) The http.c/h files gather defines, data types, structures and functions that are
*                     common to HTTP client and server.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This main network protocol suite header file is protected from multiple pre-processor
*               inclusion through use of the HTTP module present pre-processor macro definition.
*
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  HTTP_MODULE_PRESENT                                   /* See Note #1.                                         */
#define  HTTP_MODULE_PRESENT


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         HTTP INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>
#include  <lib_str.h>
#include  <lib_ascii.h>

#include  <FS/net_fs.h>

#include  <Source/net.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*********************************************************************************************************
*/

#if ((defined(HTTP_MODULE)) && \
     (defined(HTTP_GLOBALS_EXT)))
#define  HTTP_EXT
#else
#define  HTTP_EXT  extern
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
*                                       HTTP DEFAUT PORT DEFINES
*********************************************************************************************************
*/

#define  HTTP_DFLT_PORT_NBR                    80
#define  HTTP_DFLT_PORT_NBR_SECURE            443


/*
*********************************************************************************************************
*                                         URL ENCODING DEFINES
*********************************************************************************************************
*/

#define  HTTP_URL_ENCODING_LEN                  3
#define  HTTP_URL_ENCODING_JUMP                 2


/*
*********************************************************************************************************
*                                     HEXADECIMAL STRING DEFINE
*********************************************************************************************************
*/

#define  HTTP_INT_16U_HEX_STR_LEN_MAX         4u


/*
*********************************************************************************************************
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         METHODS ENUMARATION
*********************************************************************************************************
*/

typedef enum http_method {
    HTTP_METHOD_GET,
    HTTP_METHOD_POST,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_PUT,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_OPTIONS,
    HTTP_METHOD_TRACE,
    HTTP_METHOD_CONNECT,
    HTTP_METHOD_UNKNOWN
} HTTP_METHOD;


/*
*********************************************************************************************************
*                                      STATUS CODES ENUMARATION
*********************************************************************************************************
*/

typedef enum http_status_code {
    HTTP_STATUS_OK,
    HTTP_STATUS_CREATED,
    HTTP_STATUS_ACCEPTED,
    HTTP_STATUS_NO_CONTENT,
    HTTP_STATUS_RESET_CONTENT,
    HTTP_STATUS_MOVED_PERMANENTLY,
    HTTP_STATUS_FOUND,
    HTTP_STATUS_SEE_OTHER,
    HTTP_STATUS_NOT_MODIFIED,
    HTTP_STATUS_USE_PROXY,
    HTTP_STATUS_TEMPORARY_REDIRECT,
    HTTP_STATUS_BAD_REQUEST,
    HTTP_STATUS_UNAUTHORIZED,
    HTTP_STATUS_FORBIDDEN,
    HTTP_STATUS_NOT_FOUND,
    HTTP_STATUS_METHOD_NOT_ALLOWED,
    HTTP_STATUS_NOT_ACCEPTABLE,             /* With the Accept Req Hdr */
    HTTP_STATUS_REQUEST_TIMEOUT,
    HTTP_STATUS_CONFLICT,
    HTTP_STATUS_GONE,
    HTTP_STATUS_LENGTH_REQUIRED,
    HTTP_STATUS_PRECONDITION_FAILED,
    HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE,
    HTTP_STATUS_REQUEST_URI_TOO_LONG,
    HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE,
    HTTP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE,
    HTTP_STATUS_EXPECTATION_FAILED,
    HTTP_STATUS_INTERNAL_SERVER_ERR,
    HTTP_STATUS_NOT_IMPLEMENTED,
    HTTP_STATUS_SERVICE_UNAVAILABLE,
    HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED,
    HTTP_STATUS_UNKOWN
} HTTP_STATUS_CODE;


/*
*********************************************************************************************************
*                                     HTTPS HEADER ENUMARATION
*********************************************************************************************************
*/

typedef  enum http_hdr_field {
    HTTP_HDR_FIELD_UNKNOWN,
    HTTP_HDR_FIELD_CONTENT_TYPE,
    HTTP_HDR_FIELD_CONTENT_LEN,
    HTTP_HDR_FILED_CONTENT_DISPOSITION,
    HTTP_HDR_FIELD_HOST,
    HTTP_HDR_FIELD_LOCATION,
    HTTP_HDR_FIELD_CONN,
    HTTP_HDR_FIELD_TRANSFER_ENCODING,
    HTTP_HDR_FIELD_ACCEPT,
    HTTP_HDR_FIELD_ACCEPT_CHARSET,
    HTTP_HDR_FIELD_ACCEPT_ENCODING,
    HTTP_HDR_FIELD_ACCEPT_LANGUAGE,
    HTTP_HDR_FIELD_ACCEPT_RANGES,
    HTTP_HDR_FIELD_AGE,
    HTTP_HDR_FIELD_ALLOW,
    HTTP_HDR_FIELD_AUTHORIZATION,
    HTTP_HDR_FIELD_CONTENT_ENCODING,
    HTTP_HDR_FIELD_CONTENT_LANGUAGE,
    HTTP_HDR_FIELD_CONTENT_LOCATION,
    HTTP_HDR_FIELD_CONTENT_MD5,
    HTTP_HDR_FIELD_CONTENT_RANGE,
    HTTP_HDR_FIELD_COOKIE,
    HTTP_HDR_FIELD_COOKIE2,
    HTTP_HDR_FIELD_DATE,
    HTTP_HDR_FIELD_ETAG,
    HTTP_HDR_FIELD_EXPECT,
    HTTP_HDR_FIELD_EXPIRES,
    HTTP_HDR_FIELD_FROM,
    HTTP_HDR_FIELD_IF_MODIFIED_SINCE,
    HTTP_HDR_FIELD_IF_MATCH,
    HTTP_HDR_FIELD_IF_NONE_MATCH,
    HTTP_HDR_FIELD_IF_RANGE,
    HTTP_HDR_FIELD_IF_UNMODIFIED_SINCE,
    HTTP_HDR_FIELD_LAST_MODIFIED,
    HTTP_HDR_FIELD_RANGE,
    HTTP_HDR_FIELD_REFERER,
    HTTP_HDR_FIELD_RETRY_AFTER,
    HTTP_HDR_FIELD_SERVER,
    HTTP_HDR_FIELD_SET_COOKIE,
    HTTP_HDR_FIELD_SET_COOKIE2,
    HTTP_HDR_FIELD_TE,
    HTTP_HDR_FIELD_TRAILER,
    HTTP_HDR_FIELD_UPGRATE,
    HTTP_HDR_FIELD_USER_AGENT,
    HTTP_HDR_FIELD_VARY,
    HTTP_HDR_FIELD_VIA,
    HTTP_HDR_FIELD_WARNING,
    HTTP_HDR_FIELD_WWW_AUTHENTICATE
} HTTP_HDR_FIELD;


/*
*********************************************************************************************************
*                                     HTTPS VERSIONS ENUMARATION
*********************************************************************************************************
*/

typedef  enum  http_protocol_ver {
    HTTP_PROTOCOL_VER_0_9,
    HTTP_PROTOCOL_VER_1_0,
    HTTP_PROTOCOL_VER_1_1,
    HTTP_PROTOCOL_VER_UNKNOWN
} HTTP_PROTOCOL_VER;


/*
*********************************************************************************************************
*                                      CONTENT TYPES ENUMARATION
*********************************************************************************************************
*/

typedef enum http_content_type {
    HTTP_CONTENT_TYPE_UNKNOWN,
    HTTP_CONTENT_TYPE_NONE,
    HTTP_CONTENT_TYPE_HTML,
    HTTP_CONTENT_TYPE_OCTET_STREAM,
    HTTP_CONTENT_TYPE_PDF,
    HTTP_CONTENT_TYPE_ZIP,
    HTTP_CONTENT_TYPE_GIF,
    HTTP_CONTENT_TYPE_JPEG,
    HTTP_CONTENT_TYPE_PNG,
    HTTP_CONTENT_TYPE_JS,
    HTTP_CONTENT_TYPE_PLAIN,
    HTTP_CONTENT_TYPE_CSS,
    HTTP_CONTENT_TYPE_JSON,
    HTTP_CONTENT_TYPE_APP_FORM,
    HTTP_CONTENT_TYPE_MULTIPART_FORM
} HTTP_CONTENT_TYPE;


/*
*********************************************************************************************************
*                             CONTENT DISPOSITION TYPE VALUES ENUMARATION
*********************************************************************************************************
*/

typedef enum http_content_disposition {
    HTTP_CONTENT_DISPOSITION_FORM_DATA
} HTTP_CONTENT_DISPOSITION;


/*
*********************************************************************************************************
*                             HEADER FIELD CONNECTION VALUES ENUMARATION
*********************************************************************************************************
*/

typedef enum http_hdr_field_conn_val {
    HTTP_HDR_FIELD_CONN_CLOSE,
    HTTP_HDR_FIELD_CONN_PERSISTENT,
    HTTP_HDR_FIELD_CONN_UNKNOWN
} HTTP_HDR_FIELD_CONN_VAL;


/*
*********************************************************************************************************
*                             HEADER FIELD TRANSFER ENCODING VALUES ENUMARATION
*********************************************************************************************************
*/

typedef enum http_hdr_field_transfer_type {
    HTTP_HDR_FIELD_TRANSFER_TYPE_NONE,
    HTTP_HDR_FIELD_TRANSFER_TYPE_CHUNCKED
} HTTP_HDR_FIELD_TRANSFER_TYPE;


/*
*********************************************************************************************************
*                                       FILE TYPES ENUMARATION
*********************************************************************************************************
*/

typedef  enum http_file_type {
    HTTP_FILE_TYPE_FS,
    HTTP_FILE_TYPE_STATIC_DATA
} HTTP_FILE_TYPE;


/*
*********************************************************************************************************
*                                       BODY TYPES ENUMARATION
*********************************************************************************************************
*/

typedef  enum http_body_type {
    HTTP_BODY_TYPE_FS,
    HTTP_BODY_TYPE_DATA,
    HTTP_BODY_TYPE_BUF
} HTTP_BODY_TYPE;


/*
*********************************************************************************************************
*                                     CGI DATA TYPES ENUMARATION
*********************************************************************************************************
*/

typedef enum  http_cgi_data_type {
    HTTP_CGI_DATA_TYPE_CTRL_VAL_QUERY,
    HTTP_CGI_DATA_TYPE_CTRL_VAL_FORM,
    HTTP_CGI_DATA_TYPE_FILE
} HTTP_CGI_DATA_TYPE;


/*
*********************************************************************************************************
*                                            CGI DATA TYPE
*********************************************************************************************************
*/

typedef  struct  http_cgi_data  HTTP_CGI_DATA;

struct  http_cgi_data {
    HTTP_CGI_DATA_TYPE   DataType;
    CPU_CHAR            *CtrlNamePtr;
    CPU_INT16U           CtrlNameLen;
    CPU_CHAR            *ValPtr;
    CPU_INT16U           ValLen;
    HTTP_CGI_DATA       *DataNextPtr;
};


/*
*********************************************************************************************************
*                                 HTTP HDR FIELD VALUE TYPE DATA TYPE
*********************************************************************************************************
*/

typedef  enum  http_hdr_val_type {
    HTTP_HDR_VAL_TYPE_NONE,
    HTTP_HDR_VAL_TYPE_STR_CONST,
    HTTP_HDR_VAL_TYPE_STR_DYN
} HTTP_HDR_VAL_TYPE;


/*
*********************************************************************************************************
*                                     HTTP HDR FIELD BLK DATA TYPE
*********************************************************************************************************
*/

typedef  struct  http_hdr_blk  HTTP_HDR_BLK;

struct  http_hdr_blk {
    HTTP_HDR_FIELD      HdrField;
    HTTP_HDR_VAL_TYPE   ValType;
    void               *ValPtr;
    CPU_INT32U          ValLen;
    HTTP_HDR_BLK       *NextPtr;
    HTTP_HDR_BLK       *PrevPtr;
};


/*
*********************************************************************************************************
*                                        DICTIONARY DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT32U  HTTP_DICTIONARY_KEY;

#define  HTTP_DICTIONARY_KEY_INVALID                       DEF_INT_32U_MAX_VAL


typedef  struct  HTTP_dictionary {
    const  HTTP_DICTIONARY_KEY   Key;
    const  CPU_CHAR             *StrPtr;
    const  CPU_INT32U            StrLen;
} HTTP_DICTIONARY;



/*
*********************************************************************************************************
*********************************************************************************************************
*                                           GLOBAL VARIABLES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             HTTP METHOD
*********************************************************************************************************
*/

#define  HTTP_STR_METHOD_GET                               "GET"
#define  HTTP_STR_METHOD_POST                              "POST"
#define  HTTP_STR_METHOD_HEAD                              "HEAD"
#define  HTTP_STR_METHOD_PUT                               "PUT"
#define  HTTP_STR_METHOD_DELETE                            "DELETE"
#define  HTTP_STR_METHOD_TRACE                             "TRACE"
#define  HTTP_STR_METHOD_CONNECT                           "CONNECT"

static  const  HTTP_DICTIONARY  HTTP_DictionaryReqMethods[] = {
    { HTTP_METHOD_GET,     HTTP_STR_METHOD_GET,     (sizeof(HTTP_STR_METHOD_GET)     - 1) },
    { HTTP_METHOD_POST,    HTTP_STR_METHOD_POST,    (sizeof(HTTP_STR_METHOD_POST)    - 1) },
    { HTTP_METHOD_HEAD,    HTTP_STR_METHOD_HEAD,    (sizeof(HTTP_STR_METHOD_HEAD)    - 1) },
    { HTTP_METHOD_PUT,     HTTP_STR_METHOD_PUT,     (sizeof(HTTP_STR_METHOD_PUT)     - 1) },
    { HTTP_METHOD_DELETE,  HTTP_STR_METHOD_DELETE,  (sizeof(HTTP_STR_METHOD_DELETE)  - 1) },
    { HTTP_METHOD_TRACE,   HTTP_STR_METHOD_TRACE,   (sizeof(HTTP_STR_METHOD_TRACE)   - 1) },
    { HTTP_METHOD_CONNECT, HTTP_STR_METHOD_CONNECT, (sizeof(HTTP_STR_METHOD_CONNECT) - 1) },
};


/*
*********************************************************************************************************
*                                            HTTP VERSION
*********************************************************************************************************
*/

#define  HTTP_STR_PROTOCOL_VER_0_9                     "HTTP/0.9"
#define  HTTP_STR_PROTOCOL_VER_1_0                     "HTTP/1.0"
#define  HTTP_STR_PROTOCOL_VER_1_1                     "HTTP/1.1"

static  const  HTTP_DICTIONARY   HTTP_DictionaryProtocolVers[] = {
    { HTTP_PROTOCOL_VER_0_9, HTTP_STR_PROTOCOL_VER_0_9, (sizeof(HTTP_STR_PROTOCOL_VER_0_9) - 1) },
    { HTTP_PROTOCOL_VER_1_0, HTTP_STR_PROTOCOL_VER_1_0, (sizeof(HTTP_STR_PROTOCOL_VER_1_0) - 1) },
    { HTTP_PROTOCOL_VER_1_1, HTTP_STR_PROTOCOL_VER_1_1, (sizeof(HTTP_STR_PROTOCOL_VER_1_1) - 1) },
};


/*
*********************************************************************************************************
*                                          HTTPS STATUS CODE
*********************************************************************************************************
*/

#define  HTTP_STR_STATUS_CODE_OK                               "200"
#define  HTTP_STR_STATUS_CODE_CREATED                          "201"
#define  HTTP_STR_STATUS_CODE_ACCEPTED                         "202"
#define  HTTP_STR_STATUS_CODE_NO_CONTENT                       "204"
#define  HTTP_STR_STATUS_CODE_RESET_CONTENT                    "205"
#define  HTTP_STR_STATUS_CODE_MOVED_PERMANENTLY                "301"
#define  HTTP_STR_STATUS_CODE_FOUND                            "302"
#define  HTTP_STR_STATUS_CODE_SEE_OTHER                        "303"
#define  HTTP_STR_STATUS_CODE_NOT_MODIFIED                     "304"
#define  HTTP_STR_STATUS_CODE_USE_PROXY                        "305"
#define  HTTP_STR_STATUS_CODE_TEMPORARY_REDIRECT               "307"
#define  HTTP_STR_STATUS_CODE_BAD_REQUEST                      "400"
#define  HTTP_STR_STATUS_CODE_UNAUTHORIZED                     "401"
#define  HTTP_STR_STATUS_CODE_FORBIDDEN                        "403"
#define  HTTP_STR_STATUS_CODE_NOT_FOUND                        "404"
#define  HTTP_STR_STATUS_CODE_METHOD_NOT_ALLOWED               "405"
#define  HTTP_STR_STATUS_CODE_NOT_ACCEPTABLE                   "406"
#define  HTTP_STR_STATUS_CODE_REQUEST_TIMEOUT                  "408"
#define  HTTP_STR_STATUS_CODE_CONFLIT                          "409"
#define  HTTP_STR_STATUS_CODE_GONE                             "410"
#define  HTTP_STR_STATUS_CODE_LENGTH_REQUIRED                  "411"
#define  HTTP_STR_STATUS_CODE_PRECONDITION_FAILED              "412"
#define  HTTP_STR_STATUS_CODE_REQUEST_ENTITY_TOO_LARGE         "413"
#define  HTTP_STR_STATUS_CODE_REQUEST_URI_TOO_LONG             "414"
#define  HTTP_STR_STATUS_CODE_UNSUPPORTED_MEDIA_TYPE           "415"
#define  HTTP_STR_STATUS_CODE_REQUESTED_RANGE_NOT_SATISFIABLE  "416"
#define  HTTP_STR_STATUS_CODE_EXPECTATION_FAILED               "417"
#define  HTTP_STR_STATUS_CODE_INTERNAL_SERVER_ERR              "500"
#define  HTTP_STR_STATUS_CODE_NOT_IMPLEMENTED                  "501"
#define  HTTP_STR_STATUS_CODE_SERVICE_UNAVAILABLE              "503"
#define  HTTP_STR_STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED       "505"

static  const  HTTP_DICTIONARY  HTTP_DictionaryStatusCodes[] = {
    { HTTP_STATUS_OK,                               HTTP_STR_STATUS_CODE_OK,                               (sizeof(HTTP_STR_STATUS_CODE_OK)                              - 1) },
    { HTTP_STATUS_CREATED,                          HTTP_STR_STATUS_CODE_CREATED,                          (sizeof(HTTP_STR_STATUS_CODE_CREATED)                         - 1) },
    { HTTP_STATUS_ACCEPTED,                         HTTP_STR_STATUS_CODE_ACCEPTED,                         (sizeof(HTTP_STR_STATUS_CODE_ACCEPTED)                        - 1) },
    { HTTP_STATUS_NO_CONTENT,                       HTTP_STR_STATUS_CODE_NO_CONTENT,                       (sizeof(HTTP_STR_STATUS_CODE_NO_CONTENT)                      - 1) },
    { HTTP_STATUS_RESET_CONTENT,                    HTTP_STR_STATUS_CODE_RESET_CONTENT,                    (sizeof(HTTP_STR_STATUS_CODE_RESET_CONTENT)                   - 1) },
    { HTTP_STATUS_MOVED_PERMANENTLY,                HTTP_STR_STATUS_CODE_MOVED_PERMANENTLY,                (sizeof(HTTP_STR_STATUS_CODE_MOVED_PERMANENTLY)               - 1) },
    { HTTP_STATUS_FOUND,                            HTTP_STR_STATUS_CODE_FOUND,                            (sizeof(HTTP_STR_STATUS_CODE_FOUND)                           - 1) },
    { HTTP_STATUS_SEE_OTHER,                        HTTP_STR_STATUS_CODE_SEE_OTHER,                        (sizeof(HTTP_STR_STATUS_CODE_SEE_OTHER)                       - 1) },
    { HTTP_STATUS_NOT_MODIFIED,                     HTTP_STR_STATUS_CODE_NOT_MODIFIED,                     (sizeof(HTTP_STR_STATUS_CODE_NOT_MODIFIED)                    - 1) },
    { HTTP_STATUS_USE_PROXY,                        HTTP_STR_STATUS_CODE_USE_PROXY,                        (sizeof(HTTP_STR_STATUS_CODE_USE_PROXY)                       - 1) },
    { HTTP_STATUS_TEMPORARY_REDIRECT,               HTTP_STR_STATUS_CODE_TEMPORARY_REDIRECT,               (sizeof(HTTP_STR_STATUS_CODE_TEMPORARY_REDIRECT)              - 1) },
    { HTTP_STATUS_BAD_REQUEST,                      HTTP_STR_STATUS_CODE_BAD_REQUEST,                      (sizeof(HTTP_STR_STATUS_CODE_BAD_REQUEST)                     - 1) },
    { HTTP_STATUS_UNAUTHORIZED,                     HTTP_STR_STATUS_CODE_UNAUTHORIZED,                     (sizeof(HTTP_STR_STATUS_CODE_UNAUTHORIZED)                    - 1) },
    { HTTP_STATUS_FORBIDDEN,                        HTTP_STR_STATUS_CODE_FORBIDDEN,                        (sizeof(HTTP_STR_STATUS_CODE_FORBIDDEN)                       - 1) },
    { HTTP_STATUS_NOT_FOUND,                        HTTP_STR_STATUS_CODE_NOT_FOUND,                        (sizeof(HTTP_STR_STATUS_CODE_NOT_FOUND)                       - 1) },
    { HTTP_STATUS_METHOD_NOT_ALLOWED,               HTTP_STR_STATUS_CODE_METHOD_NOT_ALLOWED,               (sizeof(HTTP_STR_STATUS_CODE_METHOD_NOT_ALLOWED)              - 1) },
    { HTTP_STATUS_NOT_ACCEPTABLE,                   HTTP_STR_STATUS_CODE_NOT_ACCEPTABLE,                   (sizeof(HTTP_STR_STATUS_CODE_NOT_ACCEPTABLE)                  - 1) },
    { HTTP_STATUS_REQUEST_TIMEOUT,                  HTTP_STR_STATUS_CODE_REQUEST_TIMEOUT,                  (sizeof(HTTP_STR_STATUS_CODE_REQUEST_TIMEOUT)                 - 1) },
    { HTTP_STATUS_CONFLICT,                         HTTP_STR_STATUS_CODE_CONFLIT,                          (sizeof(HTTP_STR_STATUS_CODE_CONFLIT)                         - 1) },
    { HTTP_STATUS_GONE,                             HTTP_STR_STATUS_CODE_GONE,                             (sizeof(HTTP_STR_STATUS_CODE_GONE)                            - 1) },
    { HTTP_STATUS_LENGTH_REQUIRED,                  HTTP_STR_STATUS_CODE_LENGTH_REQUIRED,                  (sizeof(HTTP_STR_STATUS_CODE_LENGTH_REQUIRED)                 - 1) },
    { HTTP_STATUS_PRECONDITION_FAILED,              HTTP_STR_STATUS_CODE_PRECONDITION_FAILED,              (sizeof(HTTP_STR_STATUS_CODE_PRECONDITION_FAILED)             - 1) },
    { HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE,         HTTP_STR_STATUS_CODE_REQUEST_ENTITY_TOO_LARGE,         (sizeof(HTTP_STR_STATUS_CODE_REQUEST_ENTITY_TOO_LARGE)        - 1) },
    { HTTP_STATUS_REQUEST_URI_TOO_LONG,             HTTP_STR_STATUS_CODE_REQUEST_URI_TOO_LONG,             (sizeof(HTTP_STR_STATUS_CODE_REQUEST_URI_TOO_LONG)            - 1) },
    { HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE,           HTTP_STR_STATUS_CODE_UNSUPPORTED_MEDIA_TYPE,           (sizeof(HTTP_STR_STATUS_CODE_UNSUPPORTED_MEDIA_TYPE)          - 1) },
    { HTTP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE,  HTTP_STR_STATUS_CODE_REQUESTED_RANGE_NOT_SATISFIABLE,  (sizeof(HTTP_STR_STATUS_CODE_REQUESTED_RANGE_NOT_SATISFIABLE) - 1) },
    { HTTP_STATUS_EXPECTATION_FAILED,               HTTP_STR_STATUS_CODE_EXPECTATION_FAILED,               (sizeof(HTTP_STR_STATUS_CODE_EXPECTATION_FAILED)              - 1) },
    { HTTP_STATUS_INTERNAL_SERVER_ERR,              HTTP_STR_STATUS_CODE_INTERNAL_SERVER_ERR,              (sizeof(HTTP_STR_STATUS_CODE_INTERNAL_SERVER_ERR)             - 1) },
    { HTTP_STATUS_NOT_IMPLEMENTED,                  HTTP_STR_STATUS_CODE_NOT_IMPLEMENTED,                  (sizeof(HTTP_STR_STATUS_CODE_NOT_IMPLEMENTED)                 - 1) },
    { HTTP_STATUS_SERVICE_UNAVAILABLE,              HTTP_STR_STATUS_CODE_SERVICE_UNAVAILABLE,              (sizeof(HTTP_STR_STATUS_CODE_SERVICE_UNAVAILABLE)             - 1) },
    { HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED,       HTTP_STR_STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED,       (sizeof(HTTP_STR_STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED)      - 1) },
};

#define  HTTP_STR_REASON_PHRASE_LEN_MAX                          40

#define  HTTP_STR_REASON_PHRASE_OK                               "OK"
#define  HTTP_STR_REASON_PHRASE_CREATED                          "Created"
#define  HTTP_STR_REASON_PHRASE_ACCEPTED                         "Accepted"
#define  HTTP_STR_REASON_PHRASE_NO_CONTENT                       "No Content"
#define  HTTP_STR_REASON_PHRASE_RESET_CONTENT                    "Reset Content"
#define  HTTP_STR_REASON_PHRASE_MOVED_PERMANENTLY                "Moved Permanently"
#define  HTTP_STR_REASON_PHRASE_FOUND                            "Found"
#define  HTTP_STR_REASON_PHRASE_SEE_OTHER                        "See Other"
#define  HTTP_STR_REASON_PHRASE_NOT_MODIFIED                     "Not Modified"
#define  HTTP_STR_REASON_PHRASE_USE_PROXY                        "Use Proxy"
#define  HTTP_STR_REASON_PHRASE_TEMPORARY_REDIRECT               "Temporary Redirect"
#define  HTTP_STR_REASON_PHRASE_BAD_REQUEST                      "Bad Request"
#define  HTTP_STR_REASON_PHRASE_UNAUTHORIZED                     "Unauthorized"
#define  HTTP_STR_REASON_PHRASE_FORBIDDEN                        "Forbidden"
#define  HTTP_STR_REASON_PHRASE_NOT_FOUND                        "Not Found"
#define  HTTP_STR_REASON_PHRASE_METHOD_NOT_ALLOWED               "Method Not Allowed"
#define  HTTP_STR_REASON_PHRASE_NOT_ACCEPTABLE                   "Not Acceptable"
#define  HTTP_STR_REASON_PHRASE_REQUEST_TIMEOUT                  "Request Timeout"
#define  HTTP_STR_REASON_PHRASE_CONFLICT                         "Conflict"
#define  HTTP_STR_REASON_PHRASE_GONE                             "Gone"
#define  HTTP_STR_REASON_PHRASE_LENGTH_REQUIRED                  "Length Required"
#define  HTTP_STR_REASON_PHRASE_PRECONDITION_FAILED              "Precondition Failed"
#define  HTTP_STR_REASON_PHRASE_REQUEST_ENTITY_TOO_LARGE         "Request Entity Too Large"
#define  HTTP_STR_REASON_PHRASE_REQUEST_URI_TOO_LONG             "Request URI Too Long"
#define  HTTP_STR_REASON_PHRASE_UNSUPPORTED_MEDIA_TYPE           "Unsupported Media Type"
#define  HTTP_STR_REASON_PHRASE_REQUESTED_RANGE_NOT_SATISFIABLE  "Requested Range Not Satisfiable"
#define  HTTP_STR_REASON_PHRASE_EXPECTATION_FAILED               "Expectation Failed"
#define  HTTP_STR_REASON_PHRASE_INTERNAL_SERVER_ERR              "Internal Server Error"
#define  HTTP_STR_REASON_PHRASE_NOT_IMPLEMENTED                  "Not Implemented"
#define  HTTP_STR_REASON_PHRASE_BAD_GATEWAY                      "Bad Gateway"
#define  HTTP_STR_REASON_PHRASE_SERVICE_UNAVAILABLE              "Service Unavailable"
#define  HTTP_STR_REASON_PHRASE_HTTP_VERSION_NOT_SUPPORTED       "HTTP Version Not Supported"

static  const  HTTP_DICTIONARY  HTTP_DictionaryReasonPhrases[] = {
    { HTTP_STATUS_OK,                               HTTP_STR_REASON_PHRASE_OK,                               (sizeof(HTTP_STR_REASON_PHRASE_OK)                              - 1) },
    { HTTP_STATUS_CREATED,                          HTTP_STR_REASON_PHRASE_CREATED,                          (sizeof(HTTP_STR_REASON_PHRASE_CREATED)                         - 1) },
    { HTTP_STATUS_ACCEPTED,                         HTTP_STR_REASON_PHRASE_ACCEPTED,                         (sizeof(HTTP_STR_REASON_PHRASE_ACCEPTED)                        - 1) },
    { HTTP_STATUS_NO_CONTENT,                       HTTP_STR_REASON_PHRASE_NO_CONTENT,                       (sizeof(HTTP_STR_REASON_PHRASE_NO_CONTENT)                      - 1) },
    { HTTP_STATUS_RESET_CONTENT,                    HTTP_STR_REASON_PHRASE_RESET_CONTENT,                    (sizeof(HTTP_STR_REASON_PHRASE_RESET_CONTENT)                   - 1) },
    { HTTP_STATUS_MOVED_PERMANENTLY,                HTTP_STR_REASON_PHRASE_MOVED_PERMANENTLY,                (sizeof(HTTP_STR_REASON_PHRASE_MOVED_PERMANENTLY)               - 1) },
    { HTTP_STATUS_FOUND,                            HTTP_STR_REASON_PHRASE_FOUND,                            (sizeof(HTTP_STR_REASON_PHRASE_FOUND)                           - 1) },
    { HTTP_STATUS_SEE_OTHER,                        HTTP_STR_REASON_PHRASE_SEE_OTHER,                        (sizeof(HTTP_STR_REASON_PHRASE_SEE_OTHER)                       - 1) },
    { HTTP_STATUS_NOT_MODIFIED,                     HTTP_STR_REASON_PHRASE_NOT_MODIFIED,                     (sizeof(HTTP_STR_REASON_PHRASE_NOT_MODIFIED)                    - 1) },
    { HTTP_STATUS_USE_PROXY,                        HTTP_STR_REASON_PHRASE_USE_PROXY,                        (sizeof(HTTP_STR_REASON_PHRASE_USE_PROXY)                       - 1) },
    { HTTP_STATUS_TEMPORARY_REDIRECT,               HTTP_STR_REASON_PHRASE_TEMPORARY_REDIRECT,               (sizeof(HTTP_STR_REASON_PHRASE_TEMPORARY_REDIRECT)              - 1) },
    { HTTP_STATUS_BAD_REQUEST,                      HTTP_STR_REASON_PHRASE_BAD_REQUEST,                      (sizeof(HTTP_STR_REASON_PHRASE_BAD_REQUEST)                     - 1) },
    { HTTP_STATUS_UNAUTHORIZED,                     HTTP_STR_REASON_PHRASE_UNAUTHORIZED,                     (sizeof(HTTP_STR_REASON_PHRASE_UNAUTHORIZED)                    - 1) },
    { HTTP_STATUS_FORBIDDEN,                        HTTP_STR_REASON_PHRASE_FORBIDDEN,                        (sizeof(HTTP_STR_REASON_PHRASE_FORBIDDEN)                       - 1) },
    { HTTP_STATUS_NOT_FOUND,                        HTTP_STR_REASON_PHRASE_NOT_FOUND,                        (sizeof(HTTP_STR_REASON_PHRASE_NOT_FOUND)                       - 1) },
    { HTTP_STATUS_METHOD_NOT_ALLOWED,               HTTP_STR_REASON_PHRASE_METHOD_NOT_ALLOWED,               (sizeof(HTTP_STR_REASON_PHRASE_METHOD_NOT_ALLOWED)              - 1) },
    { HTTP_STATUS_NOT_ACCEPTABLE,                   HTTP_STR_REASON_PHRASE_NOT_ACCEPTABLE,                   (sizeof(HTTP_STR_REASON_PHRASE_NOT_ACCEPTABLE)                  - 1) },
    { HTTP_STATUS_REQUEST_TIMEOUT,                  HTTP_STR_REASON_PHRASE_REQUEST_TIMEOUT,                  (sizeof(HTTP_STR_REASON_PHRASE_REQUEST_TIMEOUT)                 - 1) },
    { HTTP_STATUS_CONFLICT,                         HTTP_STR_REASON_PHRASE_CONFLICT,                         (sizeof(HTTP_STR_REASON_PHRASE_CONFLICT)                        - 1) },
    { HTTP_STATUS_GONE,                             HTTP_STR_REASON_PHRASE_GONE,                             (sizeof(HTTP_STR_REASON_PHRASE_GONE)                            - 1) },
    { HTTP_STATUS_LENGTH_REQUIRED,                  HTTP_STR_REASON_PHRASE_LENGTH_REQUIRED,                  (sizeof(HTTP_STR_REASON_PHRASE_LENGTH_REQUIRED)                 - 1) },
    { HTTP_STATUS_PRECONDITION_FAILED,              HTTP_STR_REASON_PHRASE_PRECONDITION_FAILED,              (sizeof(HTTP_STR_REASON_PHRASE_PRECONDITION_FAILED)             - 1) },
    { HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE,         HTTP_STR_REASON_PHRASE_REQUEST_ENTITY_TOO_LARGE,         (sizeof(HTTP_STR_REASON_PHRASE_REQUEST_ENTITY_TOO_LARGE)        - 1) },
    { HTTP_STATUS_REQUEST_URI_TOO_LONG,             HTTP_STR_REASON_PHRASE_REQUEST_URI_TOO_LONG,             (sizeof(HTTP_STR_REASON_PHRASE_REQUEST_URI_TOO_LONG)            - 1) },
    { HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE,           HTTP_STR_REASON_PHRASE_UNSUPPORTED_MEDIA_TYPE,           (sizeof(HTTP_STR_REASON_PHRASE_UNSUPPORTED_MEDIA_TYPE)          - 1) },
    { HTTP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE,  HTTP_STR_REASON_PHRASE_REQUESTED_RANGE_NOT_SATISFIABLE,  (sizeof(HTTP_STR_REASON_PHRASE_REQUESTED_RANGE_NOT_SATISFIABLE) - 1) },
    { HTTP_STATUS_EXPECTATION_FAILED,               HTTP_STR_REASON_PHRASE_EXPECTATION_FAILED,               (sizeof(HTTP_STR_REASON_PHRASE_EXPECTATION_FAILED)              - 1) },
    { HTTP_STATUS_INTERNAL_SERVER_ERR,              HTTP_STR_REASON_PHRASE_INTERNAL_SERVER_ERR,              (sizeof(HTTP_STR_REASON_PHRASE_INTERNAL_SERVER_ERR)             - 1) },
    { HTTP_STATUS_NOT_IMPLEMENTED,                  HTTP_STR_REASON_PHRASE_NOT_IMPLEMENTED,                  (sizeof(HTTP_STR_REASON_PHRASE_NOT_IMPLEMENTED)                 - 1) },
    { HTTP_STATUS_SERVICE_UNAVAILABLE,              HTTP_STR_REASON_PHRASE_SERVICE_UNAVAILABLE,              (sizeof(HTTP_STR_REASON_PHRASE_SERVICE_UNAVAILABLE)             - 1) },
    { HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED,       HTTP_STR_REASON_PHRASE_HTTP_VERSION_NOT_SUPPORTED,       (sizeof(HTTP_STR_REASON_PHRASE_HTTP_VERSION_NOT_SUPPORTED)      - 1) },
};


/*
*********************************************************************************************************
*                                          HTTP CONTENT TYPE
*********************************************************************************************************
*/

#define  HTTP_STR_FILE_EXT_HTM                             "htm"
#define  HTTP_STR_FILE_EXT_HTML                            "html"
#define  HTTP_STR_FILE_EXT_GIF                             "gif"
#define  HTTP_STR_FILE_EXT_JPEG                            "jpeg"
#define  HTTP_STR_FILE_EXT_JPG                             "jpg"
#define  HTTP_STR_FILE_EXT_PNG                             "png"
#define  HTTP_STR_FILE_EXT_JS                              "js"
#define  HTTP_STR_FILE_EXT_TXT                             "txt"
#define  HTTP_STR_FILE_EXT_CSS                             "css"
#define  HTTP_STR_FILE_EXT_PDF                             "pdf"
#define  HTTP_STR_FILE_EXT_ZIP                             "zip"
#define  HTTP_STR_FILE_EXT_ASTERISK                        "*"
#define  HTTP_STR_FILE_EXT_CLASS                           "class"

static  const  HTTP_DICTIONARY  HTTP_DictionaryFileExts[] = {
    { HTTP_CONTENT_TYPE_HTML,         HTTP_STR_FILE_EXT_HTM,      (sizeof(HTTP_STR_FILE_EXT_HTM)      - 1) },
    { HTTP_CONTENT_TYPE_HTML,         HTTP_STR_FILE_EXT_HTML,     (sizeof(HTTP_STR_FILE_EXT_HTML)     - 1) },
    { HTTP_CONTENT_TYPE_GIF,          HTTP_STR_FILE_EXT_GIF,      (sizeof(HTTP_STR_FILE_EXT_GIF)      - 1) },
    { HTTP_CONTENT_TYPE_JPEG,         HTTP_STR_FILE_EXT_JPEG,     (sizeof(HTTP_STR_FILE_EXT_JPEG)     - 1) },
    { HTTP_CONTENT_TYPE_JPEG,         HTTP_STR_FILE_EXT_JPG,      (sizeof(HTTP_STR_FILE_EXT_JPG)      - 1) },
    { HTTP_CONTENT_TYPE_PNG,          HTTP_STR_FILE_EXT_PNG,      (sizeof(HTTP_STR_FILE_EXT_PNG)      - 1) },
    { HTTP_CONTENT_TYPE_JS,           HTTP_STR_FILE_EXT_JS,       (sizeof(HTTP_STR_FILE_EXT_JS)       - 1) },
    { HTTP_CONTENT_TYPE_PLAIN,        HTTP_STR_FILE_EXT_TXT,      (sizeof(HTTP_STR_FILE_EXT_TXT)      - 1) },
    { HTTP_CONTENT_TYPE_CSS,          HTTP_STR_FILE_EXT_CSS,      (sizeof(HTTP_STR_FILE_EXT_CSS)      - 1) },
    { HTTP_CONTENT_TYPE_PDF,          HTTP_STR_FILE_EXT_PDF,      (sizeof(HTTP_STR_FILE_EXT_PDF)      - 1) },
    { HTTP_CONTENT_TYPE_ZIP,          HTTP_STR_FILE_EXT_ZIP,      (sizeof(HTTP_STR_FILE_EXT_ZIP)      - 1) },
    { HTTP_CONTENT_TYPE_OCTET_STREAM, HTTP_STR_FILE_EXT_ASTERISK, (sizeof(HTTP_STR_FILE_EXT_ASTERISK) - 1) },
    { HTTP_CONTENT_TYPE_OCTET_STREAM, HTTP_STR_FILE_EXT_CLASS,    (sizeof(HTTP_STR_FILE_EXT_CLASS)    - 1) },
};


#define  HTTP_STR_CONTENT_TYPE_HTML                        "text/html"
#define  HTTP_STR_CONTENT_TYPE_GIF                         "image/gif"
#define  HTTP_STR_CONTENT_TYPE_JPEG                        "image/jpeg"
#define  HTTP_STR_CONTENT_TYPE_PNG                         "image/png"
#define  HTTP_STR_CONTENT_TYPE_JS                          "text/javascript"
#define  HTTP_STR_CONTENT_TYPE_PLAIN                       "text/plain"
#define  HTTP_STR_CONTENT_TYPE_CSS                         "text/css"
#define  HTTP_STR_CONTENT_TYPE_OCTET_STREAM                "application/octet-stream"
#define  HTTP_STR_CONTENT_TYPE_PDF                         "application/pdf"
#define  HTTP_STR_CONTENT_TYPE_ZIP                         "application/zip"
#define  HTTP_STR_CONTENT_TYPE_JSON                        "application/json"
#define  HTTP_STR_CONTENT_TYPE_APP_FORM                    "application/x-www-form-urlencoded"
#define  HTTP_STR_CONTENT_TYPE_MULTIPART_FORM              "multipart/form-data"

static  const  HTTP_DICTIONARY  HTTP_DictionaryContentTypes[] = {
    { HTTP_CONTENT_TYPE_HTML,            HTTP_STR_CONTENT_TYPE_HTML,            (sizeof(HTTP_STR_CONTENT_TYPE_HTML)           - 1) },
    { HTTP_CONTENT_TYPE_GIF,             HTTP_STR_CONTENT_TYPE_GIF,             (sizeof(HTTP_STR_CONTENT_TYPE_GIF)            - 1) },
    { HTTP_CONTENT_TYPE_JPEG,            HTTP_STR_CONTENT_TYPE_JPEG,            (sizeof(HTTP_STR_CONTENT_TYPE_JPEG)           - 1) },
    { HTTP_CONTENT_TYPE_PNG,             HTTP_STR_CONTENT_TYPE_PNG,             (sizeof(HTTP_STR_CONTENT_TYPE_PNG)            - 1) },
    { HTTP_CONTENT_TYPE_JS,              HTTP_STR_CONTENT_TYPE_JS,              (sizeof(HTTP_STR_CONTENT_TYPE_JS)             - 1) },
    { HTTP_CONTENT_TYPE_PLAIN,           HTTP_STR_CONTENT_TYPE_PLAIN,           (sizeof(HTTP_STR_CONTENT_TYPE_PLAIN)          - 1) },
    { HTTP_CONTENT_TYPE_CSS,             HTTP_STR_CONTENT_TYPE_CSS,             (sizeof(HTTP_STR_CONTENT_TYPE_CSS)            - 1) },
    { HTTP_CONTENT_TYPE_OCTET_STREAM,    HTTP_STR_CONTENT_TYPE_OCTET_STREAM,    (sizeof(HTTP_STR_CONTENT_TYPE_OCTET_STREAM)   - 1) },
    { HTTP_CONTENT_TYPE_PDF,             HTTP_STR_CONTENT_TYPE_PDF,             (sizeof(HTTP_STR_CONTENT_TYPE_PDF)            - 1) },
    { HTTP_CONTENT_TYPE_ZIP,             HTTP_STR_CONTENT_TYPE_ZIP,             (sizeof(HTTP_STR_CONTENT_TYPE_ZIP)            - 1) },
    { HTTP_CONTENT_TYPE_JSON,            HTTP_STR_CONTENT_TYPE_JSON,            (sizeof(HTTP_STR_CONTENT_TYPE_JSON)           - 1) },
    { HTTP_CONTENT_TYPE_APP_FORM,        HTTP_STR_CONTENT_TYPE_APP_FORM,        (sizeof(HTTP_STR_CONTENT_TYPE_APP_FORM)       - 1) },
    { HTTP_CONTENT_TYPE_MULTIPART_FORM,  HTTP_STR_CONTENT_TYPE_MULTIPART_FORM,  (sizeof(HTTP_STR_CONTENT_TYPE_MULTIPART_FORM) - 1) },
};


/*
*********************************************************************************************************
*                                          MULTIPART BOUNDARY
*********************************************************************************************************
*/

#define  HTTP_STR_MULTIPART_BOUNDARY                    "boundary"
#define  HTTP_STR_MULTIPART_BOUNDARY_LEN                (sizeof(HTTP_STR_MULTIPART_BOUNDARY) - 1)


/*
*********************************************************************************************************
*                                          HTTP HEADER FIELD
*********************************************************************************************************
*/

#define  HTTP_STR_HDR_FIELD_CONN                           "Connection"
#define  HTTP_STR_HDR_FIELD_HOST                           "Host"
#define  HTTP_STR_HDR_FIELD_LOCATION                       "Location"
#define  HTTP_STR_HDR_FIELD_CONTENT_TYPE                   "Content-Type"
#define  HTTP_STR_HDR_FIELD_CONTENT_LEN                    "Content-Length"
#define  HTTP_STR_HDR_FILED_CONTENT_DISPOSITION            "Content-Disposition"
#define  HTTP_STR_HDR_FIELD_TRANSFER_ENCODING              "Transfer-Encoding"
#define  HTTP_STR_HDR_FIELD_ACCEPT                         "Accept"
#define  HTTP_STR_HDR_FIELD_ACCEPT_CHARSET                 "Accept-Charset"
#define  HTTP_STR_HDR_FIELD_ACCEPT_ENCODING                "Accept-Encoding"
#define  HTTP_STR_HDR_FIELD_ACCEPT_LANGUAGE                "Accept-Language"
#define  HTTP_STR_HDR_FIELD_ACCEPT_RANGES                  "Accept-Ranges"
#define  HTTP_STR_HDR_FIELD_AGE                            "Age"
#define  HTTP_STR_HDR_FIELD_ALLOW                          "Allow"
#define  HTTP_STR_HDR_FIELD_AUTHORIZATION                  "Authorization"
#define  HTTP_STR_HDR_FIELD_CONTENT_ENCODING               "Content-Encoding"
#define  HTTP_STR_HDR_FIELD_CONTENT_LANGUAGE               "Content-Language"
#define  HTTP_STR_HDR_FIELD_CONTENT_LOCATION               "Content-Location"
#define  HTTP_STR_HDR_FIELD_CONTENT_MD5                    "Content-MD5"
#define  HTTP_STR_HDR_FIELD_CONTENT_RANGE                  "Content-Range"
#define  HTTP_STR_HDR_FIELD_COOKIE                         "Cookie"
#define  HTTP_STR_HDR_FIELD_COOKIE2                        "Cookie2"
#define  HTTP_STR_HDR_FIELD_DATE                           "Date"
#define  HTTP_STR_HDR_FIELD_ETAG                           "ETag"
#define  HTTP_STR_HDR_FIELD_EXPECT                         "Expect"
#define  HTTP_STR_HDR_FIELD_EXPIRES                        "Expires"
#define  HTTP_STR_HDR_FIELD_FROM                           "From"
#define  HTTP_STR_HDR_FIELD_IF_MODIFIED_SINCE              "If-Modified-Since"
#define  HTTP_STR_HDR_FIELD_IF_MATCH                       "If-Match"
#define  HTTP_STR_HDR_FIELD_IF_NONE_MATCH                  "If-None-Match"
#define  HTTP_STR_HDR_FIELD_IF_RANGE                       "If-Range"
#define  HTTP_STR_HDR_FIELD_IF_UNMODIFIED_SINCE            "If-Unmodified-Since"
#define  HTTP_STR_HDR_FIELD_LAST_MODIFIED                  "Last-Modified"
#define  HTTP_STR_HDR_FIELD_RANGE                          "Range"
#define  HTTP_STR_HDR_FIELD_REFERER                        "Referer"
#define  HTTP_STR_HDR_FIELD_RETRY_AFTER                    "Retry-After"
#define  HTTP_STR_HDR_FIELD_SERVER                         "Server"
#define  HTTP_STR_HDR_FIELD_SET_COOKIE                     "Set-Cookie"
#define  HTTP_STR_HDR_FIELD_SET_COOKIE2                    "Set-Cookie2"
#define  HTTP_STR_HDR_FIELD_TE                             "TE"
#define  HTTP_STR_HDR_FIELD_TRAILER                        "Trailer"
#define  HTTP_STR_HDR_FIELD_UPGRATE                        "Upgrade"
#define  HTTP_STR_HDR_FIELD_USER_AGENT                     "User-Agent"
#define  HTTP_STR_HDR_FIELD_VARY                           "Vary"
#define  HTTP_STR_HDR_FIELD_VIA                            "Via"
#define  HTTP_STR_HDR_FIELD_WARNING                        "Warning"
#define  HTTP_STR_HDR_FIELD_WWW_AUTHENTICATE               "WWW-Authenticate"


                                                                /* Len of Hdr Field string names in Request messages     */
#define  HTTP_STR_HDR_FIELD_CONN_LEN                       (sizeof(HTTP_STR_HDR_FIELD_CONN)                - 1)
#define  HTTP_STR_HDR_FIELD_HOST_LEN                       (sizeof(HTTP_STR_HDR_FIELD_HOST)                - 1)
#define  HTTP_STR_HDR_FIELD_LOCATION_LEN                   (sizeof(HTTP_STR_HDR_FIELD_LOCATION)            - 1)
#define  HTTP_STR_HDR_FIELD_CONTENT_TYPE_LEN               (sizeof(HTTP_STR_HDR_FIELD_CONTENT_TYPE)        - 1)
#define  HTTP_STR_HDR_FIELD_CONTENT_LEN_LEN                (sizeof(HTTP_STR_HDR_FIELD_CONTENT_LEN)         - 1)
#define  HTTP_STR_HDR_FILED_CONTENT_DISPOSITION_LEN        (sizeof(HTTP_STR_HDR_FILED_CONTENT_DISPOSITION) - 1)
#define  HTTP_STR_HDR_FIELD_TRANSFER_ENCODING_LEN          (sizeof(HTTP_STR_HDR_FIELD_TRANSFER_ENCODING)   - 1)
#define  HTTP_STR_HDR_FIELD_ACCEPT_LEN                     (sizeof(HTTP_STR_HDR_FIELD_ACCEPT)              - 1)
#define  HTTP_STR_HDR_FIELD_ACCEPT_CHARSET_LEN             (sizeof(HTTP_STR_HDR_FIELD_ACCEPT_CHARSET)      - 1)
#define  HTTP_STR_HDR_FIELD_ACCEPT_ENCODING_LEN            (sizeof(HTTP_STR_HDR_FIELD_ACCEPT_ENCODING)     - 1)
#define  HTTP_STR_HDR_FIELD_ACCEPT_LANGUAGE_LEN            (sizeof(HTTP_STR_HDR_FIELD_ACCEPT_LANGUAGE)     - 1)
#define  HTTP_STR_HDR_FIELD_AUTHORIZATION_LEN              (sizeof(HTTP_STR_HDR_FIELD_AUTHORIZATION)       - 1)
#define  HTTP_STR_HDR_FIELD_CLIENT_IP_LEN                  (sizeof(HTTP_STR_HDR_FIELD_CLIENT_IP)           - 1)
#define  HTTP_STR_HDR_FIELD_COOKIE_LEN                     (sizeof(HTTP_STR_HDR_FIELD_COOKIE)              - 1)
#define  HTTP_STR_HDR_FIELD_COOKIE2_LEN                    (sizeof(HTTP_STR_HDR_FIELD_COOKIE2)             - 1)
#define  HTTP_STR_HDR_FIELD_DATE_LEN                       (sizeof(HTTP_STR_HDR_FIELD_DATE)                - 1)
#define  HTTP_STR_HDR_FIELD_EXPECT_LEN                     (sizeof(HTTP_STR_HDR_FIELD_EXPECT)              - 1)
#define  HTTP_STR_HDR_FIELD_FROM_LEN                       (sizeof(HTTP_STR_HDR_FIELD_FROM)                - 1)
#define  HTTP_STR_HDR_FIELD_IF_MODIFIED_SINCE_LEN          (sizeof(HTTP_STR_HDR_FIELD_IF_MODIFIED_SINCE)   - 1)
#define  HTTP_STR_HDR_FIELD_IF_MATCH_LEN                   (sizeof(HTTP_STR_HDR_FIELD_IF_MATCH)            - 1)
#define  HTTP_STR_HDR_FIELD_IF_NONE_MATCH_LEN              (sizeof(HTTP_STR_HDR_FIELD_IF_NONE_MATCH)       - 1)
#define  HTTP_STR_HDR_FIELD_IF_RANGE_LEN                   (sizeof(HTTP_STR_HDR_FIELD_IF_RANGE)            - 1)
#define  HTTP_STR_HDR_FIELD_IF_UNMODIFIED_SINCE_LEN        (sizeof(HTTP_STR_HDR_FIELD_IF_UNMODIFIED_SINCE) - 1)
#define  HTTP_STR_HDR_FIELD_RANGE_LEN                      (sizeof(HTTP_STR_HDR_FIELD_RANGE)               - 1)
#define  HTTP_STR_HDR_FIELD_REFERER_LEN                    (sizeof(HTTP_STR_HDR_FIELD_REFERER)             - 1)
#define  HTTP_STR_HDR_FIELD_TE_LEN                         (sizeof(HTTP_STR_HDR_FIELD_TE)                  - 1)
#define  HTTP_STR_HDR_FIELD_UPGRATE_LEN                    (sizeof(HTTP_STR_HDR_FIELD_UPGRATE)             - 1)
#define  HTTP_STR_HDR_FIELD_USER_AGENT_LEN                 (sizeof(HTTP_STR_HDR_FIELD_USER_AGENT)          - 1)
#define  HTTP_STR_HDR_FIELD_VIA_LEN                        (sizeof(HTTP_STR_HDR_FIELD_VIA)                 - 1)

static  const  HTTP_DICTIONARY  HTTP_DictionaryHdrFields[] = {
    { HTTP_HDR_FIELD_CONTENT_TYPE,         HTTP_STR_HDR_FIELD_CONTENT_TYPE,         (sizeof(HTTP_STR_HDR_FIELD_CONTENT_TYPE)        - 1) },
    { HTTP_HDR_FIELD_CONTENT_LEN,          HTTP_STR_HDR_FIELD_CONTENT_LEN,          (sizeof(HTTP_STR_HDR_FIELD_CONTENT_LEN)         - 1) },
    { HTTP_HDR_FILED_CONTENT_DISPOSITION,  HTTP_STR_HDR_FILED_CONTENT_DISPOSITION,  (sizeof(HTTP_STR_HDR_FILED_CONTENT_DISPOSITION) - 1) },
    { HTTP_HDR_FIELD_HOST,                 HTTP_STR_HDR_FIELD_HOST,                 (sizeof(HTTP_STR_HDR_FIELD_HOST)                - 1) },
    { HTTP_HDR_FIELD_LOCATION,             HTTP_STR_HDR_FIELD_LOCATION,             (sizeof(HTTP_STR_HDR_FIELD_LOCATION)            - 1) },
    { HTTP_HDR_FIELD_CONN,                 HTTP_STR_HDR_FIELD_CONN,                 (sizeof(HTTP_STR_HDR_FIELD_CONN)                - 1) },
    { HTTP_HDR_FIELD_TRANSFER_ENCODING,    HTTP_STR_HDR_FIELD_TRANSFER_ENCODING,    (sizeof(HTTP_STR_HDR_FIELD_TRANSFER_ENCODING)   - 1) },
    { HTTP_HDR_FIELD_ACCEPT,               HTTP_STR_HDR_FIELD_ACCEPT,               (sizeof(HTTP_STR_HDR_FIELD_ACCEPT)              - 1) },
    { HTTP_HDR_FIELD_ACCEPT_CHARSET,       HTTP_STR_HDR_FIELD_ACCEPT_CHARSET,       (sizeof(HTTP_STR_HDR_FIELD_ACCEPT_CHARSET)      - 1) },
    { HTTP_HDR_FIELD_ACCEPT_ENCODING,      HTTP_STR_HDR_FIELD_ACCEPT_ENCODING,      (sizeof(HTTP_STR_HDR_FIELD_ACCEPT_ENCODING)     - 1) },
    { HTTP_HDR_FIELD_ACCEPT_LANGUAGE,      HTTP_STR_HDR_FIELD_ACCEPT_LANGUAGE,      (sizeof(HTTP_STR_HDR_FIELD_ACCEPT_LANGUAGE)     - 1) },
    { HTTP_HDR_FIELD_ACCEPT_RANGES,        HTTP_STR_HDR_FIELD_ACCEPT_RANGES,        (sizeof(HTTP_STR_HDR_FIELD_ACCEPT_RANGES)       - 1) },
    { HTTP_HDR_FIELD_AGE,                  HTTP_STR_HDR_FIELD_AGE,                  (sizeof(HTTP_STR_HDR_FIELD_AGE)                 - 1) },
    { HTTP_HDR_FIELD_ALLOW,                HTTP_STR_HDR_FIELD_ALLOW,                (sizeof(HTTP_STR_HDR_FIELD_ALLOW)               - 1) },
    { HTTP_HDR_FIELD_AUTHORIZATION,        HTTP_STR_HDR_FIELD_AUTHORIZATION,        (sizeof(HTTP_STR_HDR_FIELD_AUTHORIZATION)       - 1) },
    { HTTP_HDR_FIELD_CONTENT_ENCODING,     HTTP_STR_HDR_FIELD_CONTENT_ENCODING,     (sizeof(HTTP_STR_HDR_FIELD_CONTENT_ENCODING)    - 1) },
    { HTTP_HDR_FIELD_CONTENT_LANGUAGE,     HTTP_STR_HDR_FIELD_CONTENT_LANGUAGE,     (sizeof(HTTP_STR_HDR_FIELD_CONTENT_LANGUAGE)    - 1) },
    { HTTP_HDR_FIELD_CONTENT_LOCATION,     HTTP_STR_HDR_FIELD_CONTENT_LOCATION,     (sizeof(HTTP_STR_HDR_FIELD_CONTENT_LOCATION)    - 1) },
    { HTTP_HDR_FIELD_CONTENT_MD5,          HTTP_STR_HDR_FIELD_CONTENT_MD5,          (sizeof(HTTP_STR_HDR_FIELD_CONTENT_MD5)         - 1) },
    { HTTP_HDR_FIELD_CONTENT_RANGE,        HTTP_STR_HDR_FIELD_CONTENT_RANGE,        (sizeof(HTTP_STR_HDR_FIELD_CONTENT_RANGE)       - 1) },
    { HTTP_HDR_FIELD_COOKIE,               HTTP_STR_HDR_FIELD_COOKIE,               (sizeof(HTTP_STR_HDR_FIELD_COOKIE)              - 1) },
    { HTTP_HDR_FIELD_COOKIE2,              HTTP_STR_HDR_FIELD_COOKIE2,              (sizeof(HTTP_STR_HDR_FIELD_COOKIE2)             - 1) },
    { HTTP_HDR_FIELD_DATE,                 HTTP_STR_HDR_FIELD_DATE,                 (sizeof(HTTP_STR_HDR_FIELD_DATE)                - 1) },
    { HTTP_HDR_FIELD_ETAG,                 HTTP_STR_HDR_FIELD_ETAG,                 (sizeof(HTTP_STR_HDR_FIELD_ETAG)                - 1) },
    { HTTP_HDR_FIELD_EXPECT,               HTTP_STR_HDR_FIELD_EXPECT,               (sizeof(HTTP_STR_HDR_FIELD_EXPECT)              - 1) },
    { HTTP_HDR_FIELD_EXPIRES,              HTTP_STR_HDR_FIELD_EXPIRES,              (sizeof(HTTP_STR_HDR_FIELD_EXPIRES)             - 1) },
    { HTTP_HDR_FIELD_FROM,                 HTTP_STR_HDR_FIELD_FROM,                 (sizeof(HTTP_STR_HDR_FIELD_FROM)                - 1) },
    { HTTP_HDR_FIELD_IF_MODIFIED_SINCE,    HTTP_STR_HDR_FIELD_IF_MODIFIED_SINCE,    (sizeof(HTTP_STR_HDR_FIELD_IF_MODIFIED_SINCE)   - 1) },
    { HTTP_HDR_FIELD_IF_MATCH,             HTTP_STR_HDR_FIELD_IF_MATCH,             (sizeof(HTTP_STR_HDR_FIELD_IF_MATCH)            - 1) },
    { HTTP_HDR_FIELD_IF_NONE_MATCH,        HTTP_STR_HDR_FIELD_IF_NONE_MATCH,        (sizeof(HTTP_STR_HDR_FIELD_IF_NONE_MATCH)       - 1) },
    { HTTP_HDR_FIELD_IF_RANGE,             HTTP_STR_HDR_FIELD_IF_RANGE,             (sizeof(HTTP_STR_HDR_FIELD_IF_RANGE)            - 1) },
    { HTTP_HDR_FIELD_IF_UNMODIFIED_SINCE,  HTTP_STR_HDR_FIELD_IF_UNMODIFIED_SINCE,  (sizeof(HTTP_STR_HDR_FIELD_IF_UNMODIFIED_SINCE) - 1) },
    { HTTP_HDR_FIELD_LAST_MODIFIED,        HTTP_STR_HDR_FIELD_LAST_MODIFIED,        (sizeof(HTTP_STR_HDR_FIELD_LAST_MODIFIED)       - 1) },
    { HTTP_HDR_FIELD_RANGE,                HTTP_STR_HDR_FIELD_RANGE,                (sizeof(HTTP_STR_HDR_FIELD_RANGE)               - 1) },
    { HTTP_HDR_FIELD_REFERER,              HTTP_STR_HDR_FIELD_REFERER,              (sizeof(HTTP_STR_HDR_FIELD_REFERER)             - 1) },
    { HTTP_HDR_FIELD_RETRY_AFTER,          HTTP_STR_HDR_FIELD_RETRY_AFTER,          (sizeof(HTTP_STR_HDR_FIELD_RETRY_AFTER)         - 1) },
    { HTTP_HDR_FIELD_SERVER,               HTTP_STR_HDR_FIELD_SERVER,               (sizeof(HTTP_STR_HDR_FIELD_SERVER)              - 1) },
    { HTTP_HDR_FIELD_SET_COOKIE,           HTTP_STR_HDR_FIELD_SET_COOKIE,           (sizeof(HTTP_STR_HDR_FIELD_SET_COOKIE)          - 1) },
    { HTTP_HDR_FIELD_SET_COOKIE2,          HTTP_STR_HDR_FIELD_SET_COOKIE2,          (sizeof(HTTP_STR_HDR_FIELD_SET_COOKIE2)         - 1) },
    { HTTP_HDR_FIELD_TE,                   HTTP_STR_HDR_FIELD_TE,                   (sizeof(HTTP_STR_HDR_FIELD_TE)                  - 1) },
    { HTTP_HDR_FIELD_TRAILER,              HTTP_STR_HDR_FIELD_TRAILER,              (sizeof(HTTP_STR_HDR_FIELD_TRAILER)             - 1) },
    { HTTP_HDR_FIELD_UPGRATE,              HTTP_STR_HDR_FIELD_UPGRATE,              (sizeof(HTTP_STR_HDR_FIELD_UPGRATE)             - 1) },
    { HTTP_HDR_FIELD_USER_AGENT,           HTTP_STR_HDR_FIELD_USER_AGENT,           (sizeof(HTTP_STR_HDR_FIELD_USER_AGENT)          - 1) },
    { HTTP_HDR_FIELD_VARY,                 HTTP_STR_HDR_FIELD_VARY,                 (sizeof(HTTP_STR_HDR_FIELD_VARY)                - 1) },
    { HTTP_HDR_FIELD_VIA,                  HTTP_STR_HDR_FIELD_VIA,                  (sizeof(HTTP_STR_HDR_FIELD_VIA)                 - 1) },
    { HTTP_HDR_FIELD_WARNING,              HTTP_STR_HDR_FIELD_WARNING,              (sizeof(HTTP_STR_HDR_FIELD_WARNING)             - 1) },
    { HTTP_HDR_FIELD_WWW_AUTHENTICATE,     HTTP_STR_HDR_FIELD_WWW_AUTHENTICATE,     (sizeof(HTTP_STR_HDR_FIELD_WWW_AUTHENTICATE)    - 1) },
};


/*
*********************************************************************************************************
*                                      HTTP CONTENT DISPOSITION VALUE
*********************************************************************************************************
*/

#define  HTTP_STR_CONTENT_DISPOSITION_FORM_DATA        "form-data"

#define  HTTP_STR_CONTENT_DISPOSITION_FORM_DATA_LEN     sizeof(HTTP_STR_CONTENT_DISPOSITION_FORM_DATA)  - 1

static  const  HTTP_DICTIONARY  HTTP_DictionaryContentDispositionValue[] = {
    { HTTP_CONTENT_DISPOSITION_FORM_DATA,  HTTP_STR_CONTENT_DISPOSITION_FORM_DATA,  (sizeof(HTTP_STR_CONTENT_DISPOSITION_FORM_DATA)  - 1)},
};


/*
*********************************************************************************************************
*                                        HTTP CONNECTION VALUE
*********************************************************************************************************
*/

#define  HTTP_STR_HDR_FIELD_CONN_CLOSE                     "close"
#define  HTTP_STR_HDR_FIELD_CONN_KEEP_ALIVE                "keep-alive"

static  const  HTTP_DICTIONARY  HTTP_DictionaryHdrFieldsConnValue[] = {
    { HTTP_HDR_FIELD_CONN_CLOSE,      HTTP_STR_HDR_FIELD_CONN_CLOSE,      (sizeof(HTTP_STR_HDR_FIELD_CONN_CLOSE)      - 1)},
    { HTTP_HDR_FIELD_CONN_PERSISTENT, HTTP_STR_HDR_FIELD_CONN_KEEP_ALIVE, (sizeof(HTTP_STR_HDR_FIELD_CONN_KEEP_ALIVE) - 1)},
};


/*
*********************************************************************************************************
*                                   HTTP TRANSFER ENCODING VALUE
*********************************************************************************************************
*/


#define  HTTP_STR_HDR_FIELD_CHUNKED                     "chunked"
#define  HTTP_STR_BUF_TOP_SPACE_REQ_MIN                        6
#define  HTTP_STR_BUF_END_SPACE_REQ_MIN                        2

static  const  HTTP_DICTIONARY  HTTP_DictionaryHdrFieldsTransferTypeValue[] = {
    { HTTP_HDR_FIELD_TRANSFER_TYPE_CHUNCKED, HTTP_STR_HDR_FIELD_CHUNKED, (sizeof(HTTP_STR_HDR_FIELD_CHUNKED)   - 1) },
};


/*
*********************************************************************************************************
*                                  HTTP CGI MULTIPART CONTENT FIELD
*********************************************************************************************************
*/

typedef enum http_multipart_field {
    HTTP_MULTIPART_FIELD_NAME,
    HTTP_MULTIPART_FIELD_FILE_NAME,
    HTTP_MULTIPART_FIELD_UNKNOWN
} HTTP_MULTIPART_FIELD;

#define  HTTP_STR_MULTIPART_FIELD_NAME                     "name"
#define  HTTP_STR_MULTIPART_FIELD_FILE_NAME                "filename"

#define  HTTP_STR_MULTIPART_FIELD_NAME_LEN                  sizeof(HTTP_STR_MULTIPART_FIELD_NAME)      - 1
#define  HTTP_STR_MULTIPART_FIELD_FILE_NAME_LEN             sizeof(HTTP_STR_MULTIPART_FIELD_FILE_NAME) - 1

static  const  HTTP_DICTIONARY  HTTP_DictionaryMultipartFields[] = {
    { HTTP_MULTIPART_FIELD_NAME,      HTTP_STR_MULTIPART_FIELD_NAME,      (sizeof(HTTP_STR_MULTIPART_FIELD_NAME)      - 1) },
    { HTTP_MULTIPART_FIELD_FILE_NAME, HTTP_STR_MULTIPART_FIELD_FILE_NAME, (sizeof(HTTP_STR_MULTIPART_FIELD_FILE_NAME) - 1) },
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
*                                        HTTP COUNTER MACRO'S
*
* Description : Functionality to set and increment statistic and error counter
*
* Argument(s) : Various HTTP counter variable(s) & values.
*
* Return(s)   : none.
*
* Caller(s)   : various.
*
*               These macro's are INTERNAL HTTP suite macro's & SHOULD NOT be called by
*               application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if ((HTTPs_CFG_CTR_STAT_EN == DEF_ENABLED) || \
     (HTTPc_CFG_CTR_STAT_EN == DEF_ENABLED))
#define  HTTP_SET_PTR_STATS(p_ctr_stats, p_instance)   {                                           \
                                                           p_ctr_stats = &p_instance->StatsCtr;    \
                                                       }

#define  HTTP_STATS_INC(p_ctr)                         {                                           \
                                                            p_ctr++;                               \
                                                       }

#define  HTTP_STATS_OCTET_INC(p_ctr, octet)            {                                           \
                                                            p_ctr += octet;                        \
                                                       }

#else
                                                                /* Prevent 'variable unused' compiler warning.          */
#define  HTTP_SET_PTR_STATS(p_ctr_stats, p_instance)   {                                           \
                                                          (void)&p_ctr_stats;                      \
                                                       }

#define  HTTP_STATS_INC(p_ctr)

#define  HTTP_STATS_OCTET_INC(p_ctr, octet)

#endif



#if ((HTTPs_CFG_CTR_ERR_EN == DEF_ENABLED) || \
     (HTTPc_CFG_CTR_ERR_EN == DEF_ENABLED))

#define  HTTP_SET_PTR_ERRS(p_ctr_err, p_instance)      {                                           \
                                                            p_ctr_err = &p_instance->ErrsCtr;      \
                                                       }

#define  HTTP_ERR_INC(p_ctr)                           {                                           \
                                                            p_ctr++;                               \
                                                       }

#else
                                                                 /* Prevent 'variable unused' compiler warning.          */
#define  HTTP_SET_PTR_ERRS(p_ctr_err, p_instance)      {                                           \
                                                          (void)&p_ctr_err;                        \
                                                       }

#define  HTTP_ERR_INC(p_ctr)

#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

CPU_CHAR           *HTTP_HdrParseFieldValueGet     (       CPU_CHAR          *p_field,
                                                           CPU_INT16U         field_len,
                                                           CPU_CHAR          *p_field_end,
                                                           CPU_INT16U        *p_len_rem);

CPU_CHAR           *HTTP_StrGraphSrchFirst         (       CPU_CHAR          *p_str,
                                                           CPU_INT32U         str_len);

CPU_INT32U          HTTP_DictionaryKeyGet          (const  HTTP_DICTIONARY   *p_dictionary_tbl,
                                                           CPU_INT32U         dictionary_size,
                                                    const  CPU_CHAR          *p_str_cmp,
                                                           CPU_BOOLEAN        case_sensitive,
                                                           CPU_INT32U         str_len);

HTTP_DICTIONARY    *HTTP_DictionaryEntryGet        (const  HTTP_DICTIONARY   *p_dictionary_tbl,
                                                           CPU_INT32U         dictionary_size,
                                                           CPU_INT32U         key);

CPU_CHAR           *HTTP_DictionaryValCopy         (const  HTTP_DICTIONARY   *p_dictionary_tbl,
                                                           CPU_INT32U         dictionary_size,
                                                           CPU_INT32U         key,
                                                           CPU_CHAR          *p_buf,
                                                           CPU_SIZE_T         buf_len);

CPU_CHAR           *HTTP_DictionaryStrKeySrch      (const  HTTP_DICTIONARY   *p_dictionary_tbl,
                                                           CPU_INT32U         dictionary_size,
                                                           CPU_INT32U         key,
                                                    const  CPU_CHAR          *p_str,
                                                           CPU_SIZE_T         str_len);

CPU_BOOLEAN         HTTP_URL_EncodeStr             (const  CPU_CHAR          *p_str_src,
                                                           CPU_CHAR          *p_str_dest,
                                                           CPU_SIZE_T        *p_str_len,
                                                           CPU_SIZE_T         str_len_max);

CPU_BOOLEAN         HTTP_URL_DecodeStr             (const  CPU_CHAR          *p_str_src,
                                                           CPU_CHAR          *p_str_dest,
                                                           CPU_SIZE_T        *p_str_lenn);

CPU_INT16U          HTTP_URL_CharEncodeNbr         (const  CPU_CHAR          *p_str_src,
                                                           CPU_SIZE_T         str_len);

CPU_CHAR           *HTTP_ChunkTransferWrSize       (       CPU_CHAR          *p_buf_wr,
                                                           CPU_SIZE_T         buf_len,
                                                           CPU_INT16U         size);

HTTP_CONTENT_TYPE   HTTP_GetContentTypeFromFileExt (       CPU_CHAR          *p_file_path,
                                                           CPU_SIZE_T         path_len_max);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif  /* HTTP_MODULE_PRESENT  */
