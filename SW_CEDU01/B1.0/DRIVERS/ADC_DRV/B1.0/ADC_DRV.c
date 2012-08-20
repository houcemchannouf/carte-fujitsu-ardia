//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : ADC_DRV  
//############################################################################//
// FILE : ADC_DRV.C (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   |   Author         | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 20/08/12|  Ghariani Ahmed  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//


#include "../Drivers/ADC_DRV/ADC_DRV.h"

unsigned int rslt;

void InitADC (void)
{
  rADCS = 0xA0C0;   // stop mode, 10 bit
  rADSR = 0x9000;   // 24 cy. sampling; 88 cy. conversion; channel 0
  rADER0 = 0x01;    // enable analog port pin AN0 function 
}

void vIrq_ADC(void)
{
  
  rslt = rADCR& 0x03ff; //// read 10-bit result
  rADCS = 0xA0; // clear INT-Flag
  
}
