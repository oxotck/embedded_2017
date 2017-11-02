/*
*********************************************************************************************************
*                                             uC/TCP-IP V3
*                                      The Embedded TCP/IP Suite
*
*                          (c) Copyright 2003-2011; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/TCP-IP is provided in source form to registered licensees ONLY.  It is
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
*                            NETWORK BOARD SUPPORT PACKAGE (BSP) FUNCTIONS
*
*                                     ST Microelectronics STM32
*                                              on the
*                                         STM32F4DISCOVERY
*
* Filename      : net_bsp.c
* Version       : V3.00
* Programmer(s) : ITJ
*                 DC
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    NET_BSP_MODULE
#include  <net.h>
#include  <bsp.h>
#include  <net_bsp.h>
#include  <stm32f4xx_gpio.h>
#include  <stm32f4xx_rcc.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                  NETWORK DEVICE INTERFACE NUMBERS
*
* Note(s) : (1) (a) Each network device maps to a unique network interface number.
*
*               (b) Instances of network devices' interface number SHOULD be named using the following
*                   convention :
*
*                       <Board><Device>[Number]_IF_Nbr
*
*                           where
*                                   <Board>         Development board name
*                                   <Device>        Network device name (or type)
*                                   [Number]        Network device number for each specific instance
*                                                       of device (optional if the development board
*                                                       does NOT support multiple instances of the
*                                                       specific device)
*
*                   For example, the network device interface number variable for the #2 MACB Ethernet
*                   controller on an Atmel AT91SAM92xx should be named 'AT91SAM92xx_MACB_2_IF_Nbr'.
*
*               (c) Network device interface number variables SHOULD be initialized to 'NET_IF_NBR_NONE'.
*********************************************************************************************************
*/

#ifdef  NET_IF_ETHER_MODULE_EN
static  NET_IF_NBR  STM32F4xx_IF_Nbr = NET_IF_NBR_NONE;
#endif


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                               NETWORK DEVICE BSP FUNCTION PROTOTYPES
*
* Note(s) : (1) Device driver BSP functions may be arbitrarily named.  However, it is recommended that
*               device BSP functions be named using the suggested names/conventions provided below.
*
*               (a) (1) Network device BSP functions SHOULD be named using the following convention :
*
*                           NetDev_[Device]<Function>[Number]()
*
*                               where
*                                   (A) [Device]        Network device name or type (optional if the
*                                                           development board does NOT support multiple
*                                                           devices)
*                                   (B) <Function>      Network device BSP function
*                                   (C) [Number]        Network device number for each specific instance
*                                                           of device (optional if the development board
*                                                           does NOT support multiple instances of the
*                                                           specific device)
*
*                       For example, the NetDev_CfgClk() function for the #2 MACB Ethernet controller
*                       on an Atmel AT91SAM92xx should be named NetDev_MACB_CfgClk2().
*
*                   (2) BSP-level device ISR handlers SHOULD be named using the following convention :
*
*                           NetDev_[Device]ISR_Handler[Type][Number]()
*
*                               where
*                                   (A) [Device]        Network device name or type (optional if the
*                                                           development board does NOT support multiple
*                                                           devices)
*                                   (B) [Type]          Network device interrupt type (optional if
*                                                           interrupt type is generic or unknown)
*                                   (C) [Number]        Network device number for each specific instance
*                                                           of device (optional if the development board
*                                                           does NOT support multiple instances of the
*                                                           specific device)
*
*               (b) All BSP function prototypes SHOULD be located within the development board's network
*                   BSP C source file ('net_bsp.c') & be declared as static functions to prevent name
*                   clashes with other network protocol suite BSP functions/files.
*********************************************************************************************************
*/

static  void        NetDev_CfgClk                (NET_IF   *pif,
                                                  NET_ERR  *perr);

static  void        NetDev_CfgIntCtrl            (NET_IF   *pif,
                                                  NET_ERR  *perr);

static  void        NetDev_CfgGPIO               (NET_IF   *pif,
                                                  NET_ERR  *perr);

