//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : UART0_DRV_INT
//############################################################################//
// FILE : UART0_DRV_INT.c (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author            | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 06/08/12 |  Ghariani Ahmed   | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//

#include "..\SW_CEDU01\B1.0\UART0_DRV_INT\UART0_DRV_INT.h"
#define MAX 100;

unsigned char RXbuf[MAX];   // Reception Buffer
unsigned char TXbuf[MAX];   // Transmission Buffer
unsigned char RXptr = 0;       // Reception Buffer Pointer
unsigned char TXptr = 0;       // Transmission Buffer Pointer

void vUART0_iInitUART(void)
{
  PIER08_IE2 = 1; // Enable SIN0 Port Pin
  rBGR = 1249;   // 19200 Baud @ 24MHz
  rSSR = 0x00;   // LSB first
  rSMR = 0x0d;   // enable SOT0, reset, Asynchronous normal mode 0
  rSCR = 0x17;   // 8 Data bits ,1 stop bit, clear possible errors, enable RX, TX
   
}

// Reception Interrupt
void RX_UART0(void)
{
if (iframeError & iOverrunError & iParityError) // Check for errors PE, ORE, FRE
{
 iClearFlag = 1;          // Clear error flags
}
if (RXptr < MAX) {     //  if End of Buffer not reached
 Rxbuf[RXptr] = rRDR0;  // Fill Reception Buffer
 RXptr++;              
 }
}

// Transmission Interrupt
void TX_UART0(void)
{
rTDR0 = TXbuf[TXptr]; // Send Buffer Data
TXptr++;             // Update Buffer Pointer
if (TXptr == MAX)    // End of Buffer reached
{
  iEnableTrInt = 0;        // Disable Transmission Interrupt
}
}

  // Main Function
void Main(void){

 InitIrqLevels();

 __set_il(7);     // allow all levels
 __EI();          // enable all interrupts

// Initial Configuration
vUART0_iInitUART();    // Update UART0

//Enable Interrupts
 iEnableTrInt = 1;  // Enable Transmission interrupt
 iEnableRecInt = 1; // Enable reception interrupt

 while(1){
 __wait_nop(); // nothing to do, everything is done by interrupts
 }
}

