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
*
*                                   UC/TRACE RECORDER AND TRIGGERS
*                                         CONFIGURATION FILE
*
*                                              TEMPLATE
*
* File          : trace_cfg.h
* Version       : V1.00.00
* Programmer(s) : JPB
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef   TRACE_CFG_H
#define   TRACE_CFG_H



/*
*********************************************************************************************************
*                                             HARDWARE PORT
*
* Note(s) : The recorder needs to have knowledge of the hardware platform your are running,
*           the timer/counter used for driving the system ticker in particular.
*
*           Select from one of the following supported platforms:
*
*                       - ARM CORTEX-M   :     4u
*                       - RENESAS RX600  :     5u
*                       - ARM CORTEX-A   :    14u
*********************************************************************************************************
*/

#define  TRACE_CFG_HW_PORT                     4u


/*
*********************************************************************************************************
*                                        BSP CPU CLOCK FREQUENCY
*
* Note(s) : The recorder needs to have knowledge of the frequency of the CPU's clock.
*           A function that returns the frequency in Hz is usually declared in bsp.c
*********************************************************************************************************
*/

#define  TRACE_CFG_CPU_CLK_FREQ           BSP_CPU_ClkFreq()


/*
*********************************************************************************************************
*                                           RECORDING BUFFER
*
* Note(s) : This defines the capacity of the event buffer, i.e., the number of records it may store.
*           Each recorded event typically uses one record (4 byte in RAM).
*           Adjust to your application needs and memory resources.
*********************************************************************************************************
*/

#define  TRACE_CFG_MAX_EVENTS               8000u


/*
*********************************************************************************************************
*                                        RECORDED KERNEL OBJECTS
*
* Note(s) : These define the maximum number of kernel object types to record. 
*           Adjust to your application needs and memory resources.
*********************************************************************************************************
*/

#define  TRACE_CFG_MAX_TASK                   32u
#define  TRACE_CFG_MAX_ISR                     8u
#define  TRACE_CFG_MAX_Q                      16u
#define  TRACE_CFG_MAX_SEM                   124u
#define  TRACE_CFG_MAX_MUTEX                   8u
#define  TRACE_CFG_MAX_FLAG                    2u
#define  TRACE_CFG_MAX_MEM                     2u


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

#define  TRACE_CFG_TRIG_EN                     0u

#if (defined(TRACE_CFG_TRIG_EN) && (TRACE_CFG_TRIG_EN > 0u))


/*
*********************************************************************************************************
*                                     UC/TRACE TRIGGERS SETTINGS
*********************************************************************************************************
*/

#define  TRACE_CFG_TRIG_MAX_TRIGS             16u
#define  TRACE_CFG_TRIG_NAME_LEN              32u


/*
*********************************************************************************************************
*                                   UC/TRACE TRIGGERS TASK SETTINGS
*********************************************************************************************************
*/

#define  TRACE_CFG_TRIG_TASK_STK_SIZE        256u
#define  TRACE_CFG_TRIG_TASK_PRIO             20u


/*
*********************************************************************************************************
*                                        UC/TRACE TRIGGERS IDS
*
* Note(s) : First you create a series of unique IDs for each of your trigger points. 
*           In this example TRACE_CFG_TRIG_ID_SW1 is the trigger point executed when 
*           you press the board's switch 1.
*********************************************************************************************************
*/

#define  TRACE_CFG_TRIG_ID_SW1              1234u
#define  TRACE_CFG_TRIG_ID_SW2              1235u
#define  TRACE_CFG_TRIG_ID_SW3              1236u

#endif                                                          /* End of uC/Trace Triggering Module.                   */

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of trace cfg module include.                     */