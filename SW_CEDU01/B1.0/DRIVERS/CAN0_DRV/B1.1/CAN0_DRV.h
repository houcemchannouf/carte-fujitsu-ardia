//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without
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
//         01.10  | 15/08/12 |SBK & IH| Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//
#include "..\..\..\SYSTEME\REG\mb96348rs.h"
#include "..\..\..\DRIVERS\CAN0_DRV\B1.1\CAN0_DRV.cfg"

#define HEX      0
#define DEC      1
#define CAN_TIMEOUT 0xFFFF    // simple timeout value, if CAN-data can not be send


int  CAN0_GetRxBuffer(void);
void CAN0_init (unsigned long ulBaudRate, unsigned char ucFlag_CAN)int CAN0_ReadMessage(unsigned char buffer, unsigned long *id, unsigned char *memory);
int CAN0_SendMessage(unsigned char buffer, unsigned long id, unsigned char *memory);
void CAN0_SetRxBuffer(unsigned char buffer, unsigned long id, unsigned char irq, unsigned long mask);
void vCAN0_ReceiveInterrupt_ISRr(void);
void vCAN0_TEST_EXE(void);
