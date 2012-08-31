//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
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
//         01.10  | 15/08/12 |SBK & IH| Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//

#include "..\..\..\DRIVERS\CAN0_DRV\B1.1\CAN0_DRV.h"
#include "..\..\..\DRIVERS\CAN0_DRV\B1.1\CAN0_DRV.cfg"
#include "..\..\..\MANAGEMENT\MNG\mng.h"
#include "..\..\..\systeme\variables\var.h"

//Fonction d'initialisation:
//====================================================================
//1_Set CAN Control Register => CTRLR0_INIT = 1
//			   
//			   <====> No msg transfer (No R, No T)
//
//				+ Status of CAN_TX is recessive (H)
//
//2_Set INIT && CCE => CTRLR0_CCE=1
//		  
//		  <=> BTR0 could be setted
//
//NB: * no Message object needed => MSGVAL = 0
//
//and after (*) => ** BSP is the responsible for msg transfer	
//====================================================================
  void CAN0_init (unsigned long ulBaudRate, unsigned char ucFlag_CAN)
{
	/*Configuration des pins*/

// if ucFlag_CAN==1 => Standard sinn Extended
	
if (ucFlag_CAN==1)  
	PDR10 = 0x00;     // initialization of port data register with standard frame
else
	PDR10= 0x01; 	// ................................... with Extended Frame
	
	PIER10= 0x01;
	COER0_OE= 1 ; 	 //CAN TX is enabled
	PIER10_IEO= 1;	 // CAN RX is enabled
	
	/*setup CAN channel configuration*/ 
	CTRLR0_INIT = 1; // <=> CTRLR0= 0x0001 *Initialization is started*

	CTRLR0_CCE= 1;   //The CPU has write access to the Bit Timing Register (while Init = "1")
	
	CTRLR0_IE= 1;    //Enabled - Interrupts will be generated. The request remains active until 
			 // all pending interrupts are processed.

	BTR0_BRP= ulBaudrate; //Baud Rate Prescaler

	/*Activation of CAN operation*/

	CTRLR0_CCE=0;	//The CPU has no write access to the Bit Timing Register.

	CTRLR0_INIT=0;  //Initialization fullfiled && return to Normal Operation 

}

// Fonction Test de l'initialisation
// the test will be done by using one value for ulBaudRate and we have chosen 0x2B01

void vCAN0_eInitSendTest_Exe(void)
{
if (ucFlag_CAN==1)  

	PDR10 = 0x00;     // initialization of port data register with standard frame
  
else
	PDR10= 0x01;      // ................................... with Extended Frame

  
  PIER10 = 0x01;    // enable CAN0 input (activation of the port PIER10)   
	
  COER0_OE = 1;         // enable CAN0 output

  PIER10_IE0 = 1;       // enable CAN0 input (activate the first bit of PIER10:PIER10_IE0)

  CTRLR0_INIT = 1;      // Stop CAN Operation

//setup CAN channel configuration 

  CTRLR0_CCE  = 1;                  // Enable Configuration Change

  CTRLR0_IE   = 1;                  // 0: Disable / 1: Enable Module Interrupt

  BTR0 = 0x2B01  ;  	            // set bit timing e.g "DulBTR_8M_250k_16_68_3"

  CTRLR0_CCE  = 0;                  // Disable Configuration Change

  CTRLR0_INIT = 0;                  // Start CAN Operation
}

// Fonction SetRxBuffer   HWM 622
//
//
/*1_ preparer l'arbitrage de l'inteface registre  (623 HWM)
   ********************************************************
	* ça revient à definir l'ID et le type du message reçu
	
	NB: Msg STD => 11 bit & (ID28 _ ID18)
	
	#define MSG2STD(msg) ((msg & 0x000007FFL) << 18) only ID18_ID28 are set to 1, ID0_ID17 are reset to 0

	ucFlag_CAN: near_var=>  unsigned char ucFlag_CAN=0; 68
		 
		 mng.c => if(ucAS0_RXbuf[4]==0x00)   //unsigned char ucAS0_RXbuf[200]; // Reception Buffer in near_var
 				{
  				ucFlag_CAN=1;
 				
 				}
 
	     Else ID28_ ID0 all are set to 1

	#define MSG2EXT(msg) (msg & 0x1FFFFFFFL)
	
		 mng.c => else if (ucAS0_RXbuf[4]==0x01)  //unsigned char ucAS0_RXbuf[200]; // Reception Buffer in near_var
				{
  				ucFlag_CAN=0;
				}

HWM 608 "A received message is stored into the valid Message Object with matching
identifier and Direction = receive (Data Frame) or Direction = transmit(Remote Frame). Extended frames can
be stored only in Message Objects with XTD = one, standard frames in Message Objects with XTD = zero. If
a received message (Data Frame or Remote Frame) matches with more than one valid Message Object, it is
stored into that with the lowest message number"
*/

