/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : example_main.c
* Author             : MSH Application Team
* Author             : Fabio Tota
* Revision           : $Revision: 1.5 $
* Date               : $Date: 16/06/2011 12:19:08 $
* Description        : Example main file for MKI109V1 board
* HISTORY:
* Date        | Modification                                | Author
* 16/06/2011  | Initial Revision                            | Fabio Tota

********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOFTWARE IS SPECIFICALLY DESIGNED FOR EXCLUSIVE USE WITH ST PARTS.
*
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
//include files for MKI109V1 board 
#include <stdio.h>

//include MEMS driver
#include "..\..\DRIVERS\LIS3DH_DRV\LIS3DH_DRV.h"
#include "..\..\PROTOCOLES\LIS3DH_PRO\LIS3DH_PRO.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
unsigned char response;
unsigned char USBbuffer[64];

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//define for example1 or example2
#define __EXAMPLE1__H 
//#define __EXAMPLE2__H 
#define	ERROR	-1

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int s32ProLIS3HD_iInit(void)
{
  int s32Return = 0x00;
 
  //Inizialize MEMS Sensor
  //set ODR (turn ON device) CTRL_REG1
  s32Return = SetODR(ODR_100Hz);
  if(s32Return == 0)
  {
        return (ERROR);
  }
  //set PowerMode  CTRL_REG1
  s32Return = SetMode(NORMAL);
  if(s32Return==0)
  {
        return (ERROR);
  }
  //set Fullscale CTRL_REG4
  s32Return = SetFullScale(FULLSCALE_2);
  if(s32Return==0)
  {
        return (ERROR);
  }
  
  //set axis Enable CTRL_REG1
  s32Return = SetAxis(X_ENABLE | Y_ENABLE | Z_ENABLE);
  if(s32Return==0)
  {
        return (ERROR);
  }

 } 
 
int s32ProLIS3HD_iTestLunch(AccAxesRaw_t *Data)
{
	unsigned char position=0, old_position=0;
	AccAxesRaw_t data;
	int s32Return = 0x00;
/*********************/  
/******Example 1******/ 

  //get Acceleration Raw data  
  s32Return = GetAccAxesRaw(Data);
  if(s32Return==0)
  {
	return(ERROR); 
    old_position = position;
  }
   return (s32Return);

 
 /*********************/
/******Example 2******/
/*#ifdef __EXAMPLE2__H
 //configure Mems Sensor
 //set Interrupt Threshold 
 s32Return = SetInt1Threshold(20);
 if(s32Return==0)
  {
        return (ERROR);
  }
 //set Interrupt configuration (all enabled)
 s32Return = SetIntConfiguration(INT1_ZHIE_ENABLE | INT1_ZLIE_ENABLE |
                                INT1_YHIE_ENABLE | INT1_YLIE_ENABLE |
                                INT1_XHIE_ENABLE | INT1_XLIE_ENABLE ); 
 if(s32Return==0)
 {
        return (ERROR);
 }
 //set Interrupt Mode
 s32Return = SetIntMode(INT_MODE_6D_POSITION);
  if(s32Return==0)
  {
        return (ERROR);
  }


  //get 6D Position
  response = Get6DPosition(&position);
  if((response==1) && (old_position!=position))
  {

/*	switch (position)
	{
	case UP_SX:   sprintf((char*)buffer,"\n\rposition = UP_SX  \n\r\0");   break;
	case UP_DX:   sprintf((char*)buffer,"\n\rposition = UP_DX  \n\r\0");   break;
	case DW_SX:   sprintf((char*)buffer,"\n\rposition = DW_SX  \n\r\0");   break;              
	case DW_DX:   sprintf((char*)buffer,"\n\rposition = DW_DX  \n\r\0");   break; 
	case TOP:     sprintf((char*)buffer,"\n\rposition = TOP    \n\r\0");   break; 
	case BOTTOM:  sprintf((char*)buffer,"\n\rposition = BOTTOM \n\r\0");   break; 
	default:      sprintf((char*)buffer,"\n\rposition = unknown\n\r\0");   break;
	}
*//*	old_position = position;
  }

#endif /*__EXAMPLE2__H *//* 
 */
} // end main



/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
