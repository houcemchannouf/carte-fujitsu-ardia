//############################################################################//
// HEAD : (c) ARDIA 2010 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : MAIN 
//############################################################################//
// FILE : MAIN.C (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 29/09/10 |  SGHR  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//



#include "..\..\DRIVERS\LED_DRV\B1.0\LED_DRV_TST.h"
#include "..\..\DRIVERS\LCD_DRV\B1.0\LCD_DRV_TST.h"
#include "..\..\DRIVERS\LCD_DRV\B1.0\LCD_DRV.h"
#include "..\..\DRIVERS\CLV_DRV\B1.0\CLV_DRV.h"
#include "..\..\DRIVERS\SPI_DRV\B1.0\SPI_DRV.h"
#include "..\..\DRIVERS\LIS3DH_DRV\LIS3DH_DRV.h"
#include "..\..\PROTOCOLES\LIS3DH_PRO\LIS3DH_PRO.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#define Waiting_LunchTest 0
#define Startting_Test 	  1
char * itoa(int value, char *string, int radix);
#include "..\..\DRIVERS\CAN0_DRV\B1.0\CAN0_DRV.h"
unsigned long int us32Counter = 0 ,us32Counter_1 = 0;
void main(void)
{
	
	unsigned char  Can_Data_Buffer[6]={5,'A','R','D','I','A'}; //TEST CAN
	unsigned short i =0;
	unsigned char X =0, Y=0, Z=0;
	unsigned char ACC_Stat = Waiting_LunchTest;
	char Ecran_1Line1[16];
	char Ecran_1Line2[16];
	
	AccAxesRaw_t *FTstData;
	

// Init SPI DRV
vDSPI_eInitSPI();

//vLCD_iLcdClearDisplay_Cmd ();

////TEST clavier:
vCLV_iCLV_InitTST_Exe();
	vCAN0_iCAN0_InitTST_Exe();
	vCAN1_iCAN1_InitTST_Exe();
// Init LIS3HD
s32ProLIS3HD_iInit();
// Clear Line 1
vLCD_iLcdClearLine_Exe (DucLCD_1st_line);
// Clear Line 2
vLCD_iLcdClearLine_Exe (DucLCD_2nd_line);
FTstData->AXIS_X = 0x0000;
FTstData->AXIS_Y = 0x0000;
FTstData->AXIS_Z = 0x0000;
  
  while(1)
{
 X = i*2 +1;
 Y = i*2 +2;
 Z = i*2 +3;
 vCLV_iClvGestionButton_Cmd();
 us32Counter_1 = 0;
 us32Counter = 0;

 i++;
switch (ACC_Stat)
{
	case Waiting_LunchTest:
	{  i=0;
		vLCD_iLcdGoto_Cmd(DucLCD_1st_line); 
    	vLCD_iLcdPrintChaine_Cmd("  PRESSE SW2 ");
		vLCD_iLcdGoto_Cmd(DucLCD_2nd_line);
		vLCD_iLcdPrintChaine_Cmd(" TO Start TEST ");
		if( 0x01 == ucCLV_ePressedSwitch)
		{
			ACC_Stat = Startting_Test;
			// Clear Line 1
			vLCD_iLcdClearLine_Exe (DucLCD_1st_line);
			// Clear Line 2
			vLCD_iLcdClearLine_Exe (DucLCD_2nd_line);
			//reinit SW2Status 
			ucCLV_ePressedSwitch= 0x00;
		}
		else
		{
			ACC_Stat = Waiting_LunchTest;
		}
    }
    break;
	case Startting_Test:
	{
		s32ProLIS3HD_iTestLunch(FTstData);
		

		vLCD_iLcdGoto_Cmd(DucLCD_1st_line);
		sprintf(Ecran_1Line1,"X:%x Y:%x",FTstData->AXIS_X,FTstData->AXIS_Y);
		vLCD_iLcdPrintChaine_Cmd(Ecran_1Line1);
		vLCD_iLcdGoto_Cmd(DucLCD_2nd_line);
		sprintf(Ecran_1Line2,"Z:%x IT: %d",FTstData->AXIS_Z,i/i);
		vLCD_iLcdPrintChaine_Cmd(Ecran_1Line2);
		
		if( 0x01 == ucCLV_ePressedSwitch)
		{
			ACC_Stat = Waiting_LunchTest;
			// Clear Line 1
			vLCD_iLcdClearLine_Exe (DucLCD_1st_line);
			// Clear Line 2
			vLCD_iLcdClearLine_Exe (DucLCD_2nd_line);
			ucCLV_ePressedSwitch= 0x00;
		}
		else
		{
			if( i == 500)
			{
				i=0;
			}
			ACC_Stat = Startting_Test;
			while(us32Counter < 100)
			{
				while(us32Counter_1 < 1000)
				{
					__wait_nop();
					us32Counter_1++;
				}
				us32Counter++;
			}
			
		}
	}
	break;
	default:
		break;
}
  
}



}