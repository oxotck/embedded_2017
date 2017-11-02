/*
*********************************************************************************************************
*                                             uC/Trace
*                                      The RTOS Event Analyzer
*
*                         (c) Copyright 2004-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/Trace is provided in source form to registered licensees ONLY.  It is
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
*                                             UC/TRACE
*
* File          : trace.h
* Version       : V1.00.00
* Programmer(s) : JPB
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              MODULE
*********************************************************************************************************
*/

#ifndef   TRACE_H
#define   TRACE_H


/*
*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************
*/

#include  <trcConfig.h>
#include  <trcHardwarePort.h>

#include  "../Recorders/Percepio/TraceRecorderLibrary/Include/trcBase.h"
#include  "../Recorders/Percepio/TraceRecorderLibrary/Include/trcKernel.h"
#include  "../Recorders/Percepio/TraceRecorderLibrary/Include/trcKernelHooks.h"
#include  "../Recorders/Percepio/TraceRecorderLibrary/Include/trcTypes.h"
#include  "../Recorders/Percepio/TraceRecorderLibrary/Include/trcUser.h"

#include  "../Recorders/Percepio/TraceRecorderLibrary/KernelPorts/uCOS-III/trcKernelPort.h"

#include  "../Recorders/Percepio/OS/uCOS-III/trace_os.h"

#include <lib_def.h>


/*
*********************************************************************************************************
*                                      UC/TRACE TRIGGERS MODULE
*
* Note(s) : The uC/Trace Triggering mechanism requires the hardware platform to be 
*           supported by uC/Probe.
*
*           If your platform is uC/Probe-ready, then enable this module by setting
*           the macro below to 1.
*********************************************************************************************************
*/

#if (defined(TRACE_CFG_TRIG_EN) && (TRACE_CFG_TRIG_EN > 0u))


/*
*********************************************************************************************************
*                                              DEFINES
*********************************************************************************************************
*/

#define  TRACE_TRIG(id)                    TraceTrig(id)


/*
*********************************************************************************************************
*                                            ENUMERATIONS
*********************************************************************************************************
*/

typedef  enum  trace_trig_status_ep {
    TRACE_TRIG_STATUS_EP_IDLE             = 0u,
    TRACE_TRIG_STATUS_EP_BUSY             = 1u,
    TRACE_TRIG_STATUS_EP_READY            = 2u
} TRACE_TRIG_STATUS_EP;


typedef  enum  trace_trig_status_trig {
    TRACE_TRIG_STATUS_TRIG_DISARMED       = 0u,
    TRACE_TRIG_STATUS_TRIG_ARMED          = 1u,
    TRACE_TRIG_STATUS_TRIG_RECORDING      = 2u,
    TRACE_TRIG_STATUS_TRIG_READY          = 3u,
    TRACE_TRIG_STATUS_TRIG_IGNORED        = 4u
} TRACE_TRIG_STATUS_TRIG;


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

typedef  struct  trace_trig_status_probe {
    TRACE_TRIG_STATUS_EP    Probe;
    TRACE_TRIG_STATUS_EP    Target;
} TRACE_TRIG_STATUS;


typedef  struct  trace_trig {
    CPU_INT16U              ID;                                 /* Trigger ID.                                          */
    const CPU_CHAR         *NamePtr;                            /* Trigger Name.                                        */
    CPU_INT08U              MaxNbrFiles;                        /* Maximum number of recording files before disarming.  */
    CPU_BOOLEAN             Armed;                              /* Flag set by uC/Probe to enable/disable triggering.   */
    TRACE_TRIG_STATUS_TRIG  Status;                             /* Flag set by the Target to display status in uC/Probe */
} TRACE_TRIG;


typedef  struct  trace_trigs {
    TRACE_TRIG              Trig[TRACE_CFG_TRIG_MAX_TRIGS];     /* Array of uC/Trace triggers.                          */
    CPU_INT08U              Qty;                                /* Number of triggers.                                  */
    TRACE_TRIG_STATUS       Status;                             /* Overall status of uC/Probe and the Target.           */
    CPU_INT08U              CurIx;                              /* Index of the current recording.                      */
} TRACE_TRIGS;


typedef  const  struct  trace_trigs_cfg {
    CPU_INT16U              ID;                                 /* Trigger ID.                                          */
    CPU_CHAR                Name[TRACE_CFG_TRIG_NAME_LEN];      /* Trigger Name.                                        */
    CPU_INT08U              MaxNbrFiles;                        /* Maximum number of recording files before disarming.  */
} TRACE_CFG_TRIG;


/*
*********************************************************************************************************
*                                    UC/TRACE TRIGGERS CONFIGURATION
*********************************************************************************************************
*/

extern  const  TRACE_CFG_TRIG  TraceCfgTrigTbl[];
extern  const  CPU_INT08U      TraceCfgTrigTblLen;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  TraceTrigInit(void);
void  TraceTrig    (CPU_INT32U);

#endif                                                          /* End of uC/Trace Triggering Module.                   */


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of trace module include.                         */