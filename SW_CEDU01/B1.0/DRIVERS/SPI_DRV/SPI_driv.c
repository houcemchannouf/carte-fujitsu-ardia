
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
//         01.00  | 08/08/12|  Ben Slimene Rihem  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//
#include "..\mb96348rs.h"


void InitUSART(void)
{



 BGR02 = 207;    // 1M Bit/s @ 16 MHz

 ESCR02 = 0x01;   // SCES = 1 rising clock edge

 ECCR02 = 0x10;   // SCDE = 1 enable clock delay

 SCR02 = 0x03;   // reception and transmission enable (allow communication)

SMR02 = 0x83;   // Mode 2, SCLK enable, SOT enable

SSR02 = 0x04;   // send and receive  MSB first,Disallow interrupts

PRRR6_SIN2_R = 1;      // enable SIN2 input pin

PRRR6_SOT2_R = 1;      // enable SOT2 output

EPFR20_D1 = 0;

PRRR6_SCK2_R= 1;      // enable SCK2 output pin

EPFR20_D2 = 0;



}


void InitPorts(void)
{
// Bit#2: CS, Bit#1: PE, Bit#0: PRE


  PRRR9=0x01;	// Activate SCK9 input/output pin
  PRRR8=0xc0;// a verifier
  PDR09 = 0x00;    // All Low PDR is not changed
  DDR09 = 0x07;    // CS, PE, PRE to output
  DDR07  &= 0xFE;	//  Pin Direction
  PIER07 &= 0xFE;	// Port Input Enable



}



void wait(unsigned int j)
{

volatile unsigned short i;
for (i = 0; i < j; i++)
 {

__wait_nop();
__wait_nop();
__wait_nop();
__wait_nop();
 }
}




void write_enable(void)
{
PDR00_P7 = 1;    // CS = 1 enable communication

while (SSR2_TDRE == 0);  //wait until transmission data register is full

 TDR02 = 0x01;    // Start-Bit (with "leading zeros")

while (SSR2_TDRE == 0);

 TDR02 = 0x30;    // WEN  Enable programming (write enable) command

while (ECCR2 & 0x01);   // wait for start of transmission
//  (or ongoing)

while (!(ECCR2& 0x01));  // wait for transmission finished

PDR00_P7 = 0;    // CS = 0
}









void write_disable(void)
{

PDR00_P7  = 1;    // CS = 1  enable communication

while (SSR2_TDRE == 0);

 TDR02 = 0x01;    // Start-Bit (with "leading zeros")

while (SSR2_TDRE == 0);

 TDR02 = 0x00;    // WDS Disable programming (write disable) command

while (ECCR2 & 0x01);   // wait for start of transmission  //  (or ongoing)

while (!(ECCR2& 0x01));  // wait for transmission finished

PDR00_P7  = 0;    // CS = 0
}







void write_eeprom(unsigned char adr)
{

unsigned char dout, command;

PDR00_P7 = 1; // CS = 1

while (SSR2_TDRE == 0);

TDR02 = 0x01; // Start-Bit (with "leading zeros")

command = (adr & 0x3F) | 0x40; // Address and Write-Instruction

dout = command;

while (SSR2_TDRE == 0);

TDR02 = dout;

dout = (data[adr] >> 8) & 0xFF; // MSB direction

while (SSR2_TDRE == 0);

TDR02 = dout;

dout = data[adr] & 0xFF; // LSB

while (SSR2_TDRE == 0);

TDR02 = dout;

while (ECCR2 & 0x01); // wait for start of transmission
// (or ongoing)

while (!(ECCR2 & 0x01)); // wait for transmission finished

PDR00_P7 = 0; // CS = 0

wait(1);
// Next function (waiting for busy release) is made by
// polling. Please note, that for the NM93CS46 EEPROM the
// wait time can take till 10 ms! I. e. the CPU is then
// also busy. For fast application a timer should be used,
// which generates an interrupt after 10 ms from here,
// so that the CPU can perform other jobs in this time.

PDR00_P7 = 1; // CS = 1  enable communication

while(ESCR2_SIOP == 1); // wait for eeprom busy

while(ESCR2_SIOP == 0); // wait for eeprom busy release

PDR00_P7 = 0; // CS = 0 desable communication
}







void read_eeprom(unsigned char adr)
{
unsigned char din, command, dout;

PDR00_P7 = 1; // CS = 1

while (SSR2_TDRE == 0);

TDR02 = 0x01; // Start-Bit (with "leading zeros")

command = (adr & 0x3F) | 0x80; // Address and Write-Instruction

dout = command;

while (SSR2_RDRF == 0); // transmission finished (via
// reception)?

din = RDR02; // flush reception register

TDR02 = dout;

while (SSR2_RDRF == 0); // transmission finished (via
// reception)?

din = RDR02; // flush reception register

SCR2_CRE = 1; // Clear possible errors, reset
// reception state machine
// NOTE: Make sure that SCK is "0" while setting SCDE to "0"
// (ECCR0 = 0x00;)
// In this case (1M bps) no check is needed. Be careful with
// slower baud rates!

ECCR2 = 0x00; // SCDE = 0 Needed
// for special read timing of
// used EEPROM (may not be
// necessary for other EEPROMs)
TDR02 = 0x00; // set dummy byte to produce SCLK

while (SSR2_RDRF == 0); // transmission finished (via // reception)?

din = RDR02; // MSB
readbuffer[adr] = (din << 8);

while (SSR2_TDRE == 0);

TDR02 = 0x00; // set dummy byte to produce SCLK

while (SSR2_RDRF == 0);

din = RDR02; // LSB

readbuffer[adr] = (readbuffer[adr] | din);

ECCR2 = 0x10; // SCDE = 1: Set back

// for write timing

PDR00_P7= 0; // CS = 0
}




void main(void)
{
unsigned char i, error, dummy;
InitIrqLevels();
__set_il(31); // allow all levels
__EI(); // globally enable interrupts
PORTEN = 0x3; // Enable I/O Ports
InitPorts(); // Initialize PRE, PE, and CS
InitUSART(); // Init USART for SPI communication
// Put code or function call here to produce data for EEPROM
// write data
PDR00_P7 = 1; // PE = 1 must be set here
write_enable();
for (i = 0; i < DATASIZE; i++)
{
write_eeprom(i);
}
write_disable();
PDR00_P7 = 0; // PE = 0 must be set here
// Do something else ...
// read data
dummy = RDR02; // flush read buffer
SCR02_CRE = 1; // clear possible overruns
for (i = 0; i < DATASIZE; i++)
{
read_eeprom(i);
}


}
