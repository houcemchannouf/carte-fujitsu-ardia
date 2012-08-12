//############################################################################//
// HEAD : (c) ARDIA 2010 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : CAN0_DRV 
//############################################################################//
// FILE : CAN0_DRV.C (SOURCE)
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


#include "..\..\..\DRIVERS\CAN0_DRV\B1.0\CAN0_DRV.h"

#define DulTIMEOUT  0xFFFF

//============================================================================
// NAME : vCAN0_iInitCAN0_Cmd
//============================================================================
// ROLE : Initialiser Can0
//----------------------------------------------------------------------------
// INPUT  :  void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author | Description                           
//        --------------------------------------------------------------------
//         01.00  | 11/10/10 |  SGHR  | Creation of this function              
//============================================================================

void vCAN0_iInitCAN0_Cmd(void)
{
  DbCAN0_iEnableOutputR = 1;                           // enable CAN0 output
  DbCAN0_iEnableInputR  = 1;                           // enable CAN0 input
  DbCAN0_iContolRInit   = 1;                           // Stop CAN Operation

  // Setup CAN channel Configuration
  DbCAN0_iContolRConfChange = 1;                      // Enable Configuration Change
  DulCAN0_iBitTim           = DulBTR_8M_250k_16_68_3; // <<< set bit timing
  DbCAN0_iContolRConfChange  = 0;                     // Disable Configuration Change
  DbCAN0_iContolRInit = 0;                            // Start CAN Operation
}


//============================================================================
// NAME : vCAN0_iBufferSetup_Cmd
//============================================================================
// ROLE : Initialiser le buffer de la can0 en mode STD
//----------------------------------------------------------------------------
// INPUT  :  void
//----------------------------------------------------------------------------
// OUTPUT : void
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author | Description                           
//        --------------------------------------------------------------------
//         01.00  | 11/10/10 |  SGHR  | Creation of this function              
//============================================================================

void vCAN0_iBufferSetup_Cmd(void)
{
  // CAN0: messagebuffer 1 will be used as receive-buffer

  // Prepare Arbitration Interface Register
  DulCAN0_iArbitrationR1    = MSG2STD(0x2L);    // <<< Define message id: Use MSG2STD() for 11bit IDs / Use MSG2EXT() for 29bit IDs
  DbCAN0_iArbitrationXTD    = 0;                // <<< 0: 11bit ID / 1: 29bit ID 
  DbCAN0_iArbitrationDIR    = 0;                // <<< 0: RX Buffer / 1: TX Buffer 
  DbCAN0_iArbitrationMSGVAL = 1;                // <<< 0: Buffer invalid / 1: Buffer valid 

  // Prepare Mask Interface Register 
  DulCAN0_iMask1R     = 0x00000000;      // <<< Setup Mask corresponding to your application 
  DbCAN0_iMask2Filter = 0;               // <<< 0: ID type is not used for filtering / 1: ... is used for filtering 
  
  // Prepare Message Control Interface Register 
  DbCAN0_iMctr0FNewDat   = 0;       // Clear NEWDAT Flag 
  DbCAN0_iMctr0F1MsgLst  = 0;       // Clear MSGLST Flag 
  DbCAN0_iMctr0FIntPnd   = 0;       // Clear INTPND Flag 
  DbCAN0_iMctr0FiltMask  = 0;       // <<< 0: Not use Filter mask (Full CAN Object) / 1: Use Filter Mask 
  DbCAN0_iMctr0TXInt     = 0;       // <<< 0: Disable Tx-Interrupt / 1: Enable Tx-Interrupt 
  DbCAN0_iMctr0RXInt     = 0;       // <<< 0: Disable Rx-Interrupt / 1: Enable Rx-Interrupt 
  DbCAN0_iMctr0Remote    = 0;       // <<< 0: Disable Remote / 1: Enable Remote 
  DbCAN0_iMctr0TXRQST    = 0;       // Clear Transmission Request 
  DbCAN0_iMctr0EOB       = 1;       // <<< 0: Buffer is part of FiFo / 1: Single message buffer  
  
  DucCAN0_iCommMask1R = 0xF0; // Prepare Interface Command Mask Register: 
                              // WRRD    = 1 : Write information from interface to object
                              // MASK    = 1 : Write Mask register
                              // ARB     = 1 : Write Arbitration Register (ID Register)
                              // CONTROL = 1 : Write object control register (e.g. Data length, IRQ enable, etc)
                              // CIP     = 0 : (dont care for writing to object)
                              // TXREQ   = 0 : No Transmission Request
                              // DATAA   = 0 : Do not change Data A register
                              // DATAB   = 0 : Do not change Data B register
                              
                  

  DucCAN0_iCommRequest1R = 1;               // Transfer the Interface Register Content to the Message Buffer
  
}

//============================================================================
// NAME : iCAN0_iCAN0SendMessage_Cmd
//============================================================================
// ROLE : Envoyer un message sur le bus.
//----------------------------------------------------------------------------
// INPUT  :  unsigned char ucBuffer : Selectonner le messagebuffer.
//           unsigned long int uliID: Definir l'identifiant ID.
//           unsigned char *ucBufPtr: L'adresse du data à envoyé.
//----------------------------------------------------------------------------
// OUTPUT : int  :retourne  '1' si envoyé et '0' si échec
//----------------------------------------------------------------------------
// RESOURCES :
//----------------------------------------------------------------------------
// HIST : Version |   Date   | Author | Description                           
//        --------------------------------------------------------------------
//         01.00  | 11/10/10 |  SGHR  | Creation of this function              
//============================================================================




