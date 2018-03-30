/*
***********************************************************************************************
* INCLUDE FILES
***********************************************************************************************
*/
#include <app_cfg.h> 
#include <bsp_os.h>
#include <os.h>
/*
***********************************************************************************************
* LOCAL GLOBAL VARIABLES
***********************************************************************************************
*/

#define APP_TASK_START_STK_SIZE 50;

static OS_TCB AppTaskStartTCB; 
static CPU_STK AppTaskStartStk[APP_TASK_START_STK_SIZE]; 
/*
***********************************************************************************************
* FUNCTION PROTOTYPES
***********************************************************************************************
*/
static void AppTaskStart (void *p_arg);

void main (void)
{
  OS_ERR err;
  BSP_IntDisAll(); 
  OSInit(&err); 
  if (err != OS_ERR_NONE) {
    /* Something didn’t get initialized correctly ... */
    /* ... check os.h for the meaning of the error code, see OS_ERR_xxxx */
  }
  OSTaskCreate((OS_TCB *)&AppTaskStartTCB, 
    (CPU_CHAR *)”App Task Start”, 
    (OS_TASK_PTR )AppTaskStart, 
    (void *)0, 
    (OS_PRIO )APP_TASK_START_PRIO, 
    (CPU_STK *)&AppTaskStartStk[0], 
    (CPU_STK_SIZE)APP_TASK_START_STK_SIZE / 10, 
    (CPU_STK_SIZE)APP_TASK_START_STK_SIZE, 
    (OS_MSG_QTY )0,
    (OS_TICK )0,
    (void *)0,
    (OS_OPT )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), (
    (OS_ERR *)&err); 
  if (err != OS_ERR_NONE) {
    /* The task didn’t get created. Lookup the value of the error code ... */
    /* ... in os.h for the meaning of the error */
  }
  OSStart(&err); 
  if (err != OS_ERR_NONE) {
    /* Your code is NEVER supposed to come back to this point. */
  }
}

static void AppTaskStart (void *p_arg) 
{
  OS_ERR err;
  p_arg = p_arg;
  BSP_Init(); //init hardware on board. GPIO functionality found in bsp.c
  CPU_Init(); //init OS services e.g. measure interrupt latency, obtain time stamps, etc.
  BSP_OS_TickInit();  //set OS tick interrupt
  BSP_LED_Off(0); //will turn off all LEDs. Arg 0 means all LEDs
  while (1) { 
    BSP_LED_Toggle(0); 
    OSTimeDlyHMSM((CPU_INT16U) 0, 
      (CPU_INT16U) 0,
      (CPU_INT16U) 0,
      (CPU_INT32U)100,
      (OS_OPT )OS_OPT_TIME_HMSM_STRICT,
      (OS_ERR *)&err);
    /* Check for ‘err’ */
  }
}

void MyTask (void *p_arg)
{
/* Do something with “p_arg”.
while (1) {
/* Task body */
}

