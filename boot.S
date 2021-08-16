# The Cortex M4
.cpu cortex-m4
.syntax unified
.thumb

.word   _estack  /* stack top address */
.word   _reset_     /* 1 Reset */
.word   sleep        /* 2 NMI */
.word   sleep        /* 3 Hard Fault */
.word   sleep        /* 4 MM Fault */
.word   sleep        /* 5 Bus Fault */
.word   sleep        /* 6 Usage Fault */
.word   sleep        /* 7 RESERVED */
.word   sleep        /* 8 RESERVED */
.word   sleep        /* 9 RESERVED*/
.word   sleep        /* 10 RESERVED */
.word   sleep        /* 11 SV call */
.word   sleep        /* 12 Debug reserved */
.word   sleep        /* 13 RESERVED */
.word   sleep        /* 14 PendSV */
.word   sleep        /* 15 SysTick */
.word   sleep        /* 16 IRQ0 */
.word   sleep        /* 17 IRQ1 */
.word   sleep        /* 18 IRQ2 */
.word   sleep        /* 19 ...   */
		            /* On to IRQ67 */

sleep:
    bkpt

.thumb_func
_reset_:
    bl main
    bkpt
