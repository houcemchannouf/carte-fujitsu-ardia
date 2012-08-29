//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : LCD_DRV 
//############################################################################//
// FILE : LCD_DRV.c (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 16/08/2012 |  Ben Slimene Rihem  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//

#include "LCD_DRV.cfg"
#include "LCD_DRV.h"




void vLCD_initLcd_Cmd(void) 
{
	DbLCD_iLcd=0;			/* Port 0 Off*/
	DbLCD_iDirLcd=0xFF;		/* Set Port 0 to output */
	
	DbLCD_iLcd=0x34;		/* Startup sequence */
	vLCD_iLcdWait_Cmd(DulLCD_short_wait);
	DbLCD_iLcd=0x30;		
	vLCD_iLcdWait_Cmd(DulLCD_long_wait);
	DbLCD_iLcd=0x34;
	vLCD_iLcdWait_Cmd(DulLCD_short_wait);
	DbLCD_iLcd=0x30;		
	vLCD_iLcdWait_Cmd(DulLCD_long_wait);
	DbLCD_iLcd=0x34;
	vLCD_iLcdWait_Cmd(DulLCD_short_wait);
	DbLCD_iLcd=0x30;		
	vLCD_iLcdWait_Cmd(DulLCD_long_wait);
	DbLCD_iLcd=0x24;
	vLCD_iLcdWait_Cmd(DulLCD_short_wait);
	DbLCD_iLcd=0x20;
	vLCD_iLcdWait_Cmd(DulLCD_short_wait2);
		
	vLCD_iOutb_Cmd(0x28); 		/* Switch to 4-bit mode */
	vLCD_iOutb_Cmd(DucLCD_CUROFF);	/* No Cursor */
	vLCD_iOutb_Cmd(DucLCD_NOSHIFT);	/* No display shift */
	vLCD_iOutb_Cmd(DucLCD_HOME);		/* Cursor home */
	vLCD_iOutb_Cmd(DucLCD_CLR);		/* Display clear */
}


 


void   vLCD_iOutb_Cmd(unsigned char ucData)	
{
	unsigned char ucTmp;
	
	DbLCD_iLcd_RW =0;
	
	ucTmp = ucData & 0x70 ; 					/* upper nibble   */
	if (ucData & 0x80)       				  /* check MSB       */
	{
	  DbLCD_iLcd_RS=1;							  /* set RS line     */
	};
	
	DbLCD_iLcd_E=1;        					 /* set E line      */
	DbLCD_iLcd_DB4=(ucTmp>>4);
	DbLCD_iLcd_DB5=(ucTmp>>5);
	DbLCD_iLcd_DB6=(ucTmp>>6);
	DbLCD_iLcd_DB7= (ucTmp>>7);	
  __wait_nop();
	DbLCD_iLcd_E=0;     						/* clear E line    */
  __wait_nop();
	ucTmp =ucData ;         				/* lower nibble    */
	
	ucTmp = ucTmp <<4;    		    	/* to upper nibble */
	if (ucData & 0x80)       				/* check MSB       */
	{
		 DbLCD_iLcd_RS=1;							/* set RS line     */
	};
	DbLCD_iLcd_E=1;        					 /* set E line      */
																		
	DbLCD_iLcd_DB4=(ucTmp>>4);
	DbLCD_iLcd_DB5=(ucTmp>>5);				/* send to LCD     */
	DbLCD_iLcd_DB6=(ucTmp>>6);
	DbLCD_iLcd_DB7= (ucTmp>>7);
	
	__wait_nop();
	
	DbLCD_iLcd_E=0;									/* clear E line    */
	vLCD_iLcdBusy_Cmd();						/* check LCD       */
	
}