static  CPU_INT32U  NetDev_ClkFreqGet            (NET_IF   *pif,
                                                  NET_ERR  *perr);


static  void        NetBSP_ISR_HandlerSTM32F4xx  (void);


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    NETWORK DEVICE BSP INTERFACE
*
* Note(s) : (1) Device board-support package (BSP) interface structures are used by the device driver to
*               call specific devices' BSP functions via function pointer instead of by name.  This enables
*               the network protocol suite to compile & operate with multiple instances of multiple devices
*               & drivers.
*
*           (2) In most cases, the BSP interface structure provided below SHOULD suffice for most devices'
*               BSP functions exactly as is with the exception that BSP interface structures' names MUST be
*               unique & SHOULD clearly identify the development board, device name, & possibly the specific
*               device number (if the development board supports multiple instances of any given device).
*
*               (a) BSP interface structures SHOULD be named using the following convention :
*
*                       NetDev_BSP_<Board><Device>[Number]{}
*
*                           where
*                               (1) <Board>         Development board name
*                               (2) <Device>        Network device name (or type)
*                               (3) [Number]        Network device number for each specific instance
*                                                       of device (optional if the development board
*                                                       does NOT support multiple instances of the
*                                                       specific device)
*
*                   For example, the BSP interface structure for the #2 MACB Ethernet controller on
*                   an Atmel AT91SAM92xx should be named NetDev_BSP_AT91SAM92xx_MACB_2{}.
*
*               (b) The BSP interface structure MUST also be externally declared in the development
*                   board's network BSP header file ('net_bsp.h') with the exact same name & type.
*********************************************************************************************************
*/

const  NET_DEV_BSP_ETHER  NetDev_BSP_STM32F4xx = {                       /* Board-/device-specific BSP fnct ptrs :      */
                                                   &NetDev_CfgClk,       /*   Cfg clk(s)                                */
                                                   &NetDev_CfgIntCtrl,   /*   Cfg int ctrl(s)                           */
                                                   &NetDev_CfgGPIO,      /*   Cfg GPIO                                  */
                                                   &NetDev_ClkFreqGet    /*   Get clk freq                              */
                                                 };

/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                   NETWORK DEVICE DRIVER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           NetDev_CfgClk()
*
* Description : Configure clocks for the specified interface/device.
*
* Argument(s) : pif         Pointer to network interface to configure.
*               ---         Argument validated in NetDev_Init().
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device clock(s)     successfully configured.
*                               NET_DEV_ERR_FAULT               Device clock(s) NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : (1) The external Ethernet Phy may be clocked using several different sources.  The
*                   resulting Phy clock MUST be 25MHz for MII and 50MHz for RMII :
*
*                   (a) RCC_MCO_NoClock    External Phy clocked directly via external crystal.
*                   (b) RCC_MCO_XT1        External Phy clocked by HSE   via MCO output.
*                   (c) RCC_MCO_PLL3CLK    External Phy clocked by PLL3  via MCO output.
*********************************************************************************************************
*/

static  void  NetDev_CfgClk (NET_IF   *pif,
                             NET_ERR  *perr)
{
    NET_PHY_CFG_ETHER  *pphy_cfg;


    pphy_cfg = pif->Ext_Cfg;                                    /* Obtain pointer to Phy cfg.                           */
    if (pphy_cfg == (NET_PHY_CFG_ETHER *)0u) {
       *perr = NET_DEV_ERR_INVALID_CFG;
        return;
    }

    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_ETH_MAC, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_ETH_MAC, DISABLE);


    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC     |
                           RCC_AHB1Periph_ETH_MAC_Tx  |
                           RCC_AHB1Periph_ETH_MAC_Rx,
                           ENABLE);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA       |
                           RCC_AHB1Periph_GPIOB       |
                           RCC_AHB1Periph_GPIOC       |
                           RCC_AHB1Periph_GPIOE,
                           ENABLE);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  

    if (pphy_cfg->BusMode == NET_PHY_BUS_MODE_MII) {            /* See Note #2.                                         */
        RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);
        SYSCFG_ETH_MediaInterfaceConfig(SYSCFG_ETH_MediaInterface_MII);
    } else {
        RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_2);
        SYSCFG_ETH_MediaInterfaceConfig(SYSCFG_ETH_MediaInterface_RMII);
    }

   *perr = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                         NetDev_CfgIntCtrl()
