//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without
//                           the written consent of ARDIA is forbidden "
//        --------------------------------------------------------------------
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client
//        --------------------------------------------------------------------
//        --------------------------------------------------------------------
//        Module name : var
//############################################################################//
// FILE : NAR_VAR.H (SOURCE)
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

#define TEST_CAN_SEND

//****************************************************************************//
//  can 0: liste des variables globales
//****************************************************************************//


extern unsigned char CAN_Receive_Data[];
extern unsigned char CAN_Send_Data[];
extern unsigned char DataPos;
extern unsigned long CAN_Receive_ID, CAN_Send_ID;
extern unsigned char CAN_IRQ_selection_flag;
extern unsigned char CAN_buffer;
extern unsigned char ucFlag_CAN;
extern unsigned long ulBaudRate;
extern unsigned long CAN_MASK1;
extern unsigned long CAN_MASK2;
extern unsigned long CAN_MASK3;
extern unsigned long CAN_MASK4;

extern unsigned char  Can_Data_Buffer[];