void vLCD_iLcdBusy_Cmd(void)			
{

volatile unsigned char ucTmp;
	DbLCD_iLcd = 0;						/* Port Off before reading ! *///Eteindre le port de LCD
	ucTmp = 0x80;	   //Activer les pins d’entrées
	DbLCD_iLcd_input |= 0xF0;				/* enable input pins P00_P4 - P00-P7*/
	DbLCD_iDirLcd = 0x0F;	/* set Bus as input to read LCD-busy-flag (LCD_D7) */
	while (ucTmp & 0x80)		/* LCDwait for Busy-line */
	{
	 DbLCD_iLcd_RW = 1; //Activer le registre DbLCD_iLcd_RW.
	 __wait_nop();
	 DbLCD_iLcd_E = 1; 
	 __wait_nop();
	 ucTmp = DbLCD_iLcd;		    /* read Port */ 
	}			
	DbLCD_iLcd_E = 0; //Désactiver le registre DbLCD_iLcd_E.
	__wait_nop(); //Attente
	DbLCD_iLcd_RW = 0; 	//Désactiver le registre DbLCD_iLcd_RW
	DbLCD_iDirLcd = 0xFF;		/* reset Port to output */

}


//Saut de curseur
void vLCD_iLcdGoto_Cmd(unsigned char ucAddress)			
{
	DbLCD_iLcd_E = 1; //Activer le registre DbLCD_iLcd_E.
	// Ecriture des 4-bits de poids fort de l’adresse
	DbLCD_iLcd_DB4=(ucAddress>>4);
	DbLCD_iLcd_DB5=(ucAddress>>5);
	DbLCD_iLcd_DB6=(ucAddress>>6);
	DbLCD_iLcd_DB7= (ucAddress>>7);
  DbLCD_iLcd_E = 0;		                 /* clear E line */
  
  
  DbLCD_iLcd_E = 1; 	
  //Ecriture des 4-bits de poids faible de l’adresse
  DbLCD_iLcd_DB4=(ucAddress);
	DbLCD_iLcd_DB5=(ucAddress>>1);
	DbLCD_iLcd_DB6=(ucAddress>>2);
	DbLCD_iLcd_DB7=(ucAddress>>3);
	
  DbLCD_iLcd_E = 0;		                 /* clear E line */
  DbLCD_iLcd = 0; //Réinitialiser le port
  vLCD_iLcdBusy_Cmd();	 //Attente de libération du LCD.
}	 


//Afficher une chaîne de caractère
void vLCD_iLcdPrintChaine_Cmd(char *cChaine)	
{
 unsigned char ucTmp1;
 unsigned char ucTmp;	
 unsigned short usCounter,usTail;

 usTail=strlen(cChaine);
 for (usCounter=0; usCounter<usTail; usCounter++) 		/* go through string */
  {
	ucTmp1=(cChaine[usCounter]);											/* pick char */
	
    ucTmp=(ucTmp1 | 0x80); 
  
      vLCD_iOutb_Cmd(ucTmp);	
  } 
}

//Mettre un délai d’attente
void vLCD_iLcdWait_Cmd(unsigned long ulCounter)
{
 while(ulCounter--)  //attente
 __wait_nop();// 8MHZ 1 __waitnop() = 7 us
}

//Décaler l’affichage vers la gauche
void vLCD_iLcdShiftDisplayLeft_Cmd(void)	
{
 	vLCD_iOutb_Cmd(DucLCD_SHIFT_DISPLAY_LEFT);
} 


//Décaler l’affichage vers la droite
void vLCD_iLcdShiftDisplayRight_Cmd(void)	
{
 	vLCD_iOutb_Cmd(DucLCD_SHIFT_DIS_RIGHT);
} 


//Décaler le curseur vers la droite
void vLCD_iLcdShiftCursorRight_Cmd(void)	
{
 	vLCD_iOutb_Cmd(DucLCD_SHIFT_CUR_RIGHT);
}

//Décaler le curseur vers la gauche
void vLCD_iLcdShiftCursorLeft_Cmd(void)	
{
 	vLCD_iOutb_Cmd(DucLCD_SHIFT_CUR_LEFT);
} 


//Effacer LCD
void vLCD_iLcdClearDisplay_Cmd(void)	
{
 	vLCD_iOutb_Cmd(DucLCD_CLR);
}