*
* Description : Configure interrupts &/or interrupt controller for the specified interface/device.
*
* Argument(s) : pif         Pointer to network interface to configure.
*               ---         Argument validated in NetDev_Init().
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device interrupt(s)     successfully configured.
*                               NET_DEV_ERR_FAULT               Device interrupt(s) NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_CfgIntCtrl (NET_IF   *pif,
                                 NET_ERR  *perr)
{
    STM32F4xx_IF_Nbr = pif->Nbr;                                /* Cfg this dev's BSP instance with specific IF #.      */

    BSP_IntVectSet(BSP_INT_ID_ETH, NetBSP_ISR_HandlerSTM32F4xx);
    BSP_IntEn(BSP_INT_ID_ETH);

   *perr = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                          NetDev_CfgGPIO()
*
* Description : Configure general-purpose I/O (GPIO) for the specified interface/device.
*
* Argument(s) : pif         Pointer to network interface to configure.
*               ---         Argument validated in NetDev_Init().
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device GPIO     successfully configured.
*                               NET_DEV_ERR_FAULT               Device GPIO NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_CfgGPIO (NET_IF   *pif,
                              NET_ERR  *perr)
{
    CPU_INT16U          i;  
    NET_PHY_CFG_ETHER  *pphy_cfg;
    GPIO_InitTypeDef    GPIO_InitStructure;


    pphy_cfg = pif->Ext_Cfg;                                    /* Obtain pointer to Phy cfg.                           */
    if (pphy_cfg == (NET_PHY_CFG_ETHER *)0u) {
       *perr = NET_DEV_ERR_INVALID_CFG;
        return;
    }
  
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_ETH);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_ETH);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_ETH);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_ETH);	
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_ETH);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_ETH);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_ETH);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_ETH);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_ETH);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_ETH);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOE, GPIO_Pin_2);	
    for (i = 0; i < 20000; i++);
    GPIO_SetBits(GPIOE, GPIO_Pin_2);
    for (i = 0; i < 20000; i++);
    

   *perr = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                         NetDev_ClkFreqGet()
*
* Description : Get device clock frequency.
*
* Argument(s) : pif         Pointer to network interface to get clock frequency.
*               ---         Argument validated in NetDev_Init().
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device clock frequency     successfully
*                                                                   returned.
*                               NET_DEV_ERR_FAULT               Device clock frequency NOT successfully
*                                                                   returned.
*
* Return(s)   : Device clock frequency (in Hz).
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT32U  NetDev_ClkFreqGet (NET_IF   *pif,
                                       NET_ERR  *perr)
{
    CPU_INT32U  clk_freq;


   (void)&pif;                                                  /* Prevent 'variable unused' compiler warning.          */

    clk_freq = BSP_CPU_ClkFreq();                               /* HCLK is the MDC clk input freq.                      */
   *perr     = NET_DEV_ERR_NONE;

    return (clk_freq);
}


/*
*********************************************************************************************************
*                                        NetBSP_ISR_HandlerSTM32F4xx()
*
* Description : BSP-level ISR handler(s) for device interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU &/or device interrupts.
*
* Note(s)     : (1) (a) Each device interrupt, or set of device interrupts, MUST be handled by a
*                       unique BSP-level ISR handler which maps each specific device interrupt to
*                       its corresponding network interface ISR handler.
*
*                   (b) BSP-level device ISR handlers SHOULD be named using the following convention :
*
*                           NetDev_[Device]ISR_Handler[Type][Number]()
*
*                               where
*                                   (1) [Device]        Network device name or type (optional if the
*                                                           development board does NOT support multiple
*                                                           devices)
*                                   (2) [Type]          Network device interrupt type (optional if
*                                                           interrupt type is generic or unknown)
*                                   (3) [Number]        Network device number for each specific instance
*                                                           of device (optional if the development board
*                                                           does NOT support multiple instances of the
*                                                           specific device)
*
*                       See also 'NETWORK DEVICE BSP FUNCTION PROTOTYPES  Note #2a2'.
*********************************************************************************************************
*/

