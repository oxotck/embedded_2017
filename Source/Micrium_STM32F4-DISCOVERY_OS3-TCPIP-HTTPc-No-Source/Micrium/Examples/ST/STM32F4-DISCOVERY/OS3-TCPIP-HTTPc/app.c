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
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*                                         STM32F4DISCOVERY
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <includes.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

                                                                /* --------------- APPLICATION GLOBALS ---------------- */
static  OS_TCB         AppTaskStartTCB;

static  CPU_STK        AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void         AppTaskStart  (void  *p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int main(void)
{
    OS_ERR   err;
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_ERR  cpu_err;
#endif

    CPU_Init();                                                 /* Initialize the uC/CPU services                       */
    Mem_Init();                                                 /* Initialize Memory Mmanagment Module                  */
    Math_Init();                                                /* Initialize Mathematical Module                       */

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_NameSet((CPU_CHAR *)"STM32F407VG",
                (CPU_ERR  *)&cpu_err);
#endif

    BSP_IntDisAll();                                            /* Disable all Interrupts.                              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */

    OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,              /* Create the start task                                */
                 (CPU_CHAR     *)"App Task Start",
                 (OS_TASK_PTR   )AppTaskStart,
                 (void         *)0u,
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO,
                 (CPU_STK      *)&AppTaskStartStk[0u],
                 (CPU_STK_SIZE  )AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10u],
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

#if (OS_TASK_NAME_EN > 0u)
    OSTaskNameSet(APP_CFG_TASK_START_PRIO, "Start Task", &err);
#endif

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */

    while (DEF_ON) {                                            /* Should Never Get Here.                               */
    };
}

/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
#if ((APP_CFG_DNS_C_EN == DEF_ENABLED) || (APP_CFG_HTTP_C_EN == DEF_ENABLED))
    CPU_BOOLEAN  init_flag;
#endif
    OS_ERR       err;


   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    BSP_Tick_Init();                                            /* Start Tick Initialization                            */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif


#if (APP_CFG_TCPIP_EN == DEF_ENABLED)
    AppTCPIP_Init();                                            /* Initialize uC/TCPIP Module.                          */
#endif

#if (APP_CFG_DNS_C_EN == DEF_ENABLED)
    init_flag = App_DNScInit();
    if (init_flag == DEF_OK) {
        APP_TRACE_INFO(("DNSc initialized correctly\r\n"));
    } else {
        APP_TRACE_INFO(("DNSc initialization failed\r\n"));
    }
#endif

#if (APP_CFG_HTTP_C_EN == DEF_ENABLED)                          /* HTTPc Application Initalization                      */
    init_flag = HTTPcApp_Init();
    if (init_flag == DEF_OK) {
        APP_TRACE_INFO(("HTTPc initialized correctly\r\n"));
    } else {
        APP_TRACE_INFO(("HTTPc initialization failed.....\r\n"));
    }
#endif

    BSP_LED_Off(0u);

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        BSP_LED_Toggle(3u);
                                                                /* Request current weather data from server             */
        HTTPcApp_ReqWeather();

    }
}

