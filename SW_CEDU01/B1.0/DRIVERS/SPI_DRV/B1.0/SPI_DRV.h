//############################################################################//
// HEAD : (c) ARDIA 2010 : " Any copie and re-utilisation of this file without  
//                           the written consent of ARDIA is forbidden "        
//        --------------------------------------------------------------------  
//        Classification :  (-)No   (-)Confident. ARDIA   (-)Confident. Client  
//        --------------------------------------------------------------------  
//        --------------------------------------------------------------------  
//        Module name : SPI_DRV 
//############################################################################//
// FILE : SPI_DRV.h (SOURCE)
//----------------------------------------------------------------------------//
// DESC : Module description
//----------------------------------------------------------------------------//
// LIST : * List of the functions
//----------------------------------------------------------------------------//
// HIST : Version |   Date   | Author | Description                             
//----------------------------------------------------------------------------//
//         01.00  | 18/05/12 |  YFAR  | Creation of this file
//
//############################################################################//

//****************************************************************************//
// INCLIB
//****************************************************************************//

//****************************************************************************//
// INCUSER
//****************************************************************************//
#include "..\..\..\SYSTEME\REG\mb96346rs.h"
//#include "..\..\..\DRIVERS\LCD_DRV\B1.0\SPI_DRV.cfg"
#define Du8MultipleAcces 1

void vSPI_iInitUART(void);
void vSPI_iInitPorts(void);
void vSPI_eRead_Data(unsigned char adr);
void vDSPI_eWrite_Data(unsigned char adr);
void vDSPI_eInitSPI(void);