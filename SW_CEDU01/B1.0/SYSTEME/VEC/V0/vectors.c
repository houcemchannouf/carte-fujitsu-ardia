/************************************************************************/
/*               (C) Fujitsu Microelectronics Europe GmbH               */
/*                                                                      */
/* The following software deliverable is intended for and must only be  */
/* used in an evaluation laboratory environment.                        */
/* It is provided without charge and therefore provided on an as-is     */
/* basis, subject to alterations.                                       */
/*                                                                      */
/* The software deliverable is to be used exclusively in connection     */
/* with FME products.                                                   */
/* In the event the software deliverable includes the use of open       */
/* source components, the provisions of the governing open source       */
/* license agreement shall apply with respect to such software          */
/* deliverable.                                                         */
/* FME does not warrant that the deliverables do not infringe any       */
/* third party intellectual property right (IPR). In the event that     */
/* the deliverables infringe a third party IPR it is the sole           */
/* responsibility of the customer to obtain necessary licenses to       */
/* continue the usage of the deliverable.                               */
/*                                                                      */
/* To the maximum extent permitted by applicable law FME disclaims all  */
/* warranties, whether express or implied, in particular, but not       */
/* limited to, warranties of merchantability and fitness for a          */
/* particular purpose for which the deliverable is not designated.      */
/*                                                                      */
/* To the maximum extent permitted by applicable law, FME's liability   */
/* is restricted to intention and gross negligence.                     */
/* FME is not liable for consequential damages.                         */
/*                                                                      */
/* (V1.2)                                                               */
/************************************************************************/

/* -------------------------------------------------------------------------
  VECTORS.C
  - Interrupt level (priority) setting
  - Interrupt vector definition
-----------------------------------------------------------------------------*/

#include "..\..\Systeme\Reg\mb96348rs.h"
#include "..\..\DRIVERS\LCD_DRV\B1.0\LCD_DRV.h"
#include "..\..\DRIVERS\CLV_DRV\B1.0\CLV_DRV.h"
#include "..\..\DRIVERS\AS0_DRV\B1.0\AS0_DRV.h"
#include "..\..\DRIVERS\CAN0_DRV\B1.0\CAN0_DRV.h" 

/*---------------------------------------------------------------------------
   InitIrqLevels()
   This function  pre-sets all interrupt control registers. It can be used
   to set all interrupt priorities in static applications. If this file
   contains assignments to dedicated resources, verify  that the
   appropriate controller is used.
   NOTE: value 7 disables the interrupt and value 0 sets highest priority.
-----------------------------------------------------------------------------*/

#define MIN_ICR  12
#define MAX_ICR  96

#define DEFAULT_ILM_MASK 7

void InitIrqLevels(void)
{
  volatile int irq;
  
  for (irq = MIN_ICR; irq <= MAX_ICR; irq++) 
  {
    ICR = (irq << 8) | DEFAULT_ILM_MASK;
  }
  
  ICR = (17 << 8) | 6;  // External Interrupt 0
  ICR = (18 << 8) | 6;  // External Interrupt 1  
  ICR = (19 << 8) | 6;  // External Interrupt 2
  ICR = (20 << 8) | 6;  // External Interrupt 3 
  ICR = (79 << 8) | 6;  // uart0 rx 
  ICR = (80 << 8) | 6;  // uart 0 tx 
  ICR = (33 << 8) | 5;  // CAN0

}

/*---------------------------------------------------------------------------
   Prototypes
   Add your own prototypes here. Each vector definition needs is proto-
   type. Either do it here or include a header file containing them.
-----------------------------------------------------------------------------*/

__interrupt void DefaultIRQHandler (void);
__interrupt void IRQHandler_EI0 (void);


/*---------------------------------------------------------------------------
   Vector definiton for MB9634x
   Use following statements to define vectors. All resource related
   vectors are predefined. Remaining software interrupts can be added here
   as well.
   NOTE: If software interrupts 0 to 7 are defined here, this might 
   conflict with the reset vector in the start-up file.
-----------------------------------------------------------------------------*/