static  void  NetBSP_ISR_HandlerSTM32F4xx (void)
{
    NET_ERR  err;


    NetIF_ISR_Handler(STM32F4xx_IF_Nbr, NET_DEV_ISR_TYPE_UNKNOWN, &err);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                      NETWORK MODULE FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/
#if 0
/*
*********************************************************************************************************
*                                          NetUtil_TS_Get()
*
* Description : Get current Internet Timestamp.
*
*               (1) "The Timestamp is a right-justified, 32-bit timestamp in milliseconds since midnight
*                    UT [Universal Time]" (RFC #791, Section 3.1 'Options : Internet Timestamp').
*
*               (2) The developer is responsible for providing a real-time clock with correct time-zone
*                   configuration to implement the Internet Timestamp, if possible.
*
*
* Argument(s) : none.
*
* Return(s)   : Internet Timestamp.
*
* Caller(s)   : various.
*
*               This function is an INTERNAL network protocol suite function but MAY be called by
*               application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

NET_TS  NetUtil_TS_Get (void)
{
    NET_TS  ts;


    /* $$$$ Insert code to return Internet Timestamp (see Notes #1 & #2).   */

    ts = NET_TS_NONE;

    return (ts);
}


/*
*********************************************************************************************************
*                                         NetUtil_TS_Get_ms()
*
* Description : Get current millisecond timestamp.
*
*               (1) (a) (1) Although RFC #2988, Section 4 states that "there is no requirement for the
*                           clock granularity G used for computing [TCP] RTT measurements ... experience
*                           has shown that finer clock granularities (<= 100 msec) perform somewhat
*                           better than more coarse granularities".
*
*                       (2) (A) RFC #2988, Section 2.4 states that "whenever RTO is computed, if it is
*                               less than 1 second then the RTO SHOULD be rounded up to 1 second".
*
*                           (B) RFC #1122, Section 4.2.3.1 states that "the recommended ... RTO ... upper
*                               bound should be 2*MSL" where RFC #793, Section 3.3 'Sequence Numbers :
*                               Knowing When to Keep Quiet' states that "the Maximum Segment Lifetime
*                               (MSL) is ... to be 2 minutes".
*
*                               Therefore, the required upper bound is :
*
*                                   2 * MSL = 2 * 2 minutes = 4 minutes = 240 seconds
*
*                   (b) Therefore, the developer is responsible for providing a timestamp clock with
*                       adequate resolution to satisfy the clock granularity (see Note #1a1) & adequate
*                       range to satisfy the minimum/maximum TCP RTO values  (see Note #1a2).
*
* Argument(s) : none.
*
* Return(s)   : Timestamp, in milliseconds.
*
* Caller(s)   : NetIF_PerfMonHandler(),
*               NetTCP_RxPktValidate(),
*               NetTCP_TxPktPrepareHdr().
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s).
*
* Note(s)     : (2) (a) To avoid  timestamp calculation overflow, timestamps are updated by continually
*                       summing OS time tick delta differences converted into milliseconds :
*
*                                  Total                       [                        1000 ms/sec  ]
*                           (A)  Timestamp  =    Summation     [ (time  - time   )  *  ------------- ]
*                                 (in ms)     i = 1 --> i = N  [      i       i-1       M ticks/sec  ]
*
*
*                                   where
*                                           time        Instantaneous time value (in OS ticks/second)
*                                           M           Number of OS time ticks per second
*
*
*                       (1) However, multiplicative overflow is NOT totally avoided if the product of
*                           the OS time tick delta difference & the constant time scalar (i.e. 1000
*                           milliseconds per second) overflows the integer data type :
*
*                           (A)                 (time_delta * time_scalar)  >=  2^N
*
*                                   where
*                                           time_delta      Calculated time delta difference
*                                           time_scalar     Constant   time scalar (e.g. 1000 ms/1 sec)
*                                           N               Number of data type bits (e.g. 32)
*
*
*                   (b) To ensure timestamp calculation accuracy, timestamp calculations sum timestamp
*                       integer remainders back into total accumulated timestamp :
*
*                                  Total                         [                        1000 ms/sec  ]
*                           (A)  Timestamp  =      Summation     [ (time  - time   )  *  ------------- ]
*                                 (in ms)       i = 1 --> i = N  [      i       i-1       M ticks/sec  ]
*
*                                                                [                                     ]
*                                                  Summation     [ (time  - time   )  *   1000 ms/sec  ]  modulo  (M ticks/sec)
*                                               i = 1 --> i = N  [      i       i-1                    ]
*                                           +  ---------------------------------------------------------------------------------
*
*                                                                                M ticks/sec
*
*
*                                   where
*                                           time        Instantaneous time value (in OS ticks/second)
*                                           M           Number of OS time ticks per second
*
*
*                       (1) However, these calculations are required only when the OS time ticks per
*                           second rate is not an integer multiple of the constant time scalar (i.e.
*                           1000 milliseconds per second).
*********************************************************************************************************
*/

