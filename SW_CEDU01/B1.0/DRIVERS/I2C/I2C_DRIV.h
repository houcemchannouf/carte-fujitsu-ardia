//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : I2C_DRV 
//############################################################################//
// FILE : I2C_DRV.h (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 20/08/12 | Ben Slimene Rihem  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//
#include "mb96348rs.h"
#include "I2C_DRV.cfg"
#include "I2C_DRV.c"


//I2C port input 
#define PIER04_IE4  
#define PIER04_IE5

//I2C interface
#define ICCR0_EN 
#define ICCR0_CS0 
#define ICCR0_CS1 
#define ICCR0_CS2 
#define ICCR0_CS3 
#define ICCR0_CS

//define IDAR0 data register
#define IDAR0 

//define IBCR0 Bus Control Register
#define IBCR0_BEIE 
#define IBCR0_BER 
#define IBCR0_ACK //Acknowledge generated
#define IBCR0_INT //Transfer interrupt request flag
#define IBCR0_INTE //Interrupt
#define IBCR0_GCAA 
#define IBCR0_MSS 
#define IBCR0_SCC 

//define IBSR0 Bus Status Register
#define IBSR0_LRB
#define IBSR0_BB 


/* Prototypes */

void I2C_Init(void)
void I2C_Acknowledge(void)
void I2C_Start(unsigned char slave_address)
void I2C_Stop(void)
void I2C_Write(unsigned char value)
void I2C_Continue(unsigned char slave_address)
unsigned char I2C_Read(void)
unsigned char I2C_LastRead(void)
 
 