#pragma intvect DefaultIRQHandler   11   /* Non-maskable Interrupt       */
#pragma intvect DefaultIRQHandler   12   /* Delayed Interrupt            */
#pragma intvect DefaultIRQHandler   13   /* RC Timer                     */
#pragma intvect DefaultIRQHandler   14   /* Main Clock Timer             */
#pragma intvect DefaultIRQHandler   15   /* Sub Clock Timer              */
#pragma intvect DefaultIRQHandler   16   /* Reserved                     */
#pragma intvect vVec_eEXT0_Isr      17   /* EXT0                         */
#pragma intvect vVec_eEXT1_Isr          18   /* EXT1                         */
#pragma intvect vVec_eEXT2_Isr          19   /* EXT2                         */
#pragma intvect vVec_eEXT3_Isr          20   /* EXT3                         */
#pragma intvect DefaultIRQHandler   21   /* EXT4                         */
#pragma intvect DefaultIRQHandler   22   /* EXT5                         */
#pragma intvect DefaultIRQHandler   23   /* EXT6                         */
#pragma intvect DefaultIRQHandler   24   /* EXT7                         */
#pragma intvect DefaultIRQHandler   25   /* EXT8                         */
#pragma intvect DefaultIRQHandler   26   /* EXT9                         */
#pragma intvect DefaultIRQHandler   27   /* EXT10                        */
#pragma intvect DefaultIRQHandler   28   /* EXT11                        */
#pragma intvect DefaultIRQHandler   29   /* EXT12                        */
#pragma intvect DefaultIRQHandler   30   /* EXT13                        */
#pragma intvect DefaultIRQHandler   31   /* EXT14                        */
#pragma intvect DefaultIRQHandler   32   /* EXT15                        */
#pragma intvect vVec_eCAN0RX_Isr    33   /* CAN0                         */
#pragma intvect DefaultIRQHandler   34   /* CAN1                         */
#pragma intvect DefaultIRQHandler   35   /* PPG0                         */
#pragma intvect DefaultIRQHandler   36   /* PPG1                         */
#pragma intvect DefaultIRQHandler   37   /* PPG2                         */
#pragma intvect DefaultIRQHandler   38   /* PPG3                         */
#pragma intvect DefaultIRQHandler   39   /* PPG4                         */
#pragma intvect DefaultIRQHandler   40   /* PPG5                         */
#pragma intvect DefaultIRQHandler   41   /* PPG6                         */
#pragma intvect DefaultIRQHandler   42   /* PPG7                         */
#pragma intvect DefaultIRQHandler   43   /* PPG8                         */
#pragma intvect DefaultIRQHandler   44   /* PPG9                         */
#pragma intvect DefaultIRQHandler   45   /* PPG10                        */
#pragma intvect DefaultIRQHandler   46   /* PPG11                        */
#pragma intvect DefaultIRQHandler   47   /* PPG12                        */
#pragma intvect DefaultIRQHandler   48   /* PPG13                        */
#pragma intvect DefaultIRQHandler   49   /* PPG14                        */
#pragma intvect DefaultIRQHandler   50   /* PPG15                        */
#pragma intvect DefaultIRQHandler   51   /* RLT0                         */
#pragma intvect DefaultIRQHandler   52   /* RLT1                         */
#pragma intvect DefaultIRQHandler   53   /* RLT2                         */
#pragma intvect DefaultIRQHandler   54   /* RLT3                         */
#pragma intvect DefaultIRQHandler   55   /* PPGRLT - RLT6                */
#pragma intvect DefaultIRQHandler   56   /* ICU0                         */
#pragma intvect DefaultIRQHandler   57   /* ICU1                         */
#pragma intvect DefaultIRQHandler   58   /* ICU2                         */
#pragma intvect DefaultIRQHandler   59   /* ICU3                         */
#pragma intvect DefaultIRQHandler   60   /* ICU4                         */
#pragma intvect DefaultIRQHandler   61   /* ICU5                         */
#pragma intvect DefaultIRQHandler   62   /* ICU6                         */
#pragma intvect DefaultIRQHandler   63   /* ICU7                         */
#pragma intvect DefaultIRQHandler   64   /* OCU0                         */
#pragma intvect DefaultIRQHandler   65   /* OCU1                         */
#pragma intvect DefaultIRQHandler   66   /* OCU2                         */
#pragma intvect DefaultIRQHandler   67   /* OCU3                         */
#pragma intvect DefaultIRQHandler   68   /* OCU4                         */
#pragma intvect DefaultIRQHandler   69   /* OCU5                         */
#pragma intvect DefaultIRQHandler   70   /* OCU6                         */
#pragma intvect DefaultIRQHandler   71   /* OCU7                         */
#pragma intvect DefaultIRQHandler   72   /* FRT0                         */
#pragma intvect DefaultIRQHandler   73   /* FRT1                         */
#pragma intvect DefaultIRQHandler   74   /* I2C0                         */
#pragma intvect DefaultIRQHandler   75   /* I2C1                         */
#pragma intvect DefaultIRQHandler   76   /* ADC                          */
#pragma intvect DefaultIRQHandler   77   /* ALARM0                       */
#pragma intvect DefaultIRQHandler   78   /* ALARM1                       */
#pragma intvect vVec_eUSART0_RX_Isr 79   /* LIN-UART 0 RX                */ 
#pragma intvect vVec_eUSART0_TX_Isr 80   /* LIN-UART 0 TX                */ 
#pragma intvect DefaultIRQHandler   81   /* LIN-UART 1 RX                */
#pragma intvect DefaultIRQHandler   82   /* LIN-UART 1 TX                */
#pragma intvect DefaultIRQHandler   83   /* LIN-UART 2 RX                */
#pragma intvect DefaultIRQHandler   84   /* LIN-UART 2 TX                */
#pragma intvect DefaultIRQHandler   85   /* LIN-UART 3 RX                */
#pragma intvect DefaultIRQHandler   86   /* LIN-UART 3 TX                */
#pragma intvect DefaultIRQHandler   87   /* MAIN FLASH IRQ               */
#pragma intvect DefaultIRQHandler   88   /* SATELLITE FLASH IRQ (not on all devices) */
#pragma intvect DefaultIRQHandler   89   /* LIN-UART 7 RX (not on all devices) */
#pragma intvect DefaultIRQHandler   90   /* LIN-UART 7 TX (not on all devices) */
#pragma intvect DefaultIRQHandler   91   /* LIN-UART 8 RX (not on all devices) */
#pragma intvect DefaultIRQHandler   92   /* LIN-UART 8 TX (not on all devices) */
#pragma intvect DefaultIRQHandler   93   /* LIN-UART 9 RX (not on all devices) */
#pragma intvect DefaultIRQHandler   94   /* LIN-UART 9 TX (not on all devices) */
#pragma intvect DefaultIRQHandler   95   /* RTC (not on all devices)     */
#pragma intvect DefaultIRQHandler   96   /* CAL (not on all devices)     */