#if (OS_VERSION >= 30000u)
#define  NET_BSP_TICK_RATE_HZ       OS_CFG_TICK_RATE_HZ
#else
#define  NET_BSP_TICK_RATE_HZ       OS_TICKS_PER_SEC
#endif


NET_TS_MS  NetUtil_TS_Get_ms (void)
{
#if (NET_BSP_TICK_RATE_HZ > 0u)
#if (!( (DEF_TIME_NBR_mS_PER_SEC >= NET_BSP_TICK_RATE_HZ) &&     \
       ((DEF_TIME_NBR_mS_PER_SEC %  NET_BSP_TICK_RATE_HZ) == 0u)))
    static  NET_TS_MS    ts_ms_delta_rem_tot = 0u;
            NET_TS_MS    ts_ms_delta_rem_ovf;
            NET_TS_MS    ts_ms_delta_rem;
            NET_TS_MS    ts_ms_delta_num;
#endif
            NET_TS_MS    ts_ms_delta;
    static  CPU_BOOLEAN  ts_active           = DEF_NO;
    static  CPU_INT32U   os_tick_prev        = 0u;
            CPU_INT32U   os_tick_delta;
#endif
            CPU_INT32U   os_tick_cur;
    static  NET_TS_MS    ts_ms_tot           = 0u;
#if (OS_VERSION >= 30000u)
            OS_ERR       os_err;
#endif

                                                                        /* Get cur OS time (in ticks).                  */
#if (OS_VERSION >= 30000u)
    os_tick_cur = (CPU_INT32U)OSTimeGet(&os_err);
   (void)&os_err;
#else
    os_tick_cur = (CPU_INT32U)OSTimeGet();
#endif

#if (NET_BSP_TICK_RATE_HZ > 0u)
    if (ts_active == DEF_YES) {                                         /* If active, calc & update ts :                */
        os_tick_delta        =  os_tick_cur - os_tick_prev;             /*     Calc time delta (in OS ticks).           */

#if ( (DEF_TIME_NBR_mS_PER_SEC >= NET_BSP_TICK_RATE_HZ) &&    \
     ((DEF_TIME_NBR_mS_PER_SEC %  NET_BSP_TICK_RATE_HZ) == 0u))
                                                                        /*     Calc   ts delta (in ms).                 */
        ts_ms_delta          = (NET_TS_MS)(os_tick_delta  * (DEF_TIME_NBR_mS_PER_SEC / NET_BSP_TICK_RATE_HZ));
        ts_ms_tot           += (NET_TS_MS) ts_ms_delta;                 /*     Update ts tot   (in ms) [see Note #2a].  */

