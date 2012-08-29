//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : SPI_DRV 
//############################################################################//
// FILE : SPI_DRV.c (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 18/07/12 |  YFAR  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//
#include "mb96348rs.h"
#include "SPI_DRV.h"
//#include "mb96348rw.h"
void vSPI_iCS_Set(unsigned char u8State);
void vSPI_iStartBit_Set(unsigned char u8State);
void wait(unsigned int j);

void vSPI_iCS_Set(unsigned char u8State)
{
   // Set Bit 2 off Port 9 to u8State
	PDR09_P2 = u8State &0x01;
}

void vSPI_iStartBit_Set(unsigned char u8State)
{
   TDR9 = u8State &0x01;
}
void vSPI_iInitUART(void)
{
  BGR9 = 207;//15;       // 1M Bit/s @ 16 MHz
  ESCR9 = 0x01;    // SCES = 1 => CPOL = 0
  ECCR9 = 0x10;    // SCDE = 1 => CPHA = 0
  SCR9 = 0x03;     // reception and transmission enable
  SMR9 = 0x83;     // Mode 2, SCLK enable, SOT enable
  SSR9 = 0x04;     // MSB first, no interrupts
 }

void vSPI_iInitPorts(void)
{
  // Bit#2: CS, Bit#1: PE, Bit#0: PRE
  PRRR9=0x01;	// Activate
  PRRR8=0xc0;// a verifier
  PDR09 = 0x00;    // All Low
  DDR09 = 0x07;    // CS, PE, PRE to output
  DDR07  &= 0xFE;	//  Pin Direction
  PIER07 &= 0xFE;	// Input Enable

}

void wait(unsigned int j)
{
  volatile unsigned int i;
	
  for (i = 0; i < j; i++)
  {
    __wait_nop();
    __wait_nop();
    __wait_nop();
    __wait_nop();
  }
}

//void read_eeprom(unsigned char adr)
unsigned char u8SPI_eRead_Data(unsigned char adr,unsigned /*short*/char *Fu8Data/*, unsigned char Fu8ReadType*/)
{
  unsigned char din, command, dout;
	
  vSPI_iCS_Set(0);           // CS = 0
		
 // vSPI_iStartBit_Set(0x01);            // Start-Bit (with leading spaces)
		
  command = (adr & 0x3F) | 0x00;  // Address and Write-Instruction 0x80 : bit0 = 1
  dout = command;	
  //while (SSR9_RDRF == 0); // transmission finished (via reception)?
  while (SSR9_TDRE == 0); // transmission finished (via reception)?
  din = RDR9;             // flush reception register
  TDR9 = dout;		

  while (SSR9_RDRF == 0); // transmission finished (via reception)?
  din = RDR9;             // flush reception register
  SCR9_CRE = 1;           // Clear possible errors, reset reception state machine
	
  // NOTE: Make sure, that SCK is "0" while setting SCDE to "0" (ECCR9 = 0x00;)
  //   In this case (1M bps) no check is needed. Be careful with slower
  //   baud rates!
 // ECCR9 = 0x00;           // SCDE = 0 => CPHA = 0 : Needed for special read timing of
                          //   used EEPROM (may be not necessary for other EEPROM)
 /*if ( Du8MultipleAcces == Fu8ReadType)
  {
	TDR9 = 0x00;            // set dummy byte to produce SCLK
		
	while (SSR9_RDRF == 0); // transmission finished (via reception)?
	din = RDR9;             // MSB
	Fu16Data = (din << 8);
		
	while (SSR9_TDRE == 0);
  }
  else
  {
	//Empty ELSE
  }*/
  TDR9 = 0x00;            // set dummy byte to produce SCLK
	
  while (SSR9_RDRF == 0);
  din = RDR9;             // LSB
  /*Fu16Data = (Fu16Data | din);*/
  (*Fu8Data) = din;
		
  ECCR9 = 0x10;           // SCDE = 1 => CPHA = 1 : Set back for write timing
		
  vSPI_iCS_Set(1);           // CS = 1
  return 1;
}

unsigned char u8DSPI_eWrite_Data(unsigned char adr, unsigned char *Fu8Data)
{
  unsigned char dout, command;
	
  vSPI_iCS_Set(0);           // CS = 0
	
  //while (SSR9_TDRE == 0);		
 // vSPI_iStartBit_Set(0x01);            // Start-Bit (with leading spaces)
		
  command = (adr & 0x3F) | 0x00; // Address and Write-Instruction
  dout = command;	
  while (SSR9_TDRE == 0);		
  TDR9 = dout;
	
  dout = (*Fu8Data) & 0xFF; // MSB
  while (SSR9_TDRE == 0);		
  TDR9 = dout;
		
  while (ECCR9 & 0x01);    // wait for start of transmission (or ongoing)
  while (!(ECCR9 & 0x01)); // wait for transmission finished
		
  vSPI_iCS_Set(1);            // CS = 1
	
  wait(1);
  return 1;
}



void vDSPI_eInitSPI(void)
{
  	
  __set_il(7);    // allow all levels
  __EI();         // globally enable interrupts
  
  vSPI_iInitPorts();    // Initialize PRE, PE, and CS
  vSPI_iInitUART();     // Init UART for SPI communication
}