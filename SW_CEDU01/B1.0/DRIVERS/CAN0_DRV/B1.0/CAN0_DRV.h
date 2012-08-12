//############################################################################//
// HEAD : (c) ARDIA 2010 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : CAN0_DRV 
//############################################################################//
// FILE : CAN0_DRV.H (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 11/10/10 |  SGHR  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//
#include "..\..\..\SYSTEME\REG\mb96346rs.h"
#include "..\..\..\DRIVERS\CAN0_DRV\B1.0\CAN0_DRV.cfg"


void vCAN0_iInitCAN0_Cmd(void);
void vCAN0_iBufferSetup_Cmd(void);
int iCAN0_iCAN0SendMessage_Cmd(unsigned char ucBuffer, unsigned long int uliID, unsigned char *ucBufPtr);