#else
                                                                        /*     Calc   ts delta (in ms) [see Note #2a1]. */
        ts_ms_delta_num      = (NET_TS_MS)(os_tick_delta   * DEF_TIME_NBR_mS_PER_SEC);
        ts_ms_delta          = (NET_TS_MS)(ts_ms_delta_num / NET_BSP_TICK_RATE_HZ);
        ts_ms_tot           += (NET_TS_MS) ts_ms_delta;                 /*     Update ts tot   (in ms) [see Note #2a].  */
                                                                        /*     Calc   ts delta rem ovf (in ms) ...      */
        ts_ms_delta_rem      = (NET_TS_MS)(ts_ms_delta_num % NET_BSP_TICK_RATE_HZ);
        ts_ms_delta_rem_tot +=  ts_ms_delta_rem;
        ts_ms_delta_rem_ovf  =  ts_ms_delta_rem_tot / NET_BSP_TICK_RATE_HZ;
        ts_ms_delta_rem_tot -= (ts_ms_delta_rem_ovf * NET_BSP_TICK_RATE_HZ);
        ts_ms_tot           +=  ts_ms_delta_rem_ovf;                    /* ... & adj  ts tot by ovf    (see Note #2b).  */
#endif

    } else {
        ts_active = DEF_YES;
    }

    os_tick_prev  = os_tick_cur;                                        /* Save cur time for next ts update.            */

#else
    ts_ms_tot += (NET_TS_MS)os_tick_cur;
#endif


    return (ts_ms_tot);
}
#endif