void CAN0_SetRxBuffer(unsigned char buffer, unsigned long id, unsigned char irq, unsigned long mask)
{
// CAN0: message buffer 1 will be used as receive-buffer

// Prepare Arbitration Interface Register	    
	if(ucFlag_CAN)	  
  	{
  		IF1ARB0 = MSG2STD(id);           // Define message id
  		IF1ARB0_XTD    = 0;              //The 11-bit (“standard”) Identifier will be used for this Message Object.
  	}
  	else
	{
	 	IF1ARB0 = MSG2EXT(id);      // Define message id: Use MSG2STD() for 11bit IDs / Use MSG2EXT() for 29bit IDs
	 	IF1ARB0_XTD = 1;            // The 29-bit (“extended”) Identifier will be used for this Message Object.
	}

 IF1ARB0_DIR = 0;            // Direction = receive: On TXRQST, a Remote Frame with the identifier of this Message Object is transmitted. 
			                 // On reception of a Data Frame with matching identifier, that message is stored in this Message Object.

 IF1ARB0_MSGVAL = 1;         // The Message Object is configured and should be considered by the Message Handler.
	
//============================================================================================================================================= 
/*2_ Mask Interface Register configuration
  ***************************************
* Setup mask corresponding to our application 

mng.c => case (Mask)
	
	// Mask 01 :
	CAN_MASK1= 0x00000000;
	CAN_MASK1= ucAS0_RXbuf[9];
	CAN_MASK1 = (CAN_MASK1 << 8) + ucAS0_RXbuf[8];
	CAN_MASK1 = (CAN_MASK1 << 8) + ucAS0_RXbuf[7];
	CAN_MASK1 = (CAN_MASK1 << 8) + ucAS0_RXbuf[6];
 	
	// Mask 02 :
	CAN_MASK2= 0x00000000;
	CAN_MASK2= ucAS0_RXbuf[13];
	CAN_MASK2 = (CAN_MASK2 << 8) + ucAS0_RXbuf[12];
	CAN_MASK2 = (CAN_MASK2 << 8) + ucAS0_RXbuf[11];
	CAN_MASK2 = (CAN_MASK2 << 8) + ucAS0_RXbuf[10];
 	
	// Mask 03 :
	CAN_MASK3= 0x00000000;
	CAN_MASK3= ucAS0_RXbuf[17];
	CAN_MASK3 = (CAN_MASK3 << 8) + ucAS0_RXbuf[16];
	CAN_MASK3 = (CAN_MASK3 << 8) + ucAS0_RXbuf[15];
	CAN_MASK3 = (CAN_MASK3 << 8) + ucAS0_RXbuf[14]; 
	
	// Mask 04 :
	CAN_MASK4= 0x00000000;
	CAN_MASK4= ucAS0_RXbuf[21];
	CAN_MASK4 = (CAN_MASK4 << 8) + ucAS0_RXbuf[20];
	CAN_MASK4 = (CAN_MASK4 << 8) + ucAS0_RXbuf[19];
	CAN_MASK4 = (CAN_MASK4 << 8) + ucAS0_RXbuf[18]; 
	 return 1; 
	

[bit6] MASK Access Mask Bits
	
	0 Mask bits unchanged.
	
	1 Transfer Identifier Mask + MDir + MXtd to IFx Message Buffer Register.

*/

// Mask Interface Register configuration
 
IF1MSK0 = mask;             // Setup Mask corresponding to our application
 
IF1MSK20_MXTD   = 1;        // The extended identifier bit (XTD) is used for acceptance filtering.


IF1MSK20_MDIR= 1; 	    // The message direction bit (DIR) is used for acceptance filtering

//===================================================================================================	
// Prepare Message Control Interface Register
 
 IF1MCTR0_NEWDAT  = 0;       // No new data has been written into the data portion of this Message Object by the Message Handler since last time this flag was cleared
			     //by the CPU.

 IF1MCTR0_MSGLST  = 0;       // No message lost since last time this bit was reset by the CPU
 
 IF1MCTR0_INTPND  = 0;       // This message object is not the source of an interrupt.
 
 IF1MCTR0_UMASK   = 1;       // 0: Not use Filter mask (Full CAN Object) / 1: Use Filter Mask
	
			     // Use Mask (MSK28-0, MXTD, and MDIR) for acceptance filtering.


// Copier le message vers l'interface registre
// *******************************************
if (irq)                    // 1:activate Rx-Interrupt to prepare sending msg
{
 IF1MCTR0_TXIE  = 0;       //  0: Disable Tx-Interrupt / 1: Enable Tx-Interrupt  
 IF1MCTR0_RXIE  = 1;       //  0: Disable Rx-Interrupt / 1: Enable Rx-Interrupt 
}
 else
 {
 IF1MCTR0_TXIE  = 0;       // 0: Disable Tx-Interrupt / 1: Enable Tx-Interrupt
 IF1MCTR0_RXIE  = 0;       // 0: Disable Rx-Interrupt / 1: Enable Rx-Interrupt
   }
//==============================================================================================================
	
 IF1MCTR0_RMTEN   = 0;     // 0:Disable Remote / 1: enable Remote
 IF1MCTR0_TXRQST  = 0;     // Clear Transmission Request
 IF1MCTR0_EOB     = 1;     // 0: Buffer is part of FiFo / 1: Single message buffer
	
 IF1CMSK0  = 0xF0;          // Prepare Interface Command Mask Register:
	                    // WRRD    = 1 : Write information from interface to object
	                    // MASK    = 1 : Write Mask register
	                    // ARB     = 1 : Write Arbitration Register (ID Register)
	                    // CONTROL = 1 : Write object control register (e.g. Data length, IRQ enable, etc)
	                    // CIP     = 0 : (dont care for writing to object)
                            // TXREQ   = 0 : No Transmission Request
	                    // DATAA   = 0 : Do not change Data A register
	                    // DATAB   = 0 : Do not change Data B register
	
IF1CREQ0 = buffer;          // Transfer the Interface Register Content to the Message Buffer
}

