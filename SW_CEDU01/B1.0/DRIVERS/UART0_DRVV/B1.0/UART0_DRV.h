//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : UART0_DRV 
//############################################################################//
// FILE : UART0_DRV.h (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author            | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 29/07/12 |  Ghariani Ahmed   | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//
#include "..\Drivers\mb96348rs.h"
#include "..\Drivers\UART_0\UART0_DRV.cfg"


void vUART0_iInitUART(void);
unsigned char u8UART0_eRead_Data(void);
void vUART0_eWrite_Data(unsigned char u8Data);


