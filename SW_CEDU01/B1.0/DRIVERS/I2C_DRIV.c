//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : I2C_DRV 
//############################################################################//
// FILE : I2C_DRV.c (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 20/08/12 |  Rihem Ben Slimene | Creation of this file
//
//############################################################################//

#include "mb96348rs.h"
#include "I2C_DRV.h"
#include "I2C_DRV.cfg"


void I2C_Init(void)
{
PIER04_IE4 = 1; // SDA0 pin to input (MB96340 Series)
PIER04_IE5 = 1; // SCL0 pin to input (MB96340 Series)
//ICCR0 Clock Control Register
ICCR0_EN = 0; // stop I2C interface
ICCR0_CS4 = 1; // CS4..0 : set prescaler
ICCR0_CS3 = 1; 
ICCR0_CS2 = 1;
ICCR0_CS1 = 1;
ICCR0_CS0 = 1;
ICCR0_EN = 1; // enable I2C interface
IDAR0 = 0; // clear data register
////IBCR0 Bus Control Register
IBCR0_BER = 0; // clear bus error interrupt flag
IBCR0_BEIE = 0; // bus error interrupt disabled
IBCR0_ACK = 0; // no acknowledge generated
IBCR0_GCAA = 0; // no call acknowledge is generated
IBCR0_INTE = 0; // disable interrupt
IBCR0_INT = 0; // clear transfer interrupt request flag
}




void I2C_Acknowledge(void)
{
// IBSR0 Bus Status Register
while(IBSR0_LRB == 1); // no answer from slave, program will get stuck here
// a timeout mechanism should be implemented here
}



void I2C_Start(unsigned char slave_address)
{
  do
  {
IBCR0_BER = 0;  // clear bus error interrupt flag
ICCR0_EN = 1;  // enable I2C interface
IDAR0 = slave_address;   // slave_address is sent out with start condition
IBCR0_MSS = 1;   // set master mode and set start condition
IBCR0_INT = 0;   // clear transfer end interrupt flag
while(IBCR0_INT == 0); // look if transfer is in process
  }
  
while (IBCR0_BER == 1); // retry if Bus-Error detected
while(IBSR0_LRB == 1) // no acknowledge means device not ready
    { // maybe last write cycle not ended yet
IBCR0_SCC = 1; // try restart (= continue)
while (IBCR0_INT == 0); // wait that transfer is finished
    }
}




void I2C_Stop(void)
{
while (IBCR0_INT == 0); // wait that transfer is finished
IBCR0_MSS = 0; // change to slave and release stop condition
IBCR0_INT = 0; // clear transfer end interrupt flag
while (IBSR0_BB); // wait till bus free
}





void I2C_Write(unsigned char value)
{
IDAR0 = value; // load data or address into register
IBCR0_INT = 0; // clear transfer end interrupt flag
while (IBCR0_INT == 0); // look if transfer is in process
I2C_Acknowledge(); // wait for Acknowledge
}





void I2C_Continue(unsigned char slave_address)
{
IDAR0 = slave_address; // slave_address is sent out with start condition
IBCR0_SCC = 1; // restart (= continue)
while (IBCR0_INT == 0); // wait that transfer is finished
}





unsigned char I2C_Read(void)
{
IBCR0_ACK = 1; // acknowledge has to be sent
IBCR0_INT = 0; // clear transfer end interrupt flag
while (IBCR0_INT == 0); // wait that transfer is finished
return(IDAR0); // read received data out
}




unsigned char I2C_LastRead(void)
{
IBCR0_ACK = 0; // no acknowledge has to be send after last byte
IBCR0_INT = 0; // clear transfer end interrupt flag
while(IBCR0_INT == 0); // wait that transfer is finished
return(IDAR0); // read received data out
}



void main(void)
{
unsigned char i, result[16];
// write to EEPROM
I2C_Start(0xA0 | WRITE); // send slave address
I2C_Write(0x00); // Address where to write to
I2C_Write(65); // Databyte 'A'
I2C_Write(66); // Databyte 'B'
I2C_Write(67); // Databyte 'C'
I2C_Stop();

// read from EEPROM
I2C_Start(0xA0 | WRITE); // Write Command to ...
I2C_Write(0x00); // ... set address from where to read
I2C_Continue(0xA0 | READ); // Restart, with READ command
i = 0;
result[i++] = I2C_Read(); // receive data from EEPROM
result[i++] = I2C_Read(); // receive data from EEPROM
result[i++] = I2C_LastRead(); // receive last byte from EEPROM
I2C_Stop();

}