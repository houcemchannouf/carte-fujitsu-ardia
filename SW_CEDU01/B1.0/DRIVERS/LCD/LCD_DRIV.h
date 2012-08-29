//############################################################################//
// HEAD : (c) ARDIA 2012 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : LCD_DRV 
//############################################################################//
// FILE : LCD_DRV.h (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 16/08/12 | Ben Slimene Rihem  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//
#include "mb96348rs.h"
#include "LCD_DRV.cfg"



/* Wait times (depends on used MCU speed) */
#define DucLCD_tiny_wait   20
#define DulLCD_short_wait  400
#define DulLCD_short_wait2 700
#define DulLCD_short_wait3 1400
#define DulLCD_long_wait   50000

/* Control defines (use with LCDoutb) : */

#define DucLCD_CLR                  0x01
#define DucLCD_HOME                 0x03
#define DucLCD_CUROFF               0x0C
#define DucLCD_NOSHIFT              0x06
#define DucLCD_SHIFT_DISPLAY_LEFT   0x18
#define DucLCD_SHIFT_DIS_RIGHT      0x1C
#define DucLCD_SHIFT_CUR_LEFT       0x00
#define DucLCD_SHIFT_CUR_RIGHT      0x11
#define DucLCD_1st_line             0x80
#define DucLCD_2nd_line             0xC0


/* Prototypes */

void vLCD_initLcd_Cmd(void); 
void vLCD_iOutb_Cmd(unsigned char);
void vLCD_iLcdGoto_Cmd(unsigned char address);
void vLCD_iLcdPrintChaine_Cmd(char *Name2);
void vLCD_iLcdWait_Cmd(unsigned long i);
void vLCD_iLcdBusy_Cmd(void);
void vLCD_iLcdClearDisplay_Cmd(void)	;
void vLCD_iLcdShiftDisplayLeft_Cmd(void);
void vLCD_iLcdShiftDisplayRight_Cmd(void);
void vLCD_iLcdShiftCursorRight_Cmd(void);
void vLCD_iLcdShiftCursorLeft_Cmd(void);