int iCAN0_iCAN0SendMessage_Cmd(unsigned char ucBuffer, unsigned long int uliID, unsigned char *ucBufPtr)
{
  unsigned long int ultimeout = 0;
  unsigned char ucLen;
  
  // Prepare Arbitration Interface Register 
  DulCAN0_iArbitrationR1 = MSG2STD(uliID);    // <<< MSG2STD: 11bit ID / MSG2EXT: 29bit ID 
  DbCAN0_iArbitrationXTD    = 0;              // <<< 0: 11bit ID / 1: 29bit ID 
  DbCAN0_iArbitrationDIR    = 1;              // <<< 0: RX Buffer / 1: TX Buffer 
  DbCAN0_iArbitrationMSGVAL = 1;              // <<< 0: Buffer invalid / 1: Buffer valid 
  
  // Prepare Mask Interface Register 
  DulCAN0_iMask1R       = 0x00000000;     // <<< Setup Mask corresponding to your application 
  DbCAN0_iMask2Filter   = 1;              // <<< 0: ID type is not used for filtering / 1: ... is used for filtering 
  
  // Prepare Message Control Interface Register 
  DbCAN0_iMctr0FNewDat  = 0;             // Clear NewDat Flag 
  DbCAN0_iMctr0F1MsgLst = 0;             // Clear MsgLst Flag 
  DbCAN0_iMctr0FIntPnd  = 0;             // Clear IntPnd Flag 
  DbCAN0_iMctr0FiltMask = 0;             // <<< 0: Not use Filter Mask (Full CAN Object)/ 1: Use Filter Mask 
  DbCAN0_iMctr0TXInt    = 0;             // <<< 0: Disable Tx-Interrupt / 1: enable Tx-Interrupt 
  DbCAN0_iMctr0RXInt    = 0;             // <<< 0: Disable Rx-Interrupt / 1: enable Rx-Interrupt 
  DbCAN0_iMctr0Remote   = 0;             // <<< 0: Disable Remote / 1: enable Remote 
  DbCAN0_iMctr0TXRQST   = 0;             // Don't set Transmission Request here 
  DbCAN0_iMctr0EOB      = 1;             // <<< 0: Buffer is part of FiFo / 1: Single message buffer   
  DucCAN0_iMctr0DatNumb1 = ucLen = *ucBufPtr++;  // Set number of Data to be transmitted 
  
  // Set Data 
  DulCAN0_iDataLow1   = *((unsigned long *)ucBufPtr);
  DulCAN0_iDataHight1 = *((unsigned long *)(ucBufPtr+4));
  
  DucCAN0_iCommMask1R  = 0xF7;           // Prepare Interface Command Mask Register: 
                              // WRRD    = 1 : Write information from interface to object
                              // MASK    = 1 : Write Mask register
                              // ARB     = 1 : Write Arbitration Register (ID Register)
                              // CONTROL = 1 : Write object control register (e.g. Data length, IRQ enable, etc)
                              // CIP     = 0 : (dont care for writing to object)
                              // TXREQ   = 1 : Set Transmission Request
                              // DATAA   = 1 : Write Data A register
                              // DATAB   = 1 : Write Data B register

  DucCAN0_iCommRequest1R = ucBuffer;  // Transfer the Interface Register Content to the Message Buffer 

  // Wait for transmission of message
  //Si l'envoi sur le bus se fait une seule fois par unité de temp alors on peut éliminer cette boucle
  while(    (DbCAN0_iTransRequestR& (0x1 << (ucBuffer -1)) != 0) 
         && (ultimeout++ < DulTIMEOUT) 
         && (DbCAN0_iContolRInit != 1)
       )
  {
    __wait_nop();
 }
  
    
  if( (ultimeout == DulTIMEOUT) || (DbCAN0_iContolRInit == 1) )
  {
    // Cancel transmission request 
    DucCAN0_iCommMask1R  = 0x10;         // Prepare Interface Command Mask Register: Load only control data from message object
                              // WRRD    = 0 : Write information from interface to object
                              // MASK    = 0 : Write Mask register
                              // ARB     = 0 : Write Arbitration Register (ID Register)
                              // CONTROL = 1 : Write object control register (e.g. Data length, IRQ enable, etc)
                              // CIP     = 0 : (dont care for writing to object)
                              // TXREQ   = 0 : Set Transmission Request
                              // DATAA   = 0 : Write Data A register
                              // DATAB   = 0 : Do not write Data B register
  
    DucCAN0_iCommRequest1R = ucBuffer;        // Transfer the Interface Register Content to the Message Buffer 
    DbCAN0_iMctr0TXRQST    = 0;               // Clear Transmission Request 
    DbCAN0_iCommMask1WRRD  = 1;               // Prepare Interface Command Mask Register
    DucCAN0_iCommRequest1R = ucBuffer;        // Transfer the Interface Register Content to the Message Buffer
   
    return 0;                 // return error
  }
  
  return 1;                   // return ok 
}