/*
*********************************************************************************************************
*********************************************************************************************************
*                            TRANSMISSION CONTROL PROTOCOL LAYER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        NetTCP_InitTxSeqNbr()
*
* Description : Initialize the TCP Transmit Initial Sequence Counter, 'NetTCP_TxSeqNbrCtr'.
*
*               (1) Possible initialization methods include :
*
*                   (a) Time-based initialization is one preferred method since it more appropriately
*                       provides a pseudo-random initial sequence number.
*                   (b) Hardware-generated random number initialization is NOT a preferred method since it
*                       tends to produce a discrete set of pseudo-random initial sequence numbers--often
*                       the same initial sequence number.
*                   (c) Hard-coded initial sequence number is NOT a preferred method since it is NOT random.
*
*                   See also 'net_tcp.h  NET_TCP_TX_GET_SEQ_NBR()  Note #1'.
*
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : NetTCP_Init().
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

#ifdef  NET_TCP_MODULE_PRESENT
void  NetTCP_InitTxSeqNbr (void)
{
    /* $$$$ Insert code to initialize TCP Transmit Initial Sequence Counter (see Note #1).  */

    NetTCP_TxSeqNbrCtr = NET_TCP_SEQ_NBR_NONE;
}
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                               USER DATAGRAM PROTOCOL LAYER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      NetUDP_RxAppDataHandler()
*
* Description : Application-specific UDP connection handler function.
*
* Argument(s) : pbuf        Pointer to network buffer that received UDP datagram.
*               ----        Argument checked in NetUDP_Rx().
*
*               src_addr    Received UDP datagram's source      IP  address.
*
*               src_port    Received UDP datagram's source      UDP port.
*
*               dest_addr   Received UDP datagram's destination IP  address.
*
*               dest_port   Received UDP datagram's destination UDP port.
*
*               perr        Pointer to variable that will receive the return error code from this function
*                               (see Note #1b) :
*
*                               NET_APP_ERR_NONE                UDP datagram successfully received to application
*                                                                   connection(s).
*                               NET_ERR_RX                      Receive error; packet discarded.
*                               NET_ERR_RX_DEST                 Invalid destination; no application connection
*                                                                   available for received packet.
*
* Return(s)   : none.
*
* Caller(s)   : NetUDP_RxPktDemuxAppData().
*
* Note(s)     : (1) Application-specific UDP connection handler function is fully responsible for properly
*                   receiving, demultiplexing, & handling all UDP receive packets to the appropriate
*                   application connections.
*
*                   (a) (1) If the application-specific UDP connection handler function successfully
*                           demultiplexes UDP receive packets to an application connection, the handler
*                           function MUST at some point call NetUDP_RxAppData() to deframe the application
*                           data from the packet buffer(s) into an application array as well as copy any
*                           received IP options into an application IP options buffer.
*
*                           (A) The application-specific connection handler function may service the
*                               application data immediately within the handler function, in which case
*                               the application data SHOULD be serviced as quickly as possible since the
*                               network's global lock remains acquired for the full duration of the
*                               network receive.  Thus, no other network receives or transmits can occur
*                               while the application-specific handler function executes.
*
*                           (B) The application-specific connection handler function may delay servicing
*                               the application data by some other application-specific data servicing
*                               function(s), in which case the servicing function(s) MUST :
*
*                               (1) Acquire the network's global lock PRIOR to calling NetUDP_RxAppData()
*                               (2) Release the network's global lock AFTER    calling NetUDP_RxAppData()
*
*                               See 'net_udp.c  NetUDP_RxAppData()  Note #2'.
*
*                       (2) (A) (1) If NetUDP_RxAppDataHandler()          successfully demultiplexes the UDP
*                                   packets, it SHOULD eventually call NetUDP_RxAppData() to deframe the UDP
*                                   packet data.  If NetUDP_RxAppData() successfully deframes the UDP packet
*                                   application data :
*
*                                   (a) NetUDP_RxAppDataHandler() SHOULD return NET_APP_ERR_NONE, regardless
*                                       of whether the application handled the application data; ...
*                                   (b) but MUST NOT call NetUDP_RxPktFree() to free the UDP packet network
*                                       buffer(s) since NetUDP_RxAppData() frees the network buffer(s) [see
*                                       'NetUDP_RxAppData()  Note #1f'].
*
*                               (2) If NetUDP_RxAppDataHandler() does NOT successfully demultiplex   the UDP
*                                   packets :
*
*                                   (a) NetUDP_RxAppDataHandler() SHOULD return NET_ERR_RX_DEST, ...
*                                   (b) but must NOT free or discard the UDP packet network buffer(s) since
*                                       NetUDP_Rx() discards the network buffer(s).
*
*                               (3) If NetUDP_RxAppDataHandler() or NetUDP_RxAppData() fails for any other
*                                   reason(s) :
*
*                                   (a) NetUDP_RxAppDataHandler() SHOULD return NET_ERR_RX, ...
*                                   (b) but MUST call NetUDP_RxPktDiscard() to discard the UDP packet network
*                                       buffer(s).
*
*                           (B) FAILURE to appropriately call NetUDP_RxAppData() or NetUDP_RxPktDiscard() MAY
*                               result in lost network buffer(s).
*
*                   (b) Application-specific UDP connection handler function MUST return one of the following
*                       error codes ONLY [see 'Argument(s) : perr'] :
*
*                       (1) NET_APP_ERR_NONE  for     received UDP packets     destined to an available
*                               application connection & successfully deframed (see Note #1a2A1a)
*
*                       (2) NET_ERR_RX_DEST   for any received UDP packets NOT destined to an available
*                               application connection                         (see Note #1a2A2a)
*
*                       (3) NET_ERR_RX        for any other receive error      (see Note #1a2A3a)
*********************************************************************************************************
*/

#if ((NET_UDP_CFG_APP_API_SEL == NET_UDP_APP_API_SEL_APP     ) || \
     (NET_UDP_CFG_APP_API_SEL == NET_UDP_APP_API_SEL_SOCK_APP))
void  NetUDP_RxAppDataHandler (NET_BUF           *pbuf,
                               NET_IP_ADDR        src_addr,
                               NET_UDP_PORT_NBR   src_port,
                               NET_IP_ADDR        dest_addr,
                               NET_UDP_PORT_NBR   dest_port,
                               NET_ERR           *perr)
{
    /* $$$$ Insert code to demultiplex & handle UDP packets (see Note #1).  */

   *perr = NET_ERR_RX_DEST;
}
#endif

