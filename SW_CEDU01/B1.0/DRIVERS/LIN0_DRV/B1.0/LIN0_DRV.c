//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : LIN0_DRV  
//############################################################################//
// FILE : LIN0_DRV.C (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   |   Author         | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 11/08/12 |  Ghariani Ahmed  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//


#include "..\Drivers\LIN0_DRV\LIN0_DRV.h"


#define DATALENGTH 8
#define SLAVESEND 0x7D
#define MASTERSEND 0xFE


unsigned char LIN_State, Rx_Error, Rx_Data, Master_Send, LIN_Header, LIN_Count;
unsigned char LIN_Data[DATALENGTH];

unsigned int ICU_Value1, ICU_Value2;
unsigned char ICU_State;


void InitUART1(void)
{
// Initialize UARTn asynchronous LIN mode
BGR1 = 1666;           // 1666 => 9600Baud @ 16MHz
SMR1 = 0xC5;           // Reset, LIN mode

iTrans1 = 1;           // Enable tansmission
iRecep1  = 0;          // Disable reception

iEnableRecInt1 = 1;    // Enable Reception Interrupt
iSRLM1 = 0;            // LSB 

Sin1 = 1;              // Enable SIN , SOT for Asynchrone Transfer
SOT1 = 1;               
iEnableLINInt1 = 1;    // Enable LIN break Detection Interrupt  ESCR1_LBIE
}

// Initialize Input Capture Unitfor LIN-Synch-Field measurement
void InitICU1(void)
{
// Connect ICU1 to UART1
iInCaptur = 1;     
// Both edge detection
iICS01EG00 = 1;				// Both edge detection
iICS01EG01 = 1;
iICS01EG10 = 1;
iICS01EG11 = 1;


// Clear possible ICU1-IRQ
iICS01ICP0 = 0;      
iICS01ICP1 = 0;

 // Clear State flag
ICU_State = 0;      
}


void Rx_LIN0(void)
{
	if (iLINsynBreakFlag1)				// LIN Break Detection?
	{
		iLINsynBreakFlag1 = 0;			// Clear flag
		
		if (LIN_State == 1)
		{
			iRecep1 = 1;		// Enable reception
			LIN_State = 2;		// ready to receive synch field
			LIN_Checksum = 0;
			LIN_Count = 0;
			
			// Clear possible ICU1-IRQ
        iICS01ICP0 = 0;      
        iICS01ICP1 = 0;
     // Enable ICU7-Interrupt
        iICS01ICE1 = 1;
			  iICS01ICE0 = 1;		

		}
		
		else
		{
			Rx_Error = 1;		// Unexpected reception of break
		}
	}
	
	else if (iRecDataFlag1)			// Reception?
	{
		Rx_Data = rRDR1;			// Get reception data
		
		if (iOverrunError1 || iframeError1)	// Reception errors?
		{
			Rx_Error = 2;
		}
		
		else if (LIN_State == 2)	// Synch field read?
		{
			iICS01ICE1 = 0;
			iICS01ICE0 = 0;				// disable ICU7-Interrupt

			if (Rx_Data != 0x55)
			{
				Rx_Error = 3;
			}
			
			else
			{
				LIN_State = 3;		// ready to receive header				
			}
		}
		
		else if (LIN_State == 3)	// Header read?
		{
			LIN_Header = Rx_Data;
			LIN_Checksum = LIN_Header;	// according LIN 2.0
			
			if (LIN_Header == SLAVESEND)
			{
				rTDR1 = LIN_Data[LIN_Count];	// Send LIN Data
				LIN_Checksum += LIN_Data[LIN_Count];
				LIN_Count++;
			}
			
			LIN_State = 4;
		}
		
		else if (LIN_State == 4)	// LIN Data read / write
		{
			if (LIN_Header == MASTERSEND)	// Master sent data?
			{
				LIN_Checksum += Rx_Data;
				LIN_Data[LIN_Count] = Rx_Data;
				LIN_Count++;
				
				if (LIN_Count == DATALENGTH)	// End of message reached?
				{
					LIN_Count = 0;
					LIN_State = 5;
					LIN_Checksum = 0xFF ^ ((LIN_Checksum & 0x00FF) + (LIN_Checksum >> 8));
				}
			}	
			
			else
			{
				LIN_Checksum += LIN_Data[LIN_Count];
				TDR3 = LIN_Data[LIN_Count];	// Send next LIN Data		
				LIN_Count++;
				
				if (LIN_Count == DATALENGTH)	// End of message reached?
				{
					LIN_Count = 0;
					LIN_State = 5;
					LIN_Checksum = 0xFF ^ ((LIN_Checksum & 0x00FF) + (LIN_Checksum >> 8));
				}
			}
		}
		
		else if (LIN_State == 5)		// LIN Checksum read / write
		{
			if (LIN_Header == MASTERSEND)	// Master sent data?
			{
				if (Rx_Data != LIN_Checksum)
				{
					Rx_Error = 4;
				}
			}	
			
			else
			{
				rTDR1 = LIN_Checksum;	// Send Checksum
			}
			
			iRecep1 = 0;				// disable reception wait for LIN break
			LIN_State = 1;				//  (new message)
		}
		

	}
	
	else						// Not recognized interrupt cause
	{
		Rx_Error = 5;	
		iEnableRecInt1 = 0;			// disable reception interrupt
	}	
}

void ICU1_IRQHandler(void)
{
	if (ICU_State == 0)		// Rising edge detected?
	{
		ICU_Value1 = rIPCP1;
		ICU_State = 1;
	}
	else					// Falling edge (last edge) detected!
	{
		ICU_Value2 = rIPCP1;
		ICU_State = 0;
		rBGR1 = (ICU_Value2 - ICU_Value1) / 8; // Calculate new Baud rate
	}
	
	iICS01ICP0 = 0;      
  iICS01ICP1 = 0;
}