//Envoie d'un message CAN:
//************************
//**************************
//
//1_	Préparer l’arbitrage de l’interface registre  (voir Set_RxBuffer 1_/ )
//*******************************************************************************

int CAN0_SendMessage(unsigned char buffer, unsigned long id, unsigned char *memory)
{
  unsigned long int timeout = 0;
  
  unsigned char Len;
  
  // Prepare Arbitration Interface Register
  
  if(ucFlag_CAN)
  { 
    
   IF1ARB0 = MSG2STD(id);           //  MSG2STD: 11bit ID / MSG2EXT: 29bit ID
   
   IF1ARB0_XTD    = 0;              //  0: 11bit ID / 1: 29bit ID
  
  }
  
  else
  {
   
   IF1ARB0 = MSG2EXT(id);           //  MSG2STD: 11bit ID / MSG2EXT: 29bit ID
   
   IF1ARB0_XTD    = 1;              //  0: 11bit ID / 1: 29bit ID
  
  }  
  
  IF1ARB0_DIR    = 1;              //  Direction = transmit: On TXRQST, the respective Message Object is transmitted as a Data Frame. On reception of a Remote Frame with
				   //  matching identifier, the TXRQST bit of this Message Object is set (if RMTEN = one). 
  
  IF1ARB0_MSGVAL = 1;              //  0: Buffer invalid / 1: Buffer valid 

//=========================================================================================================================================================================
// configure Mask Interface Register 

  IF1MSK0 = 0x1FFFFFFF;            //  Setup Mask corresponding to our application (HWM 580) 
 
  IF1MSK20_MXTD   = 1;             //  The extended identifier bit (XTD) is used for acceptance filtering.
=========================================================================================================================================================================  
// Prepare Message Control Interface Register 
  
  IF1MCTR0_NEWDAT = 0;             // No new data has been written into the data portion of this Message Object by the Message Handler since last time this flag was cleared
				   // by the CPU. 
  
  IF1MCTR0_MSGLST = 0;             // No message lost since last time this bit was reset by the CPU.
				   // Message Lost (only valid for Message Objects with direction = receive)
  
  IF1MCTR0_INTPND = 0;             // This message object is not the source of an interrupt.
  
  IF1MCTR0_UMASK  = 0;             // Mask ignored 
  
  IF1MCTR0_TXIE   = 0;             // INTPND will be left unchanged after the successful transmission of a frame 
  
  IF1MCTR0_RXIE   = 0;             // INTPND will be left unchanged after a successful reception of a frame 
  
  IF1MCTR0_RMTEN  = 0;             // At the reception of a Remote Frame, TXRQST is left unchanged.
  
  IF1MCTR0_TXRQST = 0;             // This Message Object is not waiting for transmission
  
  IF1MCTR0_EOB    = 1;             // Single Message Object or last Message Object of a FIFO Buffer.  
  
  IF1MCTR0_DLC = Len = *memory++;  // Set number of Data to be transmitted 

				   // see mng.c 375  "ucAS0_TXbuf[indice++]=0x00; // DATA Len"
 
  // Set Data 
  
  IF1DTA0 = *((unsigned long *)memory);       // voir HWM 606
  
  IF1DTB0 = *((unsigned long *)(memory+4));
  
  // Demande de transmission du message

  IF1CMSK0  = 0xF7;           // Prepare Interface Command Mask Register: 

                              // WRRD    = 1 : Write: Transfer data from the selected Message Buffer Registers to the Message Object addressed by the Command
							  // Request Register

                              // MASK    = 1 : Transfer Identifier Mask + MDir + MXtd to Message Object.

                              // ARB     = 1 : Transfer Identifier + Dir + Xtd + MsgVal to Message Object.

                              // CONTROL = 1 : Write object control register (e.g. Data length, IRQ enable, etc)
							  // Transfer Control Bits to Message Object.

                              // CIP     = 0 : When writing to a Message Object, this bit is ignored. (dont care for writing to object)

                              // TXREQ   = 1 : set TXRQST bit

                              // DATAA   = 1 : Transfer Data Bytes 0-3 to Message Object.
                              
							  // DATAB   = 1 : Transfer Data Bytes 4-7 to Message Object

// RQ: 0x0000:0000:1111:0111 <=> 0xF7  


//==========================================================================================================================
  IF1CREQ0 = buffer;          // Transfer the Interface Register Content to the Message Buffer 
  
// Wait for transmission of message
  
// look void CAN0_GetRxBuffer (void)

  while((TREQR0 & (0x1 << (buffer -1)) != 0) && (timeout++ < CAN_TIMEOUT) && (CTRLR0_INIT != 1))

  {
  
  __wait_nop();

  }

  if( (timeout == CAN_TIMEOUT) || (CTRLR0_INIT == 1) )

  {

    // Cancel transmission request 

    IF1CMSK0  = 0x10;         // Prepare Interface Command Mask Register: Load only control data from message object

                              // WRRD    = 0 : Read: Transfer data from the Message Object addressed by the Command Request Register into the selected
							  //Message Buffer Registers.

                              // MASK    = 0 : Mask bits unchanged.

                              // ARB     = 0 : Arbitration bits unchanged.

                              // CONTROL = 1 : Transfer Control Bits to Message Object.

                              // CIP     = 0 : (dont care for writing to object)

                              // TXREQ   = 0 : Set Transmission Request

                              // DATAA   = 0 : Write Data A register

                              // DATAB   = 0 : Do not write Data B register
        
    IF1CREQ0 = buffer;        // Transfer the Interface Register Content to the Message Buffer 

    IF1MCTR0_TXRQST = 0;      // Clear Transmission Request 

    IF1CMSK0_WRRD = 1;        // Prepare Interface Command Mask Register

    IF1CREQ0 = buffer;        // Transfer the Interface Register Content to the Message Buffer

    return (0);               // return error

  }

  return (1);                 // return ok 

}

