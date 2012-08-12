//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : UART0_DRV 
//############################################################################//
// FILE : UART0_DRV.c (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author            | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 05/08/12 |  Ghariani Ahmed   | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//

#include "..\SW_CEDU01\B1.0\UART0_DRVV\UART0_DRV.h"

void vUART0_iInitUART(void)
{
  r16BGR = 207;                   //15;       // 1M Bit/s @ 16 MHz
  PIER08_IE2=1;           //enable SIN0
  //SCR0
  iTrans  = 1;            // Enable tansmission
  iRecep  = 1;            // Enable Reception
  iClearFlag = 1;         // Clear all flags error 
  iDataForm  = 0;         // Data format : Data bit 
  iDataLength = 1;        // Data Length : 7 bit
  iLengthStop = 0;        // Length of the stop bit : 1
  iEnableParity = 0;      // Disable Parity
  //SMR0
  iReset=1;
  iClear=1;
  iEnableOutPutPin =1;
  //SCR
  rSSR0=0x00;
  
  
  
}

unsigned char u8UART0_eRead_Data(void)
{
  unsigned char din;
  
 while(1) {
  while (iRecDataFlag == 0){     
  __wait_nop();             // Reception data register is full ?
  } 
  
  din = rRDR0;             // flush reception register
  if(iframeError||iOverrunError||iParityError)   
  iClearFlag = 1;          // Clear possible errors, reset reception state machine
	else
  return din;
  }
}

void vUART0_eWrite_Data(unsigned char u8Data) 
{		
 
  while (itrDataFlag == 0);   // Transmission data register is full ?
  rTDR0 = u8Data;             // Write data in transmission register
}



