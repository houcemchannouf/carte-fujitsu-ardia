//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without
//                           the written consent of ARDIA is forbidden "
//        --------------------------------------------------------------------
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client
//        --------------------------------------------------------------------
//        --------------------------------------------------------------------
//        Module name : near_var
//############################################################################//
// FILE : NAR_VAR.C (SOURCE)
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
//****************************************************************************//
//  can 0: liste des variables globales
//****************************************************************************//


unsigned char CAN_Receive_Data[9];
unsigned char CAN_Send_Data[9];
unsigned char DataPos;
unsigned long CAN_Receive_ID, CAN_Send_ID;
unsigned char CAN_IRQ_selection_flag;
unsigned char CAN_buffer;
unsigned char ucFlag_CAN=0;
unsigned long CAN_MASK1;
unsigned long CAN_MASK2;
unsigned long CAN_MASK3;
unsigned long CAN_MASK4;
unsigned long ulBaudeRate;


unsigned char  Can_Data_Buffer[10]; //TEST CAN