int  CAN0_GetRxBuffer(void)
{
  unsigned char number=1; 
  
  if (NEWDT0)		
  {
    while ((NEWDT0 & ((unsigned long)1 << (number++ - 1)))==0);
  
    return (number-1);
  }
  else 
    return (0);
}

int CAN0_ReadMessage(unsigned char buffer, unsigned long *id, unsigned char *memory)
{
  unsigned char Len;

  // check whether a message is received buffer 

  if (NEWDT0 & ((unsigned long)1 << (buffer - 1)))

  {
  IF2CMSK0  = 0x3F;         // Prepare Interface Command Mask Register: 

							//   Receive Control Information, Message data and Arbitration from Message Buffer

							// WRRD    = 0 :Read: Transfer data from the Message Object addressed by the Command Request Register into the selected
							  //Message Buffer Registers.

							// MASK    = 0 : Do not transfer Mask register

							// ARB     = 1 : Arbitration bits unchanged.

							// CONTROL = 1 : Transfer Control Bits to Message Object.

							// CIP     = 1 : (Clear Interrupt Pending flag)

							// TXREQ   = 1 : Set Transmission Request

							// DATAA   = 1 : Transfer Data A register

							// DATAB   = 1 : Transfer Data B register

  IF2CREQ0 = buffer;        // Start transfer  

  if( IF2MCTR0_MSGLST )     // check whether or not a message was lost 

  {

  IF2MCTR0_MSGLST = 0;      // Clear MSGLST Flag                

  IF2CMSK0  = 0x90;         // Prepare Interface Command Mask Register: 

							//   write control data only

							// WRRD    = 1 : Write information from interface to object

							// MASK    = 0 : Do not transfer Mask register

							// ARB     = 0 : Do not transfer Arbitration Register (ID Register)

							// CONTROL = 1 : Transfer object control register (e.g. Data length, IRQ enable, etc)

							// CIP     = 0 : (dont care for writing to object)

							// TXREQ   = 0 : No Transmission Request

							// DATAA   = 0 : Do not transfer Data A register

							// DATAB   = 0 : Do not transfer Data B register

  IF2CREQ0 = buffer;      // Start transfer

  }   

  *memory++ = Len = IF2MCTR0_DLC;  // Get Number of transmitted Data 

  // Get Data         

  *((unsigned long *)memory)     = IF2DTA0;

  *((unsigned long *)(memory+4)) = IF2DTB0;

  if(CAN_EXTENDED)

  *id = EXT2MSG(IF2ARB0);   // Get the message ID: STD2MSG for 11bit ID / EXT2MSG for 29bit ID 

  else

  *id = STD2MSG(IF2ARB0);   //Get the message ID: STD2MSG for 11bit ID / EXT2MSG for 29bit ID

  return (1);               // return ok

  }

  else

  {

  return (0);               // no message received

  }

  }

  void vCAN0_TEST_EXE(void)

{
  CAN0_init(); 
  
  CAN0_SetRxBuffer( 4, 0x0000, 1, CAN_MASK1); // Receive all messages
  
  CAN_IRQ_selection_flag = 1;
  
  CAN_Send_ID = 1;
} 
 

 void vCAN0_ReceiveInterrupt_ISRr(void)
{

  unsigned int buffer;

  buffer = CAN0_GetRxBuffer();

  while(buffer) 

  {

  CAN0_ReadMessage(buffer, &CAN_Receive_ID, &CAN_Receive_Data[0]);     

  for (DataPos=1; DataPos<=CAN_Receive_Data[0]; DataPos++)

  {
  ;
  }

  if(flag_stop_data==1)

  ucMng_CurrentSendState=SEND_DATA_BROADCAST_CAN; 

  buffer =0; // Only for test 
  
  } 
} 