/*---------------------------------------------------------------------------
   DefaultIRQHandler()
   This function is a placeholder for all vector definitions. Either use
   your own placeholder or add necessary code here. 
-----------------------------------------------------------------------------*/

__interrupt  void DefaultIRQHandler (void)
{
    __DI();                              /* disable interrupts */
    while(1)
    {
        __wait_nop();                    /* halt system */
    }
}



__interrupt  void vVec_eEXT0_Isr (void)
{

        vCLV_eSW2_Isr();
}

__interrupt  void vVec_eEXT1_Isr (void)
{

                vCLV_eSW3_Isr();
}

__interrupt  void vVec_eEXT2_Isr (void)
{

                vCLV_eSW4_Isr();
}

__interrupt  void vVec_eEXT3_Isr (void)
{

                vCLV_eSW5_Isr();
}
__interrupt void vVec_eUSART0_RX_Isr(void)// Reception Interrupt Service
{

    
// Receive function 
vAS0_ReceiveInterrupt_ISRr();


}

__interrupt void vVec_eUSART0_TX_Isr(void) // Transmission Interrupt Service
{   

// Transmit function
 vAS0_TransmitInterrupt_ISRr ();
                                        
   
}


__interrupt void vVec_eCAN0RX_Isr(void) // CAN0 receive interrupt
{   

// CAN0 receive interrupt
vCAN0_ReceiveInterrupt_ISRr();
                                        
